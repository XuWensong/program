#ifndef SONGZI_SYMLINK_H
#define SONGZI_SYMLINK_H

#include "op/op.hpp"

class SymlinkOp : public Op {
public:
	SymlinkOp(Argument *argument):Op(argument, "symlink", "test symlink operation") {}
	~SymlinkOp(){}

	virtual void exec();
	virtual void help();
};

#endif
