#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "common/mtime.hpp"

enum {
	CMD_USAGE = 0,
	CMD_HELP,
	CMD_IO,
	CMD_AIO,
	CMD_LEVELDB,
	CMD_SMART_POINTER,
	CMD_RADOS,
	CMD_PROXY,
	CMD_RBD,
	CMD_DESIGN_PATTERN,
	CMD_STATECHART,
	CMD_SYMLINK,
	CMD_FUSE,
	CMD_ALGORITHM,
	CMD_BINARY_TREE,
};

enum {
	SUB_CMD_TEST = 0,
	SUB_CMD_READ,
	SUB_CMD_WRITE,
	SUB_CMD_DELETE,
	SUB_CMD_LIST,
	SUB_CMD_SHARE,
	SUB_CMD_INTRUSIVE,
	SUB_CMD_FACTORY,
	SUB_CMD_ABSTRACT_FACTORY,
	SUB_CMD_BUILDER,
	SUB_CMD_PROTOTYPE,
	SUB_CMD_SINGLETON,
	SUB_CMD_BRIDGE,
	SUB_CMD_ADAPTER,
	SUB_CMD_MOUNT,
};


using namespace std;

struct Argument {
private:
	int cmd;
	int sub_cmd;
	string cmd_name;
	map<string, string> args;

	int parse_cmd(int argc, char *argv[]);
	int parse_sub_cmd(int argc, char *argv[]);
	int parse_args(int argc, char *argv[]);
public:
	Argument():cmd(CMD_HELP), sub_cmd(SUB_CMD_TEST){}
	int parse(int argc, char *argv[]);
	int get_cmd() {return cmd;}
	int get_sub_cmd() {return sub_cmd;}
	string get_cmd_name() {return cmd_name;}
	string get(string key, string def="");
	bool have(string key){
		return args.count(key) != 0;
	}
};

mtime songzi_clock_now();


#endif
