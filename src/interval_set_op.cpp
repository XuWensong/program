#include "common/IntervalSet.h"
#include "interval_set_op.h"

void IntervalSetOp::exec()
{
	map<int, int> frags;
	struct IntervalSet<int> is;
	is.insert(0, 50);
	is.dump();

	frags = is.get_frags(2, 32);

	cout << "frags:" << endl;
	map<int, int>::iterator p = frags.begin();
	for (; p != frags.end(); p++) {
		cout << p->first << "     " << p->second << endl;
	}
	

	cout << "size " << is.size() << endl;
}

void IntervalSetOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " test       test interval-set implements" << endl;
}