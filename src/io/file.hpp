#ifndef _SONGZI_FILE_H_
#define _SONGZI_FILE_H_

#include "op/op.hpp"
#include <string>

class FileOp : public Op {
private:
	std::string path;
public:
	FileOp(Argument *argument):Op(argument, "io", "test file io"){
			path = "/dev/sdl1";
	}
	void do_read();
	void do_write();
	virtual void exec();
	virtual void help();

};

#endif