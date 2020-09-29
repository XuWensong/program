#include <sys/stat.h>
#include <iostream>

#include "Journaler.h"

#define ENTRY_HEAD_SIZE 8

using namespace std;

void Journaler::Header::encode(bufferlist &bl)
{
	ENCODE_START(0, 0, bl);
	::encode(trim_pos, bl);
	::encode(sync_pos, bl);
	::encode(sync_off, bl);
	::encode(commit_pos, bl);
	::encode(commit_off, bl);
	::encode(layout, bl);
}

void Journaler::Header::decode(bufferlist::iterator &bl)
{
	DECODE_START(0, bl);
	::decode(trim_pos, bl);
	::decode(sync_pos, bl);
	::decode(sync_off, bl);
	::decode(commit_pos, bl);
	::decode(commit_off, bl);
	::decode(layout, bl);
}

void Journaler::Header::dump()
{
	cout << "Journaler head:" << endl;
	cout << "    trim_pos: " <<  trim_pos << endl;
	cout << "    sync_pos: " <<  sync_pos << endl;
	cout << "    sync_off: " <<  sync_off << endl;
	cout << "    commit_pos: " <<  commit_pos << endl;
	cout << "    commit_off: " <<  commit_off << endl;
	cout << "    layout: " <<  layout << endl;
}

Journaler::Journaler()
	:m_fd(-1), m_sync_fd(-1)
{}

Journaler::~Journaler()
{}

int Journaler::open(string top_dir)
{
	bufferlist head_bl;
	m_top_dir = top_dir;
	string log_head = _log_head_name();

	int r = head_bl.read_file(log_head.c_str());
	if (r < 0 && r != -ENOENT) {
		return r;
	}

	if (!head_bl.empty()) {
		bufferlist::iterator p = head_bl.begin();
		::decode(m_head, p);
	}

	r = _open_new_file(m_fd, m_head.commit_pos, O_CREAT | O_RDWR);
	if (r < 0)
		return r;
	lseek(m_fd, m_head.commit_off, SEEK_SET);

	r = _open_new_file(m_sync_fd, m_head.sync_pos, O_RDONLY);
	if (r < 0)
		return r;
	lseek(m_sync_fd, m_head.sync_off, SEEK_SET);
	return 0;
}

int Journaler::close()
{
	if (m_fd > 0)
		::close(m_fd);

	if (m_sync_fd)
		::close(m_sync_fd);
	return 0;
}

int Journaler::append_entry(bufferlist &bl)
{
	int r = 0;
	bufferlist write_bl;
	if (bl.empty())
		return 0;

	if (m_head.commit_off >= m_head.layout) {
		// change to new log file
		m_head.commit_pos += 1;
		m_head.commit_off = 0;
		r = _open_new_file(m_fd, m_head.commit_pos, O_CREAT | O_RDWR);
		if (r < 0)
			return r;
	}

	uint64_t len = bl.length();
	::encode(len, write_bl);
	write_bl.append(bl);

	r = write_bl.write_fd(m_fd, m_head.commit_off);
	if (r < 0)
		return r;

	m_head.commit_off += bl.length() + ENTRY_HEAD_SIZE;
	r = _write_head();
	if (r < 0)
		return r;

	return 0;
}

bool Journaler::try_read_entry(bufferlist &bl)
{
	struct stat st;
	int r = 0;
	// nothing to read
	if (!_is_readable()) {
		cout << " journaler not readable" << endl;
		return false;
	}

	if (m_loaded_ents.length()) {
		cout << "read_from_buffer" << endl;
		goto read_from_buffer;
	}

	if (m_head.sync_off >= m_head.layout) {
		// change to new file
		m_head.sync_pos += 1;
		m_head.sync_off = 0;
		r = _open_new_file(m_sync_fd, m_head.sync_pos, O_RDONLY);
		if (r < 0) {
			cout << "failed to open_new_file" << endl;
			return false;
		}
	}

	m_loaded_ents.clear();
	r = fstat(m_sync_fd, &st);
	if (r < 0)
		return false;

	cout << "load len=" << st.st_size << " from log" << endl;
	r = m_loaded_ents.read_fd(m_sync_fd, m_head.sync_off, st.st_size - m_head.sync_off);
	if (r < 0) {
		cout << "failed to read_fd" << endl;
		return false;
	}

read_from_buffer:
	uint64_t ent_len = 0;
	bufferlist l_bl;
	m_loaded_ents.splice(0, ENTRY_HEAD_SIZE, &l_bl);

	bufferlist::iterator p = l_bl.begin();
	::decode(ent_len, p);

	m_loaded_ents.splice(0, ent_len, &bl);
	

	return true;
}

string Journaler::_log_file_name(uint64_t id)
{
	string log_file = m_top_dir;
	char buf[21];

	snprintf(buf, sizeof(buf), "log.%016lx", id);
	log_file.append("/");
	log_file.append(buf);
	return log_file;
}

string Journaler::_log_head_name()
{
	string log_head = m_top_dir;
	log_head.append("/log.head");
	return log_head;
}

int Journaler::_open_new_file(int &fd, uint64_t oid, int flags)
{
	if (fd > 0) {
		::close(fd);
		fd = -1;
	}

	string log_file = _log_file_name(oid);
	fd = ::open(log_file.c_str(), flags, 0600);
	if (fd < 0)
		return -errno;
	
	return 0;
}

int Journaler::write_head()
{
	return _write_head();
}

int Journaler::_write_head()
{
	bufferlist bl;
	string log_head = _log_head_name();
	
	::encode(m_head, bl);

	return bl.write_file(log_head.c_str());
}

bool Journaler::is_readable()
{
	return _is_readable();
}

int Journaler::flushed(uint64_t l)
{
	m_head.sync_off += l + ENTRY_HEAD_SIZE;
	return _write_head();
}

bool Journaler::_is_readable()
{
	if (m_head.sync_pos < m_head.commit_pos)
		return true;

	if (m_head.sync_off < m_head.commit_off)
		return true;

	return false;
}