#ifndef SONGZI_LIST_OP_H
#define SONGZI_LIST_OP_H

#include <unistd.h>

template <typename I>
struct Node {
	int id;
	Node<I> *next;
	Node<I> *prev;
	I data;
	Node():id(0), next(NULL), prev(NULL), data(NULL){}
	Node(I d):id(0), next(NULL), prev(NULL), data(d){}
};

template <typename I>
struct List {
private:
	int m_size;
	Node<I> *m_head;
	Node<I> *m_tail;

protected:
	virtual void _push_front(Node<I> *n) = 0;
	virtual Node<I>* _pop_front() = 0;
	virtual void _push_back(Node<I> *in) = 0;
	virtual Node<I>* _pop_back() = 0;

public:
	List(){}
	virtual ~List() {
		clear();
	}
	virtual void push_front(I data);
	virtual void pop_front(I &data);
	virtual void push_back(I data);
	virtual void pop_back(I &data);

	void clear();
	int size() {return m_size;}
};

template <typename I>
class SingleList : public List<I> {
	SingleList():List<I>(){}
	virtual void _push_front(Node<I>* n);
	virtual Node<I>* _pop_front();
	virtual void _push_back(Node<I>* n);
	virtual Node<I>* _pop_back();
};

#endif
