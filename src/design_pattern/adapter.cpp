#include "adapter.hpp"

#include <iostream>

using namespace std;

Adapter::~Adapter()
{
	if (adaptee) {
		delete adaptee;
		adaptee = NULL;
	}
}

void Adapter::operation()
{
	cout << "operation in Adapter" << endl;
	adaptee->do_operation();
}

void Adaptee::do_operation()
{
	cout << "do_operation in Adaptee" << endl;
}