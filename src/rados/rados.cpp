#include "rados.hpp"
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <inttypes.h>

using namespace std;
using namespace librados;

int CephClient::rados_connect()
{
	if (!rados) {
		return -EINVAL;
	}

	int r = rados->init("rbd");
	if (r < 0) {
		cout << "Failed to init rados, return: " << r << std::endl;
		return r;
	}

	r = rados->conf_read_file(_conf.c_str());
	if (r < 0) {
		cout << "Failed to read configuration file: " << _conf <<
			", return: " << r << std::endl;
		return r;
	}

	r = rados->connect();
	if (r < 0) {
		cout << "Failed to connect to rados, return: " << r << std::endl;
		return r;
	}
	return 0;
}

int CephClient::proxy_connect()
{
	/*
	if (!rados_proxy) {
		return -EINVAL;
	}

	cout << "init rados_proxy" << std::endl;
	int r = rados_proxy->init(NULL);
	if (r < 0) {
		cout << "Failed to init rados proxy" << std::endl;
		return r;
	}

	r = rados_proxy->conf_read_file("/etc/ceph/ceph.conf");
	if (r < 0) {
		cout << "Failed to read conf file for rados_proxy" << std::endl;
		return r;
	}
	
	cout << "connect rados_proxy" << std::endl;
	r = rados_proxy->connect();
	if (r < 0) {
		cout << "Failed to connect to rados proxy" << std::endl;
		return r;
	}
	*/
	return 0;
}

int CephClient::open_ioctx(string pool)
{
	if (!rados) {
		return -EINVAL;
	}

	int r = rados->ioctx_create(pool.c_str(), ioctx);
	if (r < 0) {
		cout << "Failed to create ioctx for pool:" << pool << ", return:" << r << std::endl;
		return r;
	}
	
	return 0;
}

int CephClient::write()
{
	ObjectWriteOperation op;
	bufferlist bl;
	string object = "data";
	string pool = "songzi";
	int r = rados_connect();
	if (r < 0) {
		return r;
	}

	r = open_ioctx(pool);
	if (r < 0) {
		return r;
	}
	
	//op.create(true);
	op.write_full(bl);
	
	r = ioctx.operate(object.c_str(), &op);
	if (r < 0) {
		cout << "Failed to write data, return: " << r << std::endl;
		return r;
	}

	return 0;
}

int CephClient::read()
{
	uint64_t size = 0;
	ObjectReadOperation op_stat, op_read;
	bufferlist bl;
	string object = "data";
	string pool = "songzi";

	int r = rados_connect();
	if (r < 0) {
		return r;
	}

	r = open_ioctx(pool);
	if (r < 0) {
		return r;
	}

	op_stat.stat(&size, NULL, NULL);
	r = ioctx.operate(object.c_str(), &op_stat, NULL);
	if (r < 0) {
		cout << "Failed to get status of object:" << object << ", return:" << r << std::endl;
		return r;
	}

	op_read.read(0, size, &bl, NULL);
	
	r = ioctx.operate(object.c_str(), &op_read, NULL);
	if (r < 0) {
		cout << "Failed to read object:" << object << ", return:" << r << std::endl;
		return r;
	}

	bl.write_file("/home/songzi/program/dest");

	return 0;
}

int CephClient::print_inotable(string table_name)
{
	/*
	bufferlist bl;
	InoTable ino_table(NULL);

	int r = read(table_name, bl);
	if (r < 0) {
		return r;
	}

	bufferlist::iterator iter = bl.begin();
	ino_table.decode(iter);
	*/
	
	
	return 0;
}

int CephClient::proxy_read()
{
/*
	int poolid = 1; // the id of pool "songzi" is 1
	string prefix = "proxy_data_prefix_";
	uint64_t len = 4 * 1024 * 1024;
	
	string dest_file = "/home/songzi/program/proxy_dest";
	librados::bufferlist out;
	
	int r = proxy_connect();
	if (r < 0) {
		cout << "proxy_connect return " << r << std::endl;
		return r;
	}

	for (int i = 0; i < 1; i++) {
		uint64_t off = 0;
		cout << "round " << i << endl;
		stringstream ss;
		ss << i;
		string p;
		ss >> p;
		string oid = prefix + p;
		while (off < len) {
			uint64_t l = 100 * 1024;
			r = rados_proxy->aio_read(poolid, oid, off, l, out, c);
			if (r < 0) {
				cout << "rados_proxy aio_read failed, r=" << r << std::endl;
				return r;
			}
			c->wait_for_complete();
			off += (l + 1);
		}
	}
*/
	return 0;
}

