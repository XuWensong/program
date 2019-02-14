#include "singleton.hpp"

Singleton* Singleton::_instance = 0;

Singleton* Singleton::instance()
{
	if (!_instance) {
		_instance = new Singleton();
	} 
	return _instance;
}

