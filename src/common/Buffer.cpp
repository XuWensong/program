#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>

#include "Buffer.h"
#include "SafeIO.h"

using namespace std;

uint64_t round_up_to(uint64_t n, uint64_t d)
{
	return (n % d) ? (n + d - n%d) : n;
}

buffer::raw::raw(uint64_t len)
	:m_data(NULL), m_off(0), m_len(len), m_nref(0)
{
	if (m_len) {
		m_data = (char*)malloc(m_len);
	} else
		m_data = NULL;
}

buffer::raw::~raw()
{
	if (m_data) {
		free(m_data);
		m_data = NULL;
	}
}

buffer::ptr::ptr()
	:m_raw(NULL), m_off(0), m_len(0)
{
}

buffer::ptr::ptr(raw *r)
	:m_raw(r), m_off(0), m_len(r->m_len)
{
	m_raw->m_nref++;
}

buffer::ptr::ptr(char* c, uint64_t l)
	:m_raw(NULL), m_off(0), m_len(l)
{
	m_raw = copy(c, l);
	m_raw->m_nref++;
}

buffer::ptr::ptr(const ptr &p)
	:m_raw(p.get_raw()), m_off(p.offset()), m_len(p.length())
{
	m_raw->m_nref++;
}

buffer::ptr::ptr(ptr &p, uint64_t o, uint64_t l)
	:m_raw(p.get_raw()), m_off(p.offset() + o), m_len(l)
{
	m_raw->m_nref++;
}

buffer::ptr& buffer::ptr::operator=(const ptr &p)
{
	if (p.m_raw) {
		p.m_raw->m_nref++;
	}
	buffer::raw *_raw = p.m_raw;
	release();
	if (_raw) {
		m_raw = _raw;
		m_off = p.m_off;
		m_len = p.m_len;
	} else {
		m_off = m_len = 0;
	}
	return *this;
}

buffer::ptr::~ptr()
{
	release();
}

uint64_t buffer::ptr::unused_tail_length() const
{
	if (m_raw)
		return m_raw->m_len - (m_off + m_len);
	return 0;
}

void buffer::ptr::append(char c)
{
	(c_str())[m_len] = c;
	m_len += 1;
}

void buffer::ptr::append(const char *c, uint64_t l)
{
	memcpy(m_raw->m_data + m_len, c, l);
	m_len += l;
}

buffer::raw* buffer::ptr::copy(char *c, uint64_t l)
{
	raw *r = new raw(l);
	memcpy(r->m_data, c, l);
	return r;
}

char* buffer::ptr::c_str()
{
	return m_raw->m_data + m_off;
}

const char* buffer::ptr::c_str() const 
{
	return m_raw->m_data + m_off;
}

void buffer::ptr::copy_in(uint64_t o, uint64_t l, const char * s)
{
	memcpy(c_str() + o, s, l);
}

void buffer::ptr::copy_out(uint64_t o, uint64_t l, char* d)
{
	if (o + l > m_len)
		throw end_of_buffer();
	memcpy(d, c_str() + o, l);
}

void buffer::ptr::release()
{
	if (!m_raw)
		return;

	m_raw->m_nref--;
	if (m_raw->m_nref == 0) {
		delete m_raw;
		m_raw = NULL;
	}
}

void buffer::list::iterator::seek(uint64_t o)
{
	m_ip = m_lp->begin();
	m_bl_off = m_ptr_off = 0;
	advance(o);
}

void buffer::list::iterator::advance(uint64_t o)
{
	// advance forward
	if (o > 0) {
		m_ptr_off += o;
		while (m_ptr_off > 0) {
			if (m_ip == m_lp->end())
				throw end_of_buffer();
			if (m_ptr_off >= m_ip->length()) {
				m_ptr_off -= m_ip->length();
				m_ip++;
			} else {
				break;
			}
			m_bl_off += o;
			return;
		}
	}

	while (o < 0) {
		if (m_ptr_off) {
			uint64_t abs = -o;
			if (abs > m_ptr_off)
				abs = m_ptr_off;
			m_ptr_off -= abs;
			m_bl_off -= abs;
			o += abs;
		} else if (m_bl_off > 0) {
			m_ip--;
			m_ptr_off = m_ip->length();
		} else {
			throw end_of_buffer();
		}
	}
}

void buffer::list::iterator::copy(uint64_t l, char* d)
{
	if (m_ip == m_lp->end()) 
		seek(m_bl_off);

	while (l > 0) {
		if (m_ip == m_lp->end())
			throw end_of_buffer();

		uint64_t len = m_ip->length() - m_ptr_off;
		if (l < len) 
			len = l;
		m_ip->copy_out(m_ptr_off, len, d);
		d += len;

		l -= len;
		advance(len);
		
	}
}

void buffer::list::iterator::copy(uint64_t l, ptr& d)
{
	d = create(l);
	copy(l, d.c_str());
}

void buffer::list::iterator::copy(uint64_t l, list& d)
{
	if (m_ip == m_lp->end()) 
		seek(m_bl_off);

	while (l > 0) {
		if (m_ip == m_lp->end())
			throw end_of_buffer();

		uint64_t len = m_ip->length() - m_ptr_off;
		if (l < len)
			len = l;
		d.append(*m_ip, m_ptr_off, len);

		l -= len;
		advance(len);
	}
	
}

