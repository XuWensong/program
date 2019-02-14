#include "symlink.hpp"

#include <unistd.h>
#include <string>
#include <iostream>

using namespace std;

void SymlinkOp::exec()
{
	string actual_path = "/dev/disk/by-partuuid/cbedfeb9-4a55-4478-9079-a89d7557e7e3";
	string sym_path = "/mnt/songzi";
	int r = symlink(actual_path.c_str(), sym_path.c_str());
	if (r < 0) {
		cout << "Failed to create symlink" << std::endl;
	}
	cout << "create symlink successfully" << endl;
}

void SymlinkOp::help()
{
}