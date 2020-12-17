#include "kernel_op.h"

using namespace std;

#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)
#define container_of(ptr, type, member) ({ \
	void *mptr = (void*)ptr; \
	((type*) (mptr - offsetof(type, member)));})

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry(ptr->next, type, member)

#define list_next_entry(pos, member) \
	list_entry(pos->member.next, typeof(*pos), member)

#define list_for_each_entry(pos, head, member) \
	for (pos = list_first_entry(head, typeof(*pos), member); \
		 &pos->member != head; \
		 pos = list_next_entry(pos, member))

void KernelOp::exec()
{
	int sub_cmd = argument->get_sub_cmd();
	switch (sub_cmd) {
		case SUB_CMD_CONTAINEROF:
			test_container_of();
			break;
		case SUB_CMD_LIST:
			test_list();
			break;
	}
}

void KernelOp::test_container_of()
{
	struct kernel_data data;
	data.id = 4;
	cout << "id=" << data.id << endl;

	struct list_head *l = &(data.list);

	struct kernel_data *s = container_of(l, kernel_data, list);
	cout << "id=" << s->id << endl;
}

void KernelOp::test_list()
{
	struct list_head *l = new list_head();
	for (int i = 0; i < 10 ; i++) {
		struct kernel_data *data = new kernel_data();
		data->id = i;
		list_push_back(l, &(data->list));
	}

	struct kernel_data *data = NULL;
	list_for_each_entry(data, l, list)
		cout << data->id << endl;
}

void KernelOp::help()
{
	cout << "Support Commands:" << endl;
	cout << "  kernel containerof " << endl;
	cout << "  kernel list" << endl;
}