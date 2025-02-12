#include "command.hpp"
#include "common/common.hpp"

#include "op/op.hpp"
#include "design_pattern.hpp"
#include "level_db.hpp"
#include "state_chart.hpp"
#include "symlink.hpp"
#include "io/file.hpp"
#include "io/aio.hpp"
#include "symlink.hpp"
#include "boost_ptr.hpp"
#include "fuse_op.hpp"
#include "algorithm.hpp"
#include "tree/binary_tree.hpp"
#include "bufferlist.hpp"
#include "interval_set_op.h"
#include "kernel_op.h"

using namespace std;

Command::Command(Argument *args):argument(args)
{
	ops[CMD_SMART_POINTER] = new SmartPtrOp(args);
	ops[CMD_FUSE]          = new FuseOp(args);
	ops[CMD_ALGORITHM]     = new AlgorithmOp(args);
	ops[CMD_BINARY_TREE]   = new BinaryTreeOp(args);
	ops[CMD_STATECHART]    = new StateMachineOp(args);
	ops[CMD_BUFFERLIST]    = new BufferOp(args);
	ops[CMD_INTERVAL_SET]  = new IntervalSetOp(args);
	ops[CMD_LEVELDB]       = new LevelDBOp(args);
	ops[CMD_KERNEL]        = new KernelOp(args);
}

Command::~Command()
{
	map<int, Op*>::iterator iter = ops.begin();
	for(; iter != ops.end(); iter++) {
		delete iter->second;
		iter->second = NULL;
	}
	ops.clear();
}

void Command::execute()
{
	int cmd = argument->get_cmd();
	if (cmd == CMD_USAGE) {
		usage();
		return;
	}

	if (cmd == CMD_HELP) {
		help();
		return;
	}
	if (ops.count(cmd)) {
		Op *op = ops[cmd];
		op->exec();
	}
}

void Command::usage()
{
	map<int, Op*>::iterator iter = ops.begin();
	for(; iter != ops.end(); iter++) {
		iter->second->usage();
	}
}

void Command::help()
{
	string cmd_name = argument->get_cmd_name();
	map<int, Op*>::iterator iter = ops.begin();
	for(; iter != ops.end(); iter++) {
		if (cmd_name == iter->second->get_name()) {
			iter->second->help();
		}
	}
}


