#include "tree/binary_tree.hpp"
#include <iostream>
#include <list>

using namespace std;

void print_empty(int num) 
{
	for(int i = 0; i < num; i++) {
		cout << " ";
	}
}

void BinaryTreeNode::create(list<int> data)
{
	list<BinaryTreeNode *> nodes;
	nodes.push_back(this);
	list<int>::iterator iter = data.begin();
	
	for (; iter != data.end(); iter++) {
		BinaryTreeNode *node = nodes.front();
		nodes.pop_front();

		node->create_left(*iter);
		iter++;
		if (iter == data.end()) {
			break;
		}
		node->create_right(*iter);

		nodes.push_back(node->m_left_child);
		nodes.push_back(node->m_right_child);
	}

}

void BinaryTreeNode::remove(int data)
{

}

void BinaryTreeNode::create_left(int data)
{
	if (!m_left_child) {
		m_left_child = new BinaryTreeNode(data);
	}
}

void BinaryTreeNode::create_right(int data)
{
	if (!m_right_child) {
		m_right_child = new BinaryTreeNode(data);
	}
}

void BinaryTreeNode::print()
{
	list<list<BinaryTreeNode *> > levels;
	list<BinaryTreeNode *> nodes;
	nodes.push_back(this);
	levels.push_back(nodes);

	list<list<BinaryTreeNode *> >::iterator iter = levels.begin();
	for(; iter != levels.end(); iter++) {
		nodes.clear();
		list<BinaryTreeNode *>::iterator p = iter->begin();
		for(; p != iter->end(); p++) {
			if ((*p)->m_left_child) {
				nodes.push_back((*p)->m_left_child);
			}
			if ((*p)->m_right_child) {
				nodes.push_back((*p)->m_right_child);
			}
		}
		if (!nodes.empty()) {
			levels.push_back(nodes);
		}
	}

	int len = 25, i = 1, size = levels.size();
	for(iter = levels.begin(); iter != levels.end(); iter++, i++) {
		//print_empty(len / i);
		
		list<BinaryTreeNode *>::iterator p = iter->begin();
		for(; p != iter->end(); p++) {
			print_empty(len);
			cout << (*p)->m_data;
			print_empty(len);
		}
		cout << endl;
		len = len / 2;
	}
}

void BinaryTreeOp::exec()
{
	binary_tree = new BinaryTreeNode(0);
	list<int> data;
	for(int i = 1; i < 10; i++) {
		data.push_back(i);
	}

	binary_tree->create(data);
	cout << "Create Tree Successfully" << endl;
	binary_tree->print();
	set_tree_depth(binary_tree);

	int l_depth = 0, r_depth = 0;
	int l_data = binary_tree->m_data, r_data = binary_tree->m_data;
	if (binary_tree->m_left_child) {
		find_deepest_leaf(binary_tree->m_left_child, l_depth, l_data);
	}

	if (binary_tree->m_right_child) {
		find_deepest_leaf(binary_tree->m_right_child, r_depth, r_data);
	}

	cout << "Left deapest, data=" << l_data << ", depth=" << l_depth << endl;
	cout << "Right deapest, data=" << r_data << ", depth=" << r_depth << endl;
}

void BinaryTreeOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " test" << endl;
}

void BinaryTreeOp::create()
{
	
}

void BinaryTreeOp::print()
{

}

void BinaryTreeOp::set_tree_depth(BinaryTreeNode *node)
{
	if (node->m_left_child) {
		node->m_left_child->m_depth = node->m_depth + 1;
		set_tree_depth(node->m_left_child);
	}

	if (node->m_right_child) {
		node->m_right_child->m_depth = node->m_depth + 1;
		set_tree_depth(node->m_right_child);
	}
}

void BinaryTreeOp::find_deepest_leaf(BinaryTreeNode *node, int &depth, int &data)
{
	BinaryTreeNode *cur = node;
	if (cur->m_left_child) {
		if (cur->m_left_child->m_depth > depth) {
			depth = cur->m_left_child->m_depth;
			data = cur->m_left_child->m_data;
		}
		find_deepest_leaf(cur->m_left_child, depth, data);
	}

	if (cur->m_right_child) {
		if (cur->m_right_child->m_depth > depth) {
			depth = cur->m_right_child->m_depth;
			data = cur->m_right_child->m_data;
		}
		find_deepest_leaf(cur->m_right_child, depth, data);
	}
}