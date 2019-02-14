#ifndef SONGZI_ADAPTER_H
#define SONGZI_ADAPTER_H
#include<unistd.h>

/**
* When you defined interfaces are not compatible with the third Class interface,
* you can use Adapter Pattern. You can let you Adapter herit from the third class,
* or let the third class be one member of your Adapter
**/

class AdapterBase {
public:
	AdapterBase(){}
	virtual ~AdapterBase(){}

	virtual void operation() = 0;
};

//the third class
class Adaptee;

//let the third class be one member of Adapter
class Adapter : public AdapterBase {
private:
	Adaptee *adaptee;
public:
	Adapter(Adaptee *adp):adaptee(adp){}
	~Adapter();

	virtual void operation();
};

class Adaptee {
public:
	Adaptee(){}
	~Adaptee(){}

	void do_operation();
};

#endif
