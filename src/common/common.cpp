#include "common.hpp"

#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

int Argument::parse_cmd(int argc, char *argv[])
{
	if (argc < 1) {
		cout << "No Command specified" << endl;
		return -EINVAL;
	}else if (argc == 1) {
		cmd = CMD_USAGE;
		return 0;
	}

	string cmd_type(argv[1]);
	if (strcmp(cmd_type.c_str(), "help") == 0) {
		if (argc <= 2) {
			cmd = CMD_USAGE;
		} else {
			cmd = CMD_HELP;
			cmd_name = string(argv[2]);
		}
	} else if (strcmp(cmd_type.c_str(), "io") == 0) {
		cmd = CMD_IO;
	} else if (strcmp(cmd_type.c_str(), "aio") == 0) {
		cmd = CMD_AIO;
	} else if (strcmp(cmd_type.c_str(), "leveldb") == 0) {
		cmd = CMD_LEVELDB;
	} else if (strcmp(cmd_type.c_str(), "smartptr") == 0) {
		cmd = CMD_SMART_POINTER;
	} else if (strcmp(cmd_type.c_str(), "rados") == 0) {
		cmd = CMD_RADOS;
	} else if (strcmp(cmd_type.c_str(), "proxy") == 0) {
		cmd = CMD_PROXY;
	} else if (strcmp(cmd_type.c_str(), "rbd") == 0) {
		cmd = CMD_RBD;
	} else if (strcmp(cmd_type.c_str(), "dp") == 0) {
		cmd = CMD_DESIGN_PATTERN;
	} else if (strcmp(cmd_type.c_str(), "statechart") == 0) {
		cmd = CMD_STATECHART;
	} else if (strcmp(cmd_type.c_str(), "symlink") == 0) {
		cmd = CMD_SYMLINK;
	} else if (strcmp(cmd_type.c_str(), "fuse") == 0) {
		cmd = CMD_FUSE;
	} else if (strcmp(cmd_type.c_str(), "algorithm") == 0) {
		cmd = CMD_ALGORITHM;
	} else if (strcmp(cmd_type.c_str(), "binarytree") == 0) {
		cmd = CMD_BINARY_TREE;
	} else if (strcmp(cmd_type.c_str(), "bufferlist") == 0) {
		cmd = CMD_BUFFERLIST;
	} else if (!strcmp(cmd_type.c_str(), "interval-set")) {
		cmd = CMD_INTERVAL_SET;
	} else if (!strcmp(cmd_type.c_str(), "kernel")) {
		cmd = CMD_KERNEL;
	}
	else {
		cout << "Not supported Command:" << cmd_type << endl;
		return -EINVAL;
	}
	return 0;
}

int Argument::parse_sub_cmd(int argc, char *argv[])
{
	if (argc < 3) {
		cout << "No Sub-Command specified" << endl;
		return -EINVAL;
	}

	string sub_cmd_type(argv[2]);
	if (strcmp(sub_cmd_type.c_str(), "test") == 0) {
		sub_cmd = SUB_CMD_TEST;
	} else if (strcmp(sub_cmd_type.c_str(), "read") == 0) {
		sub_cmd = SUB_CMD_READ;
	} else if (strcmp(sub_cmd_type.c_str(), "write") == 0) {
		sub_cmd = SUB_CMD_WRITE;
	} else if (strcmp(sub_cmd_type.c_str(), "delete") == 0) {
		sub_cmd = SUB_CMD_DELETE;
	} else if (strcmp(sub_cmd_type.c_str(), "list") == 0) {
		sub_cmd = SUB_CMD_LIST;
	} else if (strcmp(sub_cmd_type.c_str(), "share") == 0) {
		sub_cmd = SUB_CMD_SHARE;
	} else if (strcmp(sub_cmd_type.c_str(), "intrusive") == 0) {
		sub_cmd = SUB_CMD_INTRUSIVE;
	} else if (strcmp(sub_cmd_type.c_str(), "factory") == 0) {
		sub_cmd = SUB_CMD_FACTORY;
	} else if (strcmp(sub_cmd_type.c_str(), "abstract-factory") == 0) {
		sub_cmd = SUB_CMD_ABSTRACT_FACTORY;
	} else if (strcmp(sub_cmd_type.c_str(), "builder") == 0) {
		sub_cmd = SUB_CMD_BUILDER;
	} else if (strcmp(sub_cmd_type.c_str(), "prototype") == 0) {
		sub_cmd = SUB_CMD_PROTOTYPE;
	} else if (strcmp(sub_cmd_type.c_str(), "singleton") == 0) {
		sub_cmd = SUB_CMD_SINGLETON;
	} else if (strcmp(sub_cmd_type.c_str(), "bridge") == 0) {
		sub_cmd = SUB_CMD_BRIDGE;
	} else if (strcmp(sub_cmd_type.c_str(), "adapter") == 0) {
		sub_cmd = SUB_CMD_ADAPTER;
	} else if (strcmp(sub_cmd_type.c_str(), "mount") == 0) {
		sub_cmd = SUB_CMD_MOUNT;
	} else if (strcmp(sub_cmd_type.c_str(), "bufferlist") == 0) {
		sub_cmd = SUB_CMD_BUFFERLIST;
	} else if (strcmp(sub_cmd_type.c_str(), "journaler") == 0) {
		sub_cmd = SUB_CMD_JOURNALER;
	} else if (!strcmp(sub_cmd_type.c_str(), "containerof")) {
		sub_cmd = SUB_CMD_CONTAINEROF;
	}
	else {
		cout << "Not supported Sub-Command:" << sub_cmd_type << endl;
		return -EINVAL;
	}
	return 0;
}

int Argument::parse_args(int argc, char *argv[])
{
	if (argc <= 3) {
		return 0;
	}

	for (int i = 3; i < argc; i++) {
		string key(argv[i]);
		string prefix;
		string value;

		if (key.length() >= 2) {
			prefix = key.substr(0, 2);
		}

		if (strcmp(prefix.c_str(), "--") == 0) {
			i++;
			if (i >= argc) {
				cout << "No matched value for " << key << endl;
				return -EINVAL;
			}
			key = key.substr(2, key.length() - 2);
			value = string(argv[i]);
			
		} else if (key.find_first_of("=")) {
			int pos = key.find_first_of("=");
			value = key.substr(pos + 1, key.length() - (pos + 1));
			key = key.substr(0, pos);
		}
		if (key.empty() || value.empty()) {
			cout << "Key or Value is empty" << endl;
			return -EINVAL;
		}
		
		args[key] = value;
	}
}

int Argument::parse(int argc, char *argv[])
{
	int r = parse_cmd(argc, argv);
	if (r < 0) {
		cout << "Faile to parse_cmd" << endl;
		return r;
	}

	if (cmd == CMD_USAGE || cmd == CMD_HELP) {
		return 0;
	}

	r = parse_sub_cmd(argc, argv);
	if (r < 0) {
		cout << "Failed to parse_sub_cmd" << endl;
		return r;
	}

	r = parse_args(argc, argv);
	if (r < 0) {
		cout << "Failed to parse_args" << endl;
		return r;
	}
	return 0;
}

string Argument::get(string key, string def)
{
	if (args.count(key)) {
		return args[key];
	} else {
		return def;
	}
}

mtime songzi_clock_now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	mtime n(&tv);
	return n;
}