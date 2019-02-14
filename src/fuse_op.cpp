#include "fuse_op.hpp"

#include <string>
#include <signal.h>
#include <string.h>

using namespace std;
static void fuse_ll_init(void *userdata, struct fuse_conn_info *conn)
{
	FuseHandle *handle = (FuseHandle *)userdata;
	cout << __func__ << endl;
}

static void fuse_ll_lookup(fuse_req_t req, fuse_ino_t parent, const char* name)
{
	FuseHandle *handle = (FuseHandle *)fuse_req_userdata(req);
	struct fuse_entry_param fe;

	cout << __func__ << endl;

	memset(&fe, 0, sizeof(fe));
	fe.ino = 0;
	fe.attr.st_rdev = 0;
	fuse_reply_entry(req, &fe);	
}

static void fuse_ll_forget(fuse_req_t req, fuse_ino_t ino, unsigned long nlookup)
{
	cout << __func__ << endl;
	fuse_reply_none(req);
}

static void fuse_ll_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	
	FuseHandle *handle = (FuseHandle*)fuse_req_userdata(req);
	const struct fuse_ctx *ctx = fuse_req_ctx(req);
	struct stat stat_buf;

	memset(&stat_buf, 0, sizeof(stat_buf));
	stat_buf.st_ino = 1;
	stat_buf.st_dev = 0;
	stat_buf.st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO;
	stat_buf.st_rdev = 0;
	stat_buf.st_nlink = 0;
	stat_buf.st_uid = ctx->uid;
	stat_buf.st_gid = ctx->gid;
	mtime now = songzi_clock_now();
	stat_buf.st_ctime = now.sec();
	stat_buf.st_mtime = now.sec();
	stat_buf.st_atime = now.sec();
	stat_buf.st_size = 6;
	stat_buf.st_blocks = 1;
	stat_buf.st_blksize = 4096;
	fuse_reply_attr(req, &stat_buf, 0);
}

