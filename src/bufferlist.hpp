#ifndef SONGZI_BUFFERLIST_H
#define SONGZI_BUFFERLIST_H

#include "op/op.hpp"
#include "common/Encoding.h"

struct Data {
	std::string m_name;
	uint64_t m_id;
	std::list<std::string> m_l;
	std::map<int, std::string> m_m;
	std::vector<std::string> m_v;

	void print();
	void encode(bufferlist &bl);
	void decode(bufferlist::iterator &bl);
};
WRITE_CLASS_ENCODER(Data);

class BufferOp : public Op{
public:
	BufferOp(Argument *arg):Op(arg, "bufferlist", "test buffer::list implements"){}
	~BufferOp(){}

	void exec();
	void help();
private:
	void test_bufferlist();
	void test_journaler();
	Data fake_data(std::string name);
};
#endif
