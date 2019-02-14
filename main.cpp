#include "command.hpp"
#include "common/common.hpp"

int main(int argc, char *argv[])
{
	struct Argument argument;
	int r = argument.parse(argc, argv);
	if (r < 0) {
		return r;
	}

	Command *command = new Command(&argument);
	command->execute();
	delete command;
	
	return 0;
}
