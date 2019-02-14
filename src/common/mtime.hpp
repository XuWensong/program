#ifndef SONGZI_MTIME_H
#define SONGZI_MTIME_H

#include <inttypes.h>
#include <sys/time.h>

struct mtime {
public:
	struct {
		uint64_t tv_sec, tv_nsec;
	} tv;

	mtime(){}
	mtime(const struct timeval *t) {
		set_from_timeval(t);
	}

	void set_from_timeval(const struct timeval *t){
		tv.tv_sec = t->tv_sec;
		tv.tv_nsec = t->tv_usec * 1000;
	}

	time_t sec() const {return tv.tv_sec;}
	long usec() const {return tv.tv_nsec / 1000;}
	int nsec() const {return tv.tv_nsec;}
	
};

#endif