static void fuse_ll_setattr(fuse_req_t req, fuse_ino_t ino, struct stat *attr,
			int to_set, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_readlink(fuse_req_t req, fuse_ino_t ino) 
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_mknod(fuse_req_t req, fuse_ino_t parent, const char* name, 
				mode_t mode, dev_t rdev){
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_mkdir(fuse_req_t req, fuse_ino_t parent, const char* name,
				mode_t mode)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_unlink(fuse_req_t req, fuse_ino_t parent, const char* name)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_rmdir(fuse_req_t req, fuse_ino_t parent, const char* name)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_symlink(fuse_req_t req, const char* link, fuse_ino_t parent,
				const char* name)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_rename(fuse_req_t req, fuse_ino_t parent, const char* name,
				fuse_ino_t newparent, const char* newname)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_link(fuse_req_t req, fuse_ino_t ino, fuse_ino_t newparent,
				const char* newname)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
				struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_write(fuse_req_t req, fuse_ino_t ino, const char* buf, size_t size,
				off_t off, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_flush(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_release(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_fsync(fuse_req_t req, fuse_ino_t ino, int datasync,
				struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_opendir(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fi->fh = NULL;
	fuse_reply_open(req, fi);
}

static void fuse_ll_readdir(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
				struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_buf(req, "", 0);
}

static void fuse_ll_releasedir(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_fsyncdir(fuse_req_t req, fuse_ino_t ino, int datasync,
				struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_statfs(fuse_req_t req, fuse_ino_t ino)
{
	cout << __func__ << endl;
	struct statvfs stat_buf;
	int BLOCK_SHIFT = 22;
	
	memset(&stat_buf, 0, sizeof(stat_buf));
	stat_buf.f_frsize = 1 << BLOCK_SHIFT;
	stat_buf.f_bsize = 1 << BLOCK_SHIFT;
	stat_buf.f_files = 1;
	stat_buf.f_ffree = -1;
	stat_buf.f_favail = -1;
	stat_buf.f_fsid = -1;
	stat_buf.f_flag = 0;
	stat_buf.f_namemax = 100;
	stat_buf.f_blocks = 1 << BLOCK_SHIFT;
	stat_buf.f_bfree = 1 << BLOCK_SHIFT;
	stat_buf.f_bavail = 1 << BLOCK_SHIFT;
	
	
	fuse_reply_statfs(req, &stat_buf);
}

static void fuse_ll_setxattr(fuse_req_t req, fuse_ino_t ino, const char* name,
				const char* value, size_t size, int flags)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_getxattr(fuse_req_t req, fuse_ino_t ino, const char* name,
				size_t size)
{
	cout << __func__  << " attr:" << string(name) << endl;
	fuse_reply_xattr(req, 0);
}

static void fuse_ll_listxattr(fuse_req_t req, fuse_ino_t ino, size_t size)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_removexattr(fuse_req_t req, fuse_ino_t ino, const char* name)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_access(fuse_req_t req, fuse_ino_t ino, int mask)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_create(fuse_req_t req, fuse_ino_t parent, const char* name, mode_t mode,
				struct fuse_file_info *fi)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_getlk(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi,
				struct flock *lock)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

static void fuse_ll_setlk(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi,
				struct flock *lock, int sleep)
{
	cout << __func__ << endl;
	fuse_reply_err(req, 0);
}

const static struct fuse_lowlevel_ops fuse_ll_oper = {
	init : fuse_ll_init,
	destroy : 0,
	lookup : fuse_ll_lookup,
	forget : fuse_ll_forget,
	getattr : fuse_ll_getattr,
	setattr : fuse_ll_setattr,
	readlink : fuse_ll_readlink,
	mknod : fuse_ll_mknod,
	mkdir : fuse_ll_mkdir,
	unlink : fuse_ll_unlink,
	rmdir : fuse_ll_rmdir,
	symlink : fuse_ll_symlink,
	rename : fuse_ll_rename,
	link : fuse_ll_link,
	open : fuse_ll_open,
	read : fuse_ll_read,
	write : fuse_ll_write,
	flush : fuse_ll_flush,
	release : fuse_ll_release,
	fsync : fuse_ll_fsync,
	opendir : fuse_ll_opendir,
	readdir : fuse_ll_readdir,
	releasedir : fuse_ll_releasedir,
	fsyncdir : fuse_ll_fsyncdir,
	statfs : fuse_ll_statfs,
	setxattr : fuse_ll_setxattr,
	getxattr : fuse_ll_getxattr,
	listxattr : fuse_ll_listxattr,
	removexattr : fuse_ll_removexattr,
	access : fuse_ll_access,
	create : fuse_ll_create,
	getlk : fuse_ll_getlk,
	setlk : fuse_ll_setlk,
	bmap : 0,
	ioctl : 0,
	poll : 0,
	write_buf : 0,
	retrieve_reply : 0,
	forget_multi : 0,
	flock : 0,
	fallocate : 0,
};

void FuseOp::exec()
{
	FuseHandle *handle = new FuseHandle();
	handle->init();
	delete handle;
	handle = NULL;
}

void FuseOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " fuse mount" << endl;
	cout << " fuse umount" << endl;
}

int FuseHandle::init()
{
	int fuse_argc = 2;
	char *fuse_argv[2];
    char *mountpoint;
	struct fuse_args args;
	struct fuse_chan *ch = NULL;
	struct fuse_session *se = NULL;

	fuse_argv[0] = "songzi";
	fuse_argv[1] = "/mnt/fuse";
	//fuse_argv[2] = "/mnt/fuse";
 	
	args = FUSE_ARGS_INIT(fuse_argc, fuse_argv);
	int r = fuse_parse_cmdline(&args, &mountpoint, NULL, NULL);
	if (r < 0) {
		cout << "Failed to fuse_parse_cmdline, r=" << r << endl;
		return r;
	}

	ch = fuse_mount(mountpoint, &args);
	if (!ch) {
		cout << "Failed to fuse_mount" << endl;
		return -1;
	}

	se = fuse_lowlevel_new(&args, &fuse_ll_oper, sizeof(fuse_ll_oper), this);
	if (!se) {
		cout << "Failed to fuse_lowlevel_new" << endl;
		return -1;
	}

	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (fuse_set_signal_handlers(se) == -1) {
		cout << "Failed to fuse_set_signal_handlers" << endl;
		return -1;
	}

	fuse_session_add_chan(se, ch);

	fuse_session_loop(se);

	if (se) {
		fuse_remove_signal_handlers(se);
	}
	if (ch) {
		fuse_session_remove_chan(ch);
	}
	if(se) {
		fuse_session_destroy(se);
	}
	if(ch) {
		fuse_unmount(mountpoint, ch);
	}
	return 0;
}

int FuseHandle::start()
{
	return 0;
}
