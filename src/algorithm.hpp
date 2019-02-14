#ifndef SONGZI_ALGORITHM_H
#define SONGZI_ALGORITHM_H

#include "op/op.hpp"
#include <list>
#include <string>
#include <stack>
#include <stdlib.h>
#include <utility>
#include <map>

struct ObjectForStack {
private:
	void* operator new(size_t size){
		return std::malloc(size);
	}
	void operator delete(void *ptr) {
		std::free(ptr);
	} 
public:
	ObjectForStack():m_name(""){}
	ObjectForStack(std::string name):m_name(name){}

	std::string m_name;
};

struct ObjectForHeap {
private:
	ObjectForHeap():m_name(""){}
	ObjectForHeap(std::string name):m_name(name){}
public:

	static ObjectForHeap* create() {return new ObjectForHeap("object_for_heap");}

	std::string m_name;
};

struct Tree {
	int m_high;
	int m_cut_len;

	Tree():m_high(0), m_cut_len(0) {}
	Tree(int len):m_high(len), m_cut_len(){}

	bool operator<(const Tree &other) {
		return m_high < other.m_high;
	}
};

struct ListByStack {
private:
	std::stack<int> m_data;
	std::stack<int> m_switch;
	void swap(std::stack<int> &src, std::stack<int> &dest);
public:
	ListByStack(){}
	bool empty() {return m_data.empty();}
	int top();
	void push(int item);
	void pop();
};

struct SymbolStack {
private:
	int m_num;
	int m_left;
	int m_right;
	std::list<std::string> m_data;
public:
	SymbolStack(int num):m_num(num), m_left(0), m_right(0){}
	void add_left() {m_data.push_back("("); m_left++;}
	void add_right() {m_data.push_back(")"); m_right++;}
	int left() {return m_left;}
	int right() {return m_right;}
	int num() {return m_num;}
	int length() {return m_left + m_right;}
	void print();
};

struct Frog {
	int m_total_steps;
	int m_cur_steps;
	std::list<int> m_steps;

	Frog(int steps):m_total_steps(steps), m_cur_steps(0){}

	void step_one() {
		m_cur_steps++;
		m_steps.push_back(1);
	}
	void step_two() {
		m_cur_steps += 2; 
		m_steps.push_back(2);
	}

	void print();
};

class AlgorithmOp : public Op {
public:
	AlgorithmOp(Argument *arg):Op(arg, "algorithm", "implement of algorithm"){
	}

	virtual void exec();
	virtual void help();
private:
	void print(int data[], int len);
	void bubble_sort(int data[], int len);
	void quick_sort(int data[], int left, int right);
	void quick_sort(Tree data[], int left, int right);

	int binary_find(int data[], int left, int right, int value);
	int binary_find_first_larger(Tree data[], int left, int right, int value);
	void find_max_consistent_array(int data[], int len);
	int find_specified_value(int data[], int left, int right, int seq);
	void find_matched_symbol(SymbolStack stack);
	void find_matched_combo(int data[], std::list<int> &pos, int start, int len, int target, int num);
	void find_combo(int data[], std::list<int> pos, int start, int len, int target);
	void frog_step(Frog &frog); 
	void cut_tree();
	void multiply_and_plus_array(int data[], int len);
	void stack_for_list();
	void rotation_array_sort();
	void object_on_stack();
	void object_on_heap();
	int devide_apple(int data[], int len, int &count);
	void circle_gas_station();
	void chase_horse_road(std::list<std::pair<int, int> > steps, int x, int y);
	void force_string_match(std::string src, std::string dest, int start, int end);
	void kmp_get_next(std::string data, std::map<int, int> &next);
	void kmp(std::string src, std::string target);
	void two_num_plus(int data[], int len, int sum);
	void three_num_plus(int data[], int len, int sum);
};

#endif
