#ifndef SONGZI_INTERVAL_SET_OP_H
#define SONGZI_INTERVAL_SET_OP_H
#include "op/op.hpp"
#include "common/IntervalSet.h"

class IntervalSetOp : public Op {
public:
	IntervalSetOp(Argument *arg):Op(arg, "interval-set", "test implements of IntervalSet"){}
	~IntervalSetOp(){}

	void exec();
	void help();
};

#endif
