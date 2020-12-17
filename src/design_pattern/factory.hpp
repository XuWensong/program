#ifndef SONGZI_FACTORY_H
#define SONGZI_FACTORY_H
#include <iostream>

using namespace std;

/**
* In Factory pattern, the caller does not know the concrete name of subclass,
* but Factory know the name, so Factory offers the interface to create concrete class
**/


class AbstractProduct;

class Factory {
public:
	Factory(){}
	~Factory(){}

	AbstractProduct* create_product(std::string product);
};


class ProductA;
class ProductB;
class AbstractProduct{
private:
	string name;
	friend class ProductA;
	friend class ProductB;
	//AbstractProduct can not be instantiated
	AbstractProduct(string n):name(n){
		cout << "create " << name << endl;
	}
public:
	~AbstractProduct(){}
	
};

class ProductA : public AbstractProduct {
public:
	ProductA():AbstractProduct("ProductA"){}
	~ProductA(){}
};

class ProductB : public AbstractProduct {
public:
	ProductB():AbstractProduct("ProductB"){}
	~ProductB(){}
};

class TV {
public:
	TV(){}
	virtual ~TV(){}
	virtual void play() = 0;
};

class HaierTV : public TV {
public:
	HaierTV():TV(){}
	~HaierTV(){}
	void play() {
		cout << "HaierTV playing..." << endl;
	}
};

class GreeTV : public TV {
public:
	GreeTV():TV(){}
	~GreeTV(){}
	void play() {
		cout << "GreeTV playing..." << endl;
	}
};

class TVFactory {
public:
	TVFactory(){}
	virtual ~TVFactory(){}

	virtual TV* produce() = 0;
};

class HaierFactory : public TVFactory {
public:
	HaierFactory():TVFactory() {}
	~HaierFactory(){}
	TV* produce() {return new HaierTV();}
};

class GreeFactory : public TVFactory {
public:
	GreeFactory():TVFactory(){}
	~GreeFactory(){}
	TV* produce() {return new GreeTV();}
};

#endif
