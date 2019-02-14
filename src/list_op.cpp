#include "list_op.hpp"

template <typename I>
void List<I>::push_front(I data)
{
	m_size++;
	Node<I> *n = new Node<I>(data);
	_push_front(n);
}

template <typename I>
void List<I>::pop_front(I &data)
{
	m_size--;
	Node<I> *n = _pop_front();
	if (n) {
		data = n->data;
		delete n;
		n = NULL;
	}
}

template <typename I>
void List<I>::push_back(I data)
{
	m_size++;
	Node<I> *n = new Node<I>(data);
	_push_back(n);
}

template <typename I>
void List<I>::pop_back(I &data) 
{
	m_size--;
	Node<I>* n = _pop_back();
	if (n) {
		data = n->data;
		delete n;
		n = NULL;
	}
}

template <typename I>
void List<I>::clear()
{
	Node<I> *next = m_head;
	while (next != NULL) {
		Node<I> *cursor = next;
		if (next != m_tail) {
			next = cursor->next;
		} else {
			next = cursor->next;
		}
		delete cursor;
		cursor = NULL;
	}
	m_head = NULL;
	m_tail = NULL;
	m_size = 0;
}

template <typename I>
void SingleList<I>::_push_front(Node<I>* n)
{
}

template <typename I>
Node<I>* SingleList<I>::_pop_front()
{
	return NULL;
}

template <typename I>
void SingleList<I>::_push_back(Node<I>* n)
{
}

template <typename I>
Node<I>* SingleList<I>::_pop_back()
{
	return NULL;
}

