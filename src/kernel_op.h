#ifndef SONGZI_KERNEL_OP_H
#define SONGZI_KERNEL_OP_H

#include "op/op.hpp"
#include <string>

struct list_head {
	struct list_head *next, *prev;

	list_head():next(this), prev(this){}
};

struct kernel_data {
	int id;
	struct list_head list;
};

void list_push_back(struct list_head *l, struct list_head *n) {
	struct list_head *back = l->prev;
	back->next = n;
	l->prev = n;
	n->prev = back;
	n->next = l;
}

void list_pop_front(struct list_head *l) {
	struct list_head* next = l->next;
	l->next = next->next;
}

bool list_empty(struct list_head *head) {return head->next == head;}

class KernelOp : public Op {
public:
	KernelOp(Argument* args):Op(args, "kernel", "test functions in kernel") {}
	~KernelOp(){}

	virtual void exec();
	virtual void help();
private:
	void test_container_of();
	void test_list();
};


#endif
