#ifndef S3FS_SAFEIO_H
#define S3FS_SAFEIO_H

#include <inttypes.h>
#include <errno.h>

int64_t safe_read(int fd, void *buf, uint64_t len);
int64_t safe_pread(int fd, void *buf, uint64_t len, uint64_t off);
int safe_write(int fd, void *buf, uint64_t len);
int safe_pwrite(int fd, void *buf, uint64_t len, uint64_t off);
#endif
