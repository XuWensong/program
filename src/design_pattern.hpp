#ifndef SONGZI_DESIGN_PATTERN_H
#define SONGZI_DESIGN_PATTERN_H

#include "op/op.hpp"
#include "design_pattern/factory.hpp"
#include "design_pattern/abstract_factory.hpp"
#include "design_pattern/singleton.hpp"
#include "design_pattern/prototype.hpp"
#include "design_pattern/builder.hpp"
#include "design_pattern/bridge.hpp"
#include "design_pattern/adapter.hpp"

class DesignPatternOp : public Op {
private:
	void test_factory();
	void test_abstract_factory();
	void test_builder();
	void test_prototype();
	void test_singleton();
	void test_bridge();
	void test_adapter();
public:
	DesignPatternOp(Argument *argument):Op(argument, "dp", "test case of design pattern") {

	}
	~DesignPatternOp(){}

	virtual void exec();
	virtual void help();
};


#endif
