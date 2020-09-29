#ifndef S3FS_JOURNALER_H
#define S3FS_JOURNALER_H

#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>

#include "common/Encoding.h"

class Journaler {
public:
	struct Header {
		uint64_t trim_pos;
		uint64_t sync_pos;
		uint64_t sync_off;
		uint64_t commit_pos;
		uint64_t commit_off;
		uint64_t layout;

		Header():trim_pos(0), sync_pos(0), sync_off(0), 
				    commit_pos(0), commit_off(0), layout(1024){}

		void encode(bufferlist &bl);
		void decode(bufferlist::iterator &bl);
		void dump();
	};
private:
	Header m_head;
	std::string m_top_dir;
	int m_fd;
	int m_sync_fd;
	bufferlist m_loaded_ents;
public:
	Journaler();
	~Journaler();
	int open(std::string top_dir);
	int close();
	int append_entry(bufferlist &bl);
	bool try_read_entry(bufferlist &bl);
	int write_head();
	bool is_readable();
	int flushed(uint64_t l);
private:
	std::string _log_file_name(uint64_t id);
	std::string _log_head_name();
	int _open_new_file(int &fd, uint64_t oid, int flags);
	int _write_head();
	bool _is_readable();
	
};
WRITE_CLASS_ENCODER(Journaler::Header)

#endif
