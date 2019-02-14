#ifndef _SONGZI_RADOS_H_
#define _SONGZI_RADOS_H_

#include <rados/librados.hpp>
#include <rbd/librbd.hpp>
//#include <radosproxy/libproxy.hpp>
#include <string>
#include "op/op.hpp"

struct RadosData {
	
};

class CephClient {
private:
	std::string _conf;
	librados::Rados *rados;
	librados::IoCtx ioctx;
	librados::bufferlist bl;
	//libproxy::RadosProxy *rados_proxy;
	//libproxy::AioCompletion *c;
	librbd::RBD *rbd;
public:
	CephClient(std::string conf):_conf(conf){
		rados = new librados::Rados();
		//rados_proxy = new libproxy::RadosProxy();
		//c = new libproxy::AioCompletion();
		bl.append("1234");
	}
	~CephClient() {
		if (rados) {
			delete rados;
			rados = NULL;
		}
		/*
		if (rados_proxy) {
			delete rados_proxy;
			rados_proxy = NULL;
		}
		if (c) {
			delete c;
			c = NULL;
		}
		*/
	}
	int rados_connect();
	int proxy_connect();
	int open_ioctx(std::string pool);
	int write();
	int read();
	int print_inotable(std::string table_name);
	int proxy_read();
	int proxy_write();
	int rbd_write();
	int rbd_read();
};

class RadosOp : public Op {
public:
	RadosOp(Argument *argument):Op(argument, "rados", "test rados interface"){}
	~RadosOp() {}
	virtual void exec();
	virtual void help();
};

class RBDOp : public Op {
public:
	RBDOp(Argument *argument):Op(argument, "rbd", "test rbd interface"){}
	~RBDOp(){}
	virtual void exec();
	virtual void help();
};

class ProxyOp : public Op {
public:
	ProxyOp(Argument *argument):Op(argument, "proxy", "test ceph-proxy interface"){}
	~ProxyOp(){}
	virtual void exec();
	virtual void help();
};

#endif
