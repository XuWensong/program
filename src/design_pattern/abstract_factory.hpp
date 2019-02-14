#ifndef SONGZI_ABSTRACT_FACTORY_H
#define SONGZI_ABSTRACT_FACTORY_H
#include <iostream>
#include <string>

using namespace std;

/**
* AbstractFactory is used to create a set of class that related to each other
**/

class ProductLowLevelA;
class ProductMilddleLevelA;
class ProductHighLevelA;
class ProductLowLevelB;
class ProductMiddleLevelB;
class ProductHighLevelB;

class BaseProduct {
private:
	friend class ProductLowLevelA;
	friend class ProductMilddleLevelA;
	friend class ProductHighLevelA;
	friend class ProductLowLevelB;
	friend class ProductMiddleLevelB;
	friend class ProductHighLevelB;
	string name;
	BaseProduct(string n):name(n) {
		cout << "create " << name << endl;
	}
public:
	~BaseProduct(){}
};

class ProductLowLevelA : public BaseProduct {
public:
	ProductLowLevelA():BaseProduct("ProductLowLevelA"){}
	~ProductLowLevelA(){}
};

class ProductMilddleLevelA : public BaseProduct {
public:
	ProductMilddleLevelA():BaseProduct("ProductMiddleLevelA"){}
	~ProductMilddleLevelA(){}

};

class ProductHighLevelA : public BaseProduct {
public:
	ProductHighLevelA():BaseProduct("ProductHighLevelA"){}
};

class ProductLowLevelB : public BaseProduct {
public:
	ProductLowLevelB():BaseProduct("ProductLowLevelB"){}
	~ProductLowLevelB(){}
};

class ProductMiddleLevelB : public BaseProduct {
public:
	ProductMiddleLevelB():BaseProduct("ProductMiddleLevelB"){}
	~ProductMiddleLevelB(){}
};

class ProductHighLevelB : public BaseProduct {
public:
	ProductHighLevelB():BaseProduct("ProductHighLevelB") {}
	~ProductHighLevelB(){}
};

class AbstractFactory {
public:
	AbstractFactory(){}
	~AbstractFactory(){}

	virtual void create_product_low_level() {}
	virtual void create_product_middle_level() {}
	virtual void create_product_high_level() {}
};

class FactoryLowLevel : AbstractFactory {
public:
	FactoryLowLevel():AbstractFactory(){}
	~FactoryLowLevel(){}
	void create_product_low_level();
};

class FactoryMiddleLevel : AbstractFactory {
public:
	FactoryMiddleLevel():AbstractFactory(){}
	~FactoryMiddleLevel(){}
	void create_product_middle_level();
};

class FactoryHighLevel : AbstractFactory {
public:
	FactoryHighLevel():AbstractFactory(){}
	~FactoryHighLevel(){}
	void create_product_high_level();
};



#endif
