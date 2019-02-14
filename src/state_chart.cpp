#include "state_chart.hpp"

using namespace std;

sc::result Initial::react(const EvtStart &) {
	cout << "Get Event:EvtStart in State:" << name << endl;
	return transit<Started>();
}

sc::result Started::react(const EvtStop &)
{
	cout << "Get Event:EvtStop in State:" << name << endl;
	return transit<Stopped>();
}

sc::result Active::react(const EvtStop &)
{
	cout << "Get Event:EvtStop in State:" << name << endl;
	return transit<Stopped>();
}

sc::result Active::react(const EvtHello &evt)
{
	cout << "Parent State:" << context<Started>().get_name() << endl;
	cout << "Get Event:EvtHello in State:" << name << endl;
	return discard_event();
}

sc::result Acting::react(const EvtHello &evt)
{
	cout << "Get Event:EvtHello in State:" << name << endl;
	post_event(evt);
	return transit<Hello>();
}

sc::result Hello::react(const EvtHello &)
{
	cout << "Get Event:EvtHello in State:" << name << endl;
	return transit<Active>();
}

void StateMachineOp::exec()
{
	StateMachine state_machine;
	state_machine.initiate();
	state_machine.process_event(EvtStart());
	state_machine.process_event(EvtHello());
	state_machine.process_event(EvtStop());
}

void StateMachineOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " test" << endl;
}