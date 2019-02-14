#ifndef _AIO_H_
#define _AIO_H_

#include <string>

#include "op/op.hpp"

class AioOp : public Op{
private:
	std::string path;
	void read();
	void write();
public:
	AioOp(Argument *argument):Op(argument, "aio", "test aio interface"){
		path = "/home/songzi/program/src/io/data";
	}
	~AioOp(){}
	virtual void exec();
	virtual void help();
};

#endif
