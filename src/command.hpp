#ifndef SONGZI_COMMAND_H
#define SONGZI_COMMAND_H

#include <map>
#include <string>

#include "command.hpp"

class Op;
class Argument;

class Command {
private:
	Argument *argument;
	std::map<int, Op*> ops;
public:
	Command(Argument *args);
	~Command();
	void execute();
private:
	void usage();
	void help();
};

#endif
