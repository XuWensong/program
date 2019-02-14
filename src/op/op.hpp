#ifndef _OP_H_
#define _OP_H_

#include <string>

#include "common/common.hpp"

class Op {
protected:
	Argument *argument;
	std::string name;
	std::string description;
public:
	Op(Argument *arg):argument(arg), name("help"), description("show this message"){}
	Op(Argument *arg, std::string n, std::string desc):argument(arg), name(n), 
		description(desc){}
	virtual ~Op(){}

	std::string get_name() {return name;}
	virtual void usage();
 	virtual void exec() = 0;
	virtual void help() = 0;
};

#endif