int CephClient::proxy_write()
{
/*
	int poolid = 1; // the id of pool "songzi" is 1
	string prefix = "proxy_data_prefix_";
	
	string src_file = "/home/songzi/program/proxy_src";
	bufferlist in;
	int r = proxy_connect();
	if (r < 0) {
		cout << "proxy_connect return " << r << std::endl;
		return r;
	}

	in.read_file(src_file.c_str(), NULL);

	for (int i = 0; i < 1; i++) {
		uint64_t off = 0;
		cout << "round " << i << endl;
		stringstream ss;
		ss << i;
		string p;
		ss >> p;
		string oid = prefix + p;
		uint64_t l = 4 * 1024 * 1024;
		while (off + l <= in.length()) {
			
			bufferlist bl;
			bl.substr_of(in, off, l);
			r = rados_proxy->aio_write(poolid, oid, off, bl, c);
			if (r < 0) {
				cout << "rados_proxy aio_read failed, r=" << r << std::endl;
				return r;
			}
			c->wait_for_complete();
			off += (l + 1);
		}
	}
*/
	return 0;
}

int CephClient::rbd_write()
{
	string pool = "songzi";
	string image_name = "image0";
	librbd::RBD rbd;
	librbd::Image image;
	string data = "1234567890";
	int offset = 0;

	int r = rados_connect();
	if (r < 0) {
		return r;
	}

	r = open_ioctx(pool);
	if (r < 0) {
		return r;
	}

	r = rbd.open(ioctx, image, image_name.c_str());
	if (r < 0) {
		cout << "Failed to open image " << image_name << std::endl;
		return r;
	}

	cout << "Open image " << image_name << " successfully" << std::endl;
	for (int i = 0; i < 10; i++) {
		librados::bufferlist data_bl;
		//data_bl.append(data.c_str());
		data_bl.read_file("/home/songzi/program/data", NULL);
		r = image.write(offset, data_bl.length(), data_bl);
		cout << "Write image offset:"<< offset <<  ", return " << r << std::endl;
		offset += data_bl.length();
	}

	r = image.close();
	if (r < 0) {
		cout << "Failed to close image " << image_name << std::endl;
		return r;
	}
	return 0;
}

int CephClient::rbd_read()
{
	return 0;
}

void RadosOp::exec()
{
	string conf = argument->get("conf", "/etc/ceph/ceph.conf");
	string pool = argument->get("pool", "songzi");
	
	CephClient *rc = new CephClient(conf);

	int sub_cmd = argument->get_sub_cmd();
	switch (sub_cmd) {
		case SUB_CMD_READ:{
			rc->read();
			break;
		}
		case SUB_CMD_WRITE: {
			rc->write();
			break;
		}
	}

	if (rc) {
		delete rc;
		rc = NULL;
	}
	return;
}

void RadosOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " rados read" << endl;
	cout << " rados write" << endl;
	cout << "Options:" << endl;
	cout << " --conf    config file for rados" << endl;
	cout << " --file    local file to read or write" << endl;
	cout << " --pool    the name of rados pool" << endl;
	cout << " --object  the name of rados object" << endl;
	cout << " --outfile the file data write to" << endl;
}

void RBDOp::exec()
{
	string conf = argument->get("conf", "/etc/ceph/ceph.conf");
	string pool = argument->get("pool", "songzi");
	
	CephClient *rc = new CephClient(conf);

	int sub_cmd = argument->get_sub_cmd();
	switch (sub_cmd) {
		case SUB_CMD_READ:{
			rc->rbd_read();
			break;
		}
		case SUB_CMD_WRITE: {
			rc->rbd_write();
			break;
		}
	}

	if (rc) {
		delete rc;
		rc = NULL;
	}
	return;
}

void RBDOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " rbd read" << endl;
	cout << " rbd write" << endl;
	cout << "Options:" << endl;
	cout << " --conf    config file for rados" << endl;
	cout << " --file    local file to read or write" << endl;
	cout << " --pool    the name of rados pool" << endl;
	cout << " --image   the name of image" << endl;
	cout << " --outfile the file data write to" << endl;
	cout << " --infile  the file data read from" << endl;
}

void ProxyOp::exec()
{

}

void ProxyOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " proxy read" << endl;
	cout << " proxy write" << endl;
	cout << "Options:" << endl;
	cout << " --conf    config file for rados" << endl;
	cout << " --file    local file to read or write" << endl;
	cout << " --pool    the name of rados pool" << endl;
	cout << " --object  the name of rados object" << endl;
	cout << " --outfile the file data write to" << endl;
}
