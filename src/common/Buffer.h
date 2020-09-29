#ifndef S3FS_BUFFER_H
#define S3FS_BUFFER_H
#include <inttypes.h>
#include <list>
#include <unistd.h>
#include <atomic>
#include <string>
#include <exception>

#define S3FS_PAGE_SIZE sysconf(_SC_PAGESIZE)

typedef std::atomic<uint64_t> atomic_t;

struct error : public std::exception {
	const char* what() const throw() {
		return "buffer::exception";
	}
};

struct end_of_buffer : public error {
	const char* what() const throw() {
		return "buffer::end_of_buffer";
	}
};

struct malformed_input : public error {
	const char* what() throw() {
		return "buffer::malformed_input";
	}
};


class buffer {

public:
class raw{
public:
	char *m_data;
	uint64_t m_off, m_len;
	atomic_t m_nref;
public:
	raw(uint64_t len);
	~raw();

}; //end raw

class ptr{
private:
	raw *m_raw;
	uint64_t m_off, m_len;

public:
	ptr();
	ptr(raw *r);
	ptr(char *c, uint64_t l);
	ptr(const ptr &ptr);
	ptr(ptr &p, uint64_t o, uint64_t l);
	ptr& operator=(const ptr &p);
	~ptr();

	raw* get_raw() const {return m_raw;}
	uint64_t unused_tail_length() const;
	void append(char c);
	void append(const char *c, uint64_t l);
	raw* copy(char *c, uint64_t l);
	char* c_str();
	const char* c_str() const;
	void copy_in(uint64_t o, uint64_t l, const char* s);
	void copy_out(uint64_t o, uint64_t l, char* d);
	void set_offset(uint64_t o) {m_off = o;}
	void set_length(uint64_t l) {m_len = l;}
	uint64_t offset() const {return m_off;}
	uint64_t length() const {return m_len;}
	uint64_t start() {return m_off;}
	uint64_t end() {return m_off + m_len;}
private:
	void release();

}; //end ptr


// buffer::list is not thread safe
class list{
private:
	std::list<ptr> m_buffers;
	uint64_t m_len;
	ptr m_append_buffer;
public:
class iterator{
private:
	list *m_bl;
	std::list<ptr> *m_lp;
	uint64_t m_bl_off;
	uint64_t m_ptr_off;
	std::list<ptr>::iterator m_ip;
public:
	iterator():m_bl(NULL), m_lp(NULL), m_bl_off(0), m_ptr_off(0){}
	iterator(list *bl, uint64_t bo):
		m_bl(bl), m_lp(&(bl->m_buffers)), m_bl_off(0), m_ptr_off(0), m_ip(m_lp->begin()){}
	iterator(list *bl, uint64_t bo, uint64_t po, std::list<ptr>::iterator ip)
		:m_bl(bl), m_lp(&bl->m_buffers), m_bl_off(bo), m_ptr_off(po), m_ip(ip){}

	void seek(uint64_t o);
	void advance(uint64_t o);
	void copy(uint64_t l, char* d);
	void copy(uint64_t l, ptr& d);
	void copy(uint64_t l, list& d);
	void copy(uint64_t l, std::string &d);
private:
	raw* create(uint64_t l) {return new raw(l);}
};
public:
	list():m_len(0){}
	list(const list &l):m_buffers(l.m_buffers), m_len(l.m_len){}
	~list() {}
	void append(char c);
	void append(const char *c, uint64_t l);
	void append(std::string s);
	void append(ptr &p);
	void append(ptr &p, uint64_t off, uint64_t l);
	void append(const list &l);
	void splice(uint64_t off, uint64_t len, list *by);
	uint64_t length() {return m_len;}
	char* c_str();
	void push_back(ptr &p);
	void clear();
	bool empty() {return m_buffers.empty();}
	iterator begin() {return iterator(this, 0);}
	iterator end(){return iterator(this, m_len, 0, m_buffers.end());}
	int64_t read_file(const char* path);
	int64_t read_fd(int fd, uint64_t len);
	int64_t read_fd(int fd, uint64_t off, uint64_t len);
	int write_file(const char* path, int mode=0644);
	int write_fd(int fd);
	int write_fd(int fd, uint64_t off);
	void rebuild();
private:
	raw* create_aligned(uint64_t alen);
};//end list
};// end buffer

typedef buffer::ptr bufferptr;
typedef buffer::list bufferlist;

#endif
