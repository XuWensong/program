#include <iostream>
#include "bridge.hpp"

using namespace std;

BridgeInterface::~BridgeInterface()
{
	if (_imp) {
		delete _imp;
		_imp = NULL;
	}
}

void BridgeInterface::operation()
{
	_imp->operation();
}

void BridgeImplementA::operation()
{
	cout << "Implement in BridgeImplementA" << endl;
}

void BridgeImplementB::operation() {
	cout << "Implement in BridgeImplementB" << endl;
}