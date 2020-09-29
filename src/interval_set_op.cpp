#include "common/IntervalSet.h"
#include "interval_set_op.h"

void IntervalSetOp::exec()
{
	struct IntervalSet<int> is;
	is.insert(50, 10);
	is.dump();
	is.insert(55, 5);
	is.dump();

	cout << "size " << is.size() << endl;
}

void IntervalSetOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " test       test interval-set implements" << endl;
}