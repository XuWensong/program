#include <unistd.h>
#include <errno.h>
#include <iostream>

#include "SafeIO.h"

using namespace std;

int64_t safe_read(int fd, void *buf, uint64_t len)
{
	uint64_t cnt = 0;
	while (cnt < len) {
		int64_t r = read(fd, buf, len);
		if (r <= 0) {
			//EOF
			if (r == 0)
				return cnt;

			// no data was read, retry
			if (errno == EINTR)
				continue;

			return -errno;
		}

		cnt += r;
		buf = (char *)buf + r;
	}
	return cnt;
}

int64_t safe_pread(int fd, void *buf, uint64_t len, uint64_t off)
{
	uint64_t cnt = 0;
	while (cnt < len) {
		int64_t r = pread(fd, buf, len, off);
		if (r <= 0) {
			//EOF
			if (r == 0)
				return cnt;

			if (errno == EINTR)
				continue;
			return -errno;
		}

		cnt += r;
		off += r;
		buf = (char *)buf + r;
	}
	return cnt;
}

int safe_write(int fd, void *buf, uint64_t len)
{
	while (len > 0) {
		int r = write(fd, buf, len);
		if (r < 0) {
			// no data was written, retry
			if (errno == EINTR)
				continue;
			return -errno;
		}

		len -= r;
		buf = (char *)buf + r;
	}
	return 0;
}

int safe_pwrite(int fd, void *buf, uint64_t len, uint64_t off)
{
	while (len > 0) {
		int r = pwrite(fd, buf, len, off);
		if (r < 0) {
			if (errno == EINTR)
				continue;
			return -errno;
		}

		off += r;
		len -= r;
		buf = (char *)buf + r;
	}
	return 0;
}