void buffer::list::iterator::copy(uint64_t l, string &d)
{
	if (m_ip == m_lp->end())
		seek(m_bl_off);

	while (l > 0) {
		if (m_ip == m_lp->end())
			throw end_of_buffer();

		uint64_t len = m_ip->length() - m_ptr_off;
		if (l < len)
			len = l;
		const char* c = m_ip->c_str();
		d.append(c + m_ptr_off, len);
		l -= len;
		advance(len);
	}
}

void buffer::list::append(char c)
{
	uint64_t gap = m_append_buffer.unused_tail_length();
	if (!gap) {
		uint64_t alen = S3FS_PAGE_SIZE;
		m_append_buffer = create_aligned(alen);
		m_append_buffer.set_length(0);
	}

	m_append_buffer.append(c);
	append(m_append_buffer, m_append_buffer.end() - 1, 1);
}

void buffer::list::append(const char *c, uint64_t l)
{
	while (l > 0) {
		uint64_t gap = m_append_buffer.unused_tail_length();
		if (gap) {
			if (gap > l) 
				gap = l;
			m_append_buffer.append(c, gap);
			append(m_append_buffer, m_append_buffer.end() - gap, gap);
			l -= gap;
			c += gap;
		}

		if (l == 0)
			break;

		uint64_t alen = S3FS_PAGE_SIZE * ((l - 1) / S3FS_PAGE_SIZE + 1);
		m_append_buffer = create_aligned(alen);
		m_append_buffer.set_length(0);
	}
	
}

void buffer::list::append(string s)
{
	append(s.c_str(), s.length());
}

void buffer::list::append(ptr &p)
{
	if (p.length())
		push_back(p);
}

void buffer::list::append(ptr &p, uint64_t o, uint64_t l)
{
	if (!m_buffers.empty()) {
		ptr &bp = m_buffers.back();
		if (bp.get_raw() == p.get_raw() &&
			bp.end() == p.start() + o) {
			bp.set_length(bp.length() + l);
			m_len += l;
			// contiguous, return;
			return;
		}
	}

	ptr tp(p, o, l);
	push_back(tp);
}

void buffer::list::append(const list &l)
{
	m_len += l.m_len;
	std::list<ptr>::const_iterator it = l.m_buffers.begin();
	for(; it != l.m_buffers.end(); it++)
		m_buffers.push_back(*it);
}

void buffer::list::splice(uint64_t off, uint64_t len, list *by)
{
	if (len == 0)
		return;

	if (off >= length())
		throw end_of_buffer();

	std::list<ptr>::iterator it = m_buffers.begin();
	while (off > 0) {
		if (off >= it->length()) {
			off -= it->length();
			it++;
		} else {
			break;
		}
	}

	if (off) {
		// trim and keep head of ptr
		m_buffers.insert(it, ptr(*it, 0, off));
		m_len += off;
	}

	while (len > 0) {
		if (off + len < it->length()) {
			if (by)
				by->append(*it, off, len);
			// trim and keep end of ptr
			it->set_offset(off + len + it->offset());
			it->set_length(it->length() - (off + len));
			m_len -= off + len;
			break;
		}

		uint64_t cnt = it->length() - off;
		if (by)
			by->append(*it, off, cnt);
		m_len -= it->length();
		m_buffers.erase(it++);
		len -= cnt;
		off = 0;
	}
	
}

char* buffer::list::c_str()
{
	if (m_buffers.empty())
		return NULL;

	std::list<ptr>::iterator it = m_buffers.begin();
	it++;

	if (it != m_buffers.end())
		rebuild();

	return m_buffers.front().c_str();
}

void buffer::list::push_back(ptr & p)
{
	if (!p.length())
		return;

	m_buffers.push_back(p);
	m_len += p.length();
}

void buffer::list::clear()
{
	m_buffers.clear();
	m_len = 0;
}

buffer::raw* buffer::list::create_aligned(uint64_t alen)
{
	return new raw(alen);
}

void buffer::list::rebuild()
{
	cout << __func__ << endl;
	ptr np(create_aligned(m_len));
	uint64_t pos = 0;
	std::list<ptr>::iterator iter = m_buffers.begin();
	for (; iter != m_buffers.end(); iter++) {
		np.copy_in(pos, iter->length(), iter->c_str());
		pos += iter->length();
	}

	m_buffers.clear();
	m_buffers.push_back(np);
}

int64_t buffer::list::read_file(const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0) {
		return -errno;
	}

	struct stat st;
	int r = fstat(fd, &st);
	if (r < 0)
		return r;

	r = read_fd(fd, 0, st.st_size);
	::close(fd);

	return r;
}

int64_t buffer::list::read_fd(int fd, uint64_t len)
{
	return read_fd(fd, 0, len);
}

int64_t buffer::list::read_fd(int fd, uint64_t off, uint64_t len)
{
	uint64_t alen = round_up_to(len, S3FS_PAGE_SIZE);
	bufferptr bp = create_aligned(alen);
	int64_t r = safe_pread(fd, bp.c_str(), len, off);
	if (r >= 0) {
		bp.set_length(r);
		append(bp);
	}
	return r;
}

int buffer::list::write_file(const char *path, int mode)
{
	int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, mode);
	if (fd < 0) {
		return -errno;
	}

	int r = write_fd(fd, 0);
	::close(fd);

	return r;
}

int buffer::list::write_fd(int fd)
{
	return write_fd(fd, 0);
}

int buffer::list::write_fd(int fd, uint64_t off)
{
	std::list<ptr>::iterator it = m_buffers.begin();
	for(; it != m_buffers.end(); it++) {
		int r = safe_pwrite(fd, it->c_str(), it->length(), off);
		if (r < 0)
			return r;

		off += it->length();
	}
	return 0;
}