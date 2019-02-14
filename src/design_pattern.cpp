#include "design_pattern.hpp"

void DesignPatternOp::test_factory()
{
	Factory *factory = new Factory();
	AbstractProduct *a = factory->create_product("ProductA");
	AbstractProduct *b = factory->create_product("ProductB");

	delete factory;
	factory = NULL;
	delete a;
	a = NULL;
	delete b;
	b = NULL;
}

void DesignPatternOp::test_abstract_factory()
{
	FactoryLowLevel *low_level_factory = new FactoryLowLevel();
	low_level_factory->create_product_low_level();

	FactoryMiddleLevel *middle_level_factory = new FactoryMiddleLevel();
	middle_level_factory->create_product_middle_level();

	FactoryHighLevel *high_level_factory = new FactoryHighLevel();
	high_level_factory->create_product_high_level();

	delete low_level_factory;
	low_level_factory = NULL;
	delete middle_level_factory;
	middle_level_factory = NULL;
	delete high_level_factory;
	high_level_factory = NULL;
}

void DesignPatternOp::test_builder()
{
	Student *primary_student = new Student(new PrimarySchool());
	Student *senior_student = new Student(new JuniorSchool());

	primary_student->study();
	senior_student->study();

	delete primary_student;
	primary_student = NULL;
	delete senior_student;
	senior_student = NULL;
}

void DesignPatternOp::test_prototype()
{
	ProtoType *p = new ConcreteProtoType();
	ProtoType *p1 = p->clone();

	delete p;
	p = NULL;
	delete p1;
	p1 = NULL;
}

void DesignPatternOp::test_singleton()
{
	Singleton *inst = Singleton::instance();

	
}

void DesignPatternOp::test_bridge()
{
	BridgeImplementA *imp_a = new BridgeImplementA();
	BridgeInterface *bridge_a = new BridgeInterface(imp_a);
	BridgeImplementB *imp_b = new BridgeImplementB();
	BridgeInterface *bridge_b = new BridgeInterface(imp_b);

	bridge_a->operation();
	bridge_b->operation();

	delete bridge_a;
	bridge_a = NULL;
	delete bridge_b;
	bridge_b = NULL;
}

void DesignPatternOp::test_adapter()
{
	Adaptee *adaptee = new Adaptee();
	AdapterBase *adapter = new Adapter(adaptee);
	adapter->operation();

	delete adapter;
	adapter = NULL;
}

void DesignPatternOp::exec()
{
}

void DesignPatternOp::help()
{
}