#include <iostream>
#include "op/op.hpp"

using namespace std;

void Op::usage()
{
	int prefix_len = 15;
	string help_info = name;
	for (int i = 0; i < prefix_len - name.length(); i++) {
		help_info.append(" ");
	}
	help_info.append(description);
	cout << help_info << endl;
}