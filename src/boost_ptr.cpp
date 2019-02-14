#include "boost_ptr.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>

using namespace std;
typedef boost::shared_ptr<PtrInstance> Instance;
typedef boost::intrusive_ptr<IntrusivePtrInstance> IntrusiveInstanceRef;

void intrusive_ptr_add_ref(IntrusivePtrInstance *p)
{
	p->get();
}

void intrusive_ptr_release(IntrusivePtrInstance *p)
{
	p->put();
}

void SmartPtrOp::exec() {
	int sub_cmd = argument->get_sub_cmd();
	switch (sub_cmd) {
		case SUB_CMD_SHARE:
			shared_ptr_test();
			break;
		case SUB_CMD_INTRUSIVE:
			intrusive_ptr_test();
			break;
	}
}

void SmartPtrOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " smartptr share" << endl;
	cout << " smartptr intrusive" << endl;
}

void SmartPtrOp::shared_ptr_test()
{
	Instance ins = Instance();
	//Instance ins(new PtrInstance);
	
	if (!ins) {
		cout << "shared_ptr is NULL without true instance" << endl;
	}
	{
		PtrInstance *ptr_instance = new PtrInstance();
		Instance ins1 = Instance(ptr_instance, RemoveOnDelete());
		if (ins1) {
			cout << "shared_ptr is not NULL with true instance" << endl;
		}

		cout << "shared_ptr will auto release at the end of lifecycle" << endl;
		
	}
	{
		PtrInstance *ptr_instance = new PtrInstance();
		Instance ins1 = Instance(ptr_instance, RemoveOnDelete());
		if (!ins1) {
			return;
		}

		ins = ins1;
		cout << "shared_ptr will not auto release with new reference" << endl;
	}

	cout << "shared_ptr will auto release while all reference compelete lifecycle" << endl;
	return;
}

void test_intrusive_arg(IntrusiveInstanceRef p)
{
	//IntrusiveInstanceRef p1(new IntrusivePtrInstance("test"));
	//p = p1;
	p->ref_count();
}

class TestSmartPtrOp{
private:
	IntrusiveInstanceRef ptr;
public:
	
	TestSmartPtrOp(IntrusivePtrInstance *p):ptr(p){}
	~TestSmartPtrOp(){};

	void complete(){
		ptr.reset();
		//delete this;
	}
};

void SmartPtrOp::intrusive_ptr_test()
{
	IntrusiveInstanceRef ins = IntrusiveInstanceRef();
	if (ins == NULL) {
		cout << "No instance" << endl;
	}
	IntrusivePtrInstance *b = new IntrusivePtrInstance("first");
	//IntrusiveInstanceRef p(b);
	//IntrusiveInstanceRef p1(b);
	//p.reset();
	//cout << p1->get_name() << endl;
	
	//TestSmartPtrOp t(b);
	//p.reset();
	//IntrusiveInstanceRef p1(new IntrusivePtrInstance("second"));
	TestSmartPtrOp t(b);
	//t.complete();
	//p1 = p;
	//return;
	

	//IntrusiveInstanceRef p;
	//wtest_intrusive_arg(p);
	cout << __func__ << " end" << endl;
	return;
}
