#ifndef _SONGZI_BOOST_PTR_H_
#define _SONGZI_BOOST_PTR_H_

#include <iostream>
#include <string>

#include "op/op.hpp"

using namespace std;


class PtrInstance {
public:
	PtrInstance(){std::cout << "PtrInstance construct" << std::endl;}
	~PtrInstance(){std::cout << "PtrInstance destruct" << std::endl;}
};

class RemoveOnDelete {
public:
	RemoveOnDelete(){}
	void operator()(PtrInstance *instance){
		if (instance) {
			delete instance;
			instance = NULL;
		}
	}
};


class IntrusivePtrInstance{
private:
	int ref;
	string name;
public:
	IntrusivePtrInstance(string n):ref(0), name(n) {
		cout << "Construct IntrusiveInstance:" << name << endl;
	}
	~IntrusivePtrInstance() {
		cout << "Release IntrusiveInstance:" << name << endl;
	}

	void get(){
		ref++;
		cout << "Get IntrusiveInstance ref:" << name << endl;
	}
	void put(){
		ref--;
		cout << "Put IntrusiveInstance ref:" << name << endl;
		return;
		if(!ref) {
			delete this;
		}
	}
	int ref_count() {return ref;}
	string get_name() {return name;}
};

void intrusive_ptr_add_ref(IntrusivePtrInstance *p);
void intrusive_ptr_release(IntrusivePtrInstance *p);

class SmartPtrOp : public Op {
public:
	SmartPtrOp(Argument *argument):Op(argument, "smartptr", "test smart pointer"){}
	virtual void exec();
	virtual void help();
	void shared_ptr_test();
	void intrusive_ptr_test();
};

#endif
