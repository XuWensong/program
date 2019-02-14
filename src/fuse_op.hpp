#ifndef SONGZI_FUSE_OP_H
#define SONGZI_FUSE_OP_H

#include "op/op.hpp"

#define FUSE_USE_VERSION 30
#include <fuse.h>
#include <fuse/fuse_lowlevel.h>

class FuseOp : public Op {
public:
	FuseOp(Argument *arg):Op(arg, "fuse", "test interface for fuse"){}
	~FuseOp(){}

	virtual void exec();
	virtual void help();
};

class FuseHandle {
public:
	FuseHandle(){}
	~FuseHandle(){}

	int init();
	int start();
private:
	struct fuse_args m_fuse_args;
};

#endif
