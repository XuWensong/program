#ifndef SONGZI_SINGLETON_H
#define SONGZI_SINGLETON_H

/**
* Singleton is used to create the unique instance for a class
**/

class Singleton {
private:
	
	Singleton() {}
public:
	static Singleton* _instance;

	~Singleton() {
		if(_instance) {
			delete _instance;
			_instance = 0;
		}
	}

	static Singleton* instance();
};

#endif
