#include <iostream>
#include <sstream>
#include <string.h>

#include "common/Journaler.h"
#include "bufferlist.hpp"

using namespace std;

void Data::print()
{
	cout << "m_name: " << m_name << endl;
	cout << "m_id: " << m_id << endl;
	cout << "m_l: " << endl;
	for (list<string>::iterator it = m_l.begin(); it != m_l.end(); it++)
		cout << *it << endl;

	cout << "m_m: " << endl;
	for(map<int, string>::iterator it = m_m.begin(); it != m_m.end(); it++)
		cout << it->first << " " << it->second << endl;

	cout << "m_v: " << endl;
	for(vector<string>::iterator it = m_v.begin(); it != m_v.end(); it++)
		cout << *it << endl;
		
}

void Data::encode(bufferlist &bl)
{
	ENCODE_START(100, 0, bl);
	::encode(m_name, bl);
	::encode(m_id, bl);
	::encode(m_l, bl);
	::encode(m_m, bl);
	::encode(m_v, bl);
}

void Data::decode(bufferlist::iterator &bl)
{
	DECODE_START(1, bl);
	::decode(m_name, bl);
	::decode(m_id, bl);
	::decode(m_l, bl);
	::decode(m_m, bl);
	::decode(m_v, bl);
}

void BufferOp::exec()
{
	switch(argument->get_sub_cmd()) {
		case SUB_CMD_BUFFERLIST:
			test_bufferlist();
			break;
		case SUB_CMD_JOURNALER:
			test_journaler();
			break;
		default:
			return;
	}

}

void BufferOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " bufferlist       test bufferlist dencoding" << endl;
	cout << " journaler        test journaler implement" << endl;
}

void BufferOp::test_bufferlist()
{
	bufferlist bl, nbl;
	Data d, nd;
	d.m_name = "Data";
	d.m_id = 1022;
	d.m_l.push_back("first");
	d.m_l.push_back("second");
	d.m_l.push_back("third");
	d.m_m[0] = "first";
	d.m_m[1] = "second";
	d.m_m[2] = "third";
	d.m_v.push_back("first");
	d.m_v.push_back("second");
	d.m_v.push_back("third");

	d.print();
	::encode(d, bl);
	string data(bl.c_str(), bl.length());
	nbl.append(data);

	cout << "\n\n\n" << endl;
	cout << "nbl.length() = " << nbl.length() << endl;
	bufferlist::iterator it = nbl.begin();
	::decode(nd, it);
	nd.print();
	
}

void BufferOp::test_journaler()
{
	string log_path = "/home/songzi/github/program/src/journaler";
	bufferlist data_bl;
	
	Journaler journaler;
	journaler.open(log_path);

	for (int i = 0; i < 3; i++) {
		Data d;
		bufferlist bl;
		string name;
		stringstream ss;
		ss << "data";
		ss << i;
		name = ss.str();

		d= fake_data(name);
		::encode(d, bl);
		int r = journaler.append_entry(bl);
		if (r < 0) {
			cout << "failed to append_entry" << endl;
		}
	}

	while (true) {
		bufferlist bl;
		Data d;
		if (!journaler.try_read_entry(bl))
			break;

		bufferlist::iterator p = bl.begin();
		::decode(d, p);
		d.print();
		journaler.flushed(bl.length());
		break;
	}

	journaler.close();
}

Data BufferOp::fake_data(string name)
{
	Data d;
	d.m_name = name;
	d.m_id = 1022;
	d.m_l.push_back("first");
	d.m_l.push_back("second");
	d.m_l.push_back("third");
	d.m_m[0] = "first";
	d.m_m[1] = "second";
	d.m_m[2] = "third";
	d.m_v.push_back("first");
	d.m_v.push_back("second");
	d.m_v.push_back("third");

	return d;
}