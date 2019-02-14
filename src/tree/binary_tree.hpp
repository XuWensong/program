#ifndef SONGZI_BINARY_TREE_H_
#define SONGZI_BINARY_TREE_H_

#include "op/op.hpp"
#include <list>

struct BinaryTreeNode {
	int m_data;
	int m_depth;
	BinaryTreeNode *m_left_child;
	BinaryTreeNode *m_right_child;

	BinaryTreeNode():m_data(0), m_depth(0), m_left_child(NULL), m_right_child(NULL){}
	BinaryTreeNode(int data):m_data(data), m_depth(0), m_left_child(NULL), m_right_child(NULL){}

	void create(std::list<int> data);
	void remove(int data);

	void create_left(int data);
	void create_right(int data);
	void print();
};

class BinaryTreeOp : public Op {
private:
	BinaryTreeNode *binary_tree;
public:
	BinaryTreeOp(Argument *arg):Op(arg, "binarytree", "implement of binary tree"){}
	virtual void exec();
	virtual void help();

	void create();
	void print();
	void set_tree_depth(BinaryTreeNode *node);
	void find_deepest_leaf(BinaryTreeNode *node, int &depth, int &data);

};


#endif
