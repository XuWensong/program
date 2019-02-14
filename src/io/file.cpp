#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <malloc.h>
#include <memory.h>

#include "file.hpp"

using namespace std;

void FileOp::exec()
{ 
	return;
}

void FileOp::help()
{
}

void FileOp::do_read()
{
	string data;
	int buffer_size = 1024;
	string path = "/mnt/songzi";
	char *buffer = (char *)malloc(sizeof(char) * buffer_size);
	int fd = open(path.c_str(), O_RDONLY | O_CREAT);
	if (fd < 0) {
		cout << "Failed to open file, return:" << fd << endl;
		return;
	}

	int len = 0;
	memset(buffer, 0, buffer_size);
	while (len = read(fd, buffer, buffer_size) > 0) {
		data.append(buffer);
		memset(buffer, 0, buffer_size);
		break;
	}

	close(fd);
	free(buffer);
	cout << "Read:" << data << endl;
	return;
	
}

void FileOp::do_write()
{
	string data = "Just a test";
	path = "/mnt/songzi";
	//int fd = open(path.c_str(), O_DIRECTORY);
	int fd = ::open(path.c_str(), O_WRONLY);
	if (fd < 0) {
		cout << "Failed to open file, return:" << fd << endl;
		return;
	}
	
	int r = write(fd, data.c_str(), data.length());
	if (r < 0) {
		cout << "Failed to write data, return: " << r << endl;
		close(fd);
		return;
	}

	close(fd);
	cout << "Write return:" << r << endl;
	return;
}

