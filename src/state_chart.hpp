#ifndef _SONGZI_STATE_CHART_H_
#define _SONGZI_STATE_CHART_H_
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
//#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <iostream>
#include <string>

#include "op/op.hpp"

namespace sc = boost::statechart;

/**
*
*/

struct NamedState {
public:
	std::string name;
	NamedState(std::string _name):name(_name) {
		std::cout << "Enter State:" << name << std::endl;
	}
	virtual ~NamedState() {
		std::cout << "Leave state:" << name << std::endl;
	}

	std::string get_name() {
		return name;
	}
};
struct EvtStop : sc::event<EvtStop> {};
struct EvtStart : sc::event<EvtStart> {};
struct EvtHello : sc::event<EvtHello> {};

struct Initial;
struct StateMachine : sc::state_machine<StateMachine, Initial> {

};

struct Initial : sc::state <Initial, StateMachine>, NamedState {
public:
	//typedef sc::transition<EvtStop, Stopped> reactions;
	typedef sc::custom_reaction<EvtStart> reactions;
	Initial(my_context ctx):my_base(ctx), NamedState("Initial"){}

	sc::result react(const EvtStart&);
	
};

/**
*1.若存在子状态，则无条件自动进入子状态；
*2.若子状态已实现实现某种事件的响应，则优先调用当前状态的响应接口，否则调用父状态响应接口
*/
struct Active;
struct Started : sc::state<Started, StateMachine, Active>, NamedState {
public:
	Started(my_context ctx):my_base(ctx), NamedState("Started"){}
	typedef sc::custom_reaction<EvtStop> reactions;

	sc::result react(const EvtStop &);
};

/**
*state模板类的第二个参数为状态机或者父状态，第三个参数为初始子状态
*状态机转入子状态时，会默认优先转入父状态
*/
struct Acting;
struct Active : sc::state<Active, Started, Acting>, NamedState {
public:
	Active(my_context ctx):my_base(ctx), NamedState("Active") {}
	typedef boost::mpl::list <
		sc::custom_reaction<EvtStop>,
		sc::custom_reaction<EvtHello>
	> reactions;

	sc::result react(const EvtStop &);
	sc::result react(const EvtHello &);
};

struct Acting : sc::state<Acting, Active>, NamedState {
public:
	Acting(my_context ctx):my_base(ctx), NamedState("Acting"){}
	typedef boost::mpl::list<
		sc::custom_reaction<EvtHello>
	> reactions;

	sc::result react(const EvtHello&);
};

struct Hello : sc::state<Hello, StateMachine>, NamedState {
public:
	Hello(my_context ctx):my_base(ctx), NamedState("Hello"){}
	typedef boost::mpl::list<
		sc::custom_reaction<EvtHello>
	> reactions;

	sc::result react(const EvtHello &);
};

struct Stopped : sc::state<Stopped, StateMachine>, NamedState {
public:
	Stopped(my_context ctx):my_base(ctx), NamedState("Stopped") {}
};

struct StateMachineOp : public Op {
public:
	StateMachineOp(Argument *argument):Op(argument, "statechart", "test state chart"){}
	~StateMachineOp(){}
	virtual void exec();
	virtual void help();
};

#endif