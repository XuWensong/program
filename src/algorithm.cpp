#include "algorithm.hpp"
#include "common/types.hpp"
#include <iostream>
#include <map>
#include <string.h>
#include <stack>
#include <list>
#include <utility>

using namespace std;

void ListByStack::swap(stack<int> &src, stack<int> &dest)
{
	while (!src.empty()) {
		dest.push(src.top());
		src.pop();
	}
}

int ListByStack::top()
{
	int data;
	swap(m_data, m_switch);
	data = m_switch.top();
	swap(m_switch, m_data);
	return data;
}

void ListByStack::push(int item)
{
	m_data.push(item);
}

void ListByStack::pop()
{
	swap(m_data, m_switch);
	m_switch.pop();
	swap(m_switch, m_data);
}

void SymbolStack::print()
{
	list<string>::iterator iter = m_data.begin();
	for (; iter != m_data.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
}

void Frog::print() 
{
	list<int>::iterator iter = m_steps.begin();
	for(; iter != m_steps.end(); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
}

void AlgorithmOp::exec()
{
	int len = 8;
	int data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	cout << "Array: " << endl;
	print(data, len);
	//bubble_sort(data, len);
	
	//quick_sort(data, 0, len - 1);
	
	//find_max_consistent_array(data, len);

	//cout << find_specified_value(data, 0, len - 1, 6) << endl;
	
	//list<int> pos;
	//find_matched_combo(data, pos, 0, len, 5, 3);
	
	//multiply_and_plus_array(data, len);

	//list<int> pos;
	//find_combo(data, pos, 0, len, 3);
	
	//int index = binary_find(data, 0, len - 1, 0);
	//cout << "Index=" << index << endl;

	/*
	int count = 0;
	int r = devide_apple(data, len, count); 
	if (r < 0) {
		cout << "No way" << endl;
	}
	cout << "Move count=" << count << endl;
	*/
	//list<pair<int, int> > steps;
	//steps.push_back(pair<int, int> (1, 1));
	//chase_horse_road(steps, 10, 6);

	string src = "abcdbc";
	string dest = "bc";
	//force_string_match(src, dest, 0, 0);
	//kmp(src, dest);
	//two_num_plus(data, len, 6);
	three_num_plus(data, len, 11);
	
	
	cout << "Array after process: " << endl;
	print(data, len);

	
	//SymbolStack stack(3);
	//find_matched_symbol(stack);

	//Frog frog(5);
	//frog_step(frog);
	
	//stack_for_list();
	
	//cut_tree();

	//object_on_stack();
	//object_on_heap();
}

void AlgorithmOp::help()
{
	cout << "Support Commands:" << endl;
	cout << " algorithm" << endl;
}

void AlgorithmOp::print(int data[], int len)
{
	for (int i = 0; i < len; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
}

//冒泡排序
void AlgorithmOp::bubble_sort(int data[], int len)
{
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (data[i] > data[j]) {
				int tmp = data[i];
				data[i] = data[j];
				data[j] = tmp;
			}
		}
	}
}

//快速排序
void AlgorithmOp::quick_sort(int data[], int left, int right)
{
	int l = left;
	int r = right;
	int axis = data[left];

	while (l < r) {
		while (data[r] >= axis && l < r) {
			r--;
		}

		if (l < r) {
			data[l] = data[r];
			l++;
			while (data[l] <= axis && l < r) {
				l++;
			}

			if (l < r) {
				data[r] = data[l];
				r--;
			}
		}
	}
	data[l] = axis;

	if (right > r + 1) {
		quick_sort(data, r + 1, right);
	} 
	if (left < l - 1) {
		quick_sort(data, left, l - 1);
	}
}

//快速排序
void AlgorithmOp::quick_sort(Tree data[], int left, int right)
{
	int l = left;
	int r = right;
	Tree axis = data[l];

	while (l < r) {
		while (axis < data[r] && l < r) {
			r--;
		}
		if (l < r) {
			data[l] = data[r];
			l++;

			while(data[l] < axis && l < r) {
				l++;
			}

			if (l < r) {
				data[r] = data[l];
				r--;
			}
		}
	}
	data[l] = axis;

	if (right > r + 1) {
		quick_sort(data, r + 1, right);
	}

	if (left < l - 1) {
		quick_sort(data, left, l - 1);
	}
}

// 二分查找，要求数组有序
int AlgorithmOp::binary_find(int data [], int left, int right, int value)
{
	int center = (left + right) / 2;
	if (center == left || center == right) {
		if (data[center] == value) {
			return center;
		}
		return -1;
	}

	if (data[center] == value) {
		return center;
	} else if (data[center] < value) {
		return binary_find(data, left, center, value);
	} else {
		return binary_find(data, center, right, value);
	}
	return -1;
}

//通过二分法查找数组内第一个大于给定的值
int AlgorithmOp::binary_find_first_larger(Tree data[], int left, int right, int value)
{
	int center = (left + right) / 2;
	if (left == right && data[left].m_cut_len > value) {
		return left;
	} 

	if (left < right) {
		if (data[right].m_cut_len <= value && data[right - 1].m_cut_len > value) {
			return right - 1;
		}
		if (data[left].m_cut_len > value && data[left + 1].m_cut_len <= value) {
			return left;
		}
	}

	if (data[center].m_cut_len >= value) {
		return binary_find_first_larger(data, center, right, value);
	} else {
		return binary_find_first_larger(data, left, center, value);
	}
	return -1;
}

//求数组内子数组最大和，采用动态规划思想
void AlgorithmOp::find_max_consistent_array(int data[], int len)
{
	int max = 0, cur = 0;
	int start = -1, end = -1, new_start = -1;
	bool started = false;

	for (int i = 0; i < len; i++) {
		cur += data[i];
		if (!started) {
			new_start = i;
			started = true;
		}

		if (cur > max) {
			max = cur;
			start = new_start;
			end = i;
		}
		if (cur < 0) {
			cur = 0;
			started = false;
		}
	}

	cout << "Max=" << max << ", start=" << start << ", end=" << end << endl;
}

//查找无序数组内第几大的值，结合快排思想，时间复杂度为O(n)
int AlgorithmOp::find_specified_value(int data[], int left, int right, int seq)
{
	int l = left;
	int r = right;
	int axis = data[left];

	while (l < r) {
		while (data[r] >= axis && l < r) {
			r--;
		}

		if (l < r) {
			data[l] = data[r];
			l++;
			while (data[l] <= axis && l < r) {
				l++;
			}
			if (l < r) {
				data[r] = data[l];
				r--;
			}
		}
	}
	data[l] = axis;

	int larger = right - l + 1;
	if (seq == larger) {
		return data[l];
	} else if (seq < larger) {
		if (right > r + 1) {
			return find_specified_value(data, r + 1, right, seq);
		} else {
			return data[right];
		}
		
	} else {
		if (left < l - 1) {
			return find_specified_value(data, left, l - 1, seq - larger);
		} else {
			return data[left];
		}
	}
}


//左右括号的匹配方式，模拟二叉树的深度优先搜索
void AlgorithmOp::find_matched_symbol(SymbolStack stack)
{
	if (!stack.length()) {
		stack.add_left();
	}
	SymbolStack l_stack = stack;
	SymbolStack r_stack = stack;

	if (l_stack.left() < l_stack.num()) {
		l_stack.add_left();
		find_matched_symbol(l_stack);
	}

	if (r_stack.left() > r_stack.right() && r_stack.right() < r_stack.num()) {
		r_stack.add_right();
		find_matched_symbol(r_stack);
	}
	if (stack.length() == stack.num() * 2) {
		stack.print();
	}
}

void AlgorithmOp::find_matched_combo(int data[], list<int> &pos, int start, int len, int target, int num)
{
	for (int i = start; i < len; i++) {
		list<int> m_pos = pos;
		int m_target = target;
		int m_num = num;
		if (m_num == 1) {
			if (data[i] == target) {
				pos.push_back(i);
				list<int>::iterator iter = pos.begin();
				for(; iter != pos.end(); iter++) {
					cout << *iter << " ";
				}
				cout << endl;
			} 
		} else {
			m_target -= data[i];
			m_num--;
			m_pos.push_back(i);
			find_matched_combo(data, m_pos, i + 1, len, m_target, m_num);
		}
	}
}

//寻找数组内和为target的所有连续子数组
void AlgorithmOp::find_combo(int data[], list<int> pos, int start, int len, int target)
{
	for (int i = start; i < len; i++) {
		int m_target = target;
		list<int> m_pos = pos;
		if (data[i] == m_target) {
			m_pos.push_back(i);
			list<int>::iterator iter = m_pos.begin();
			for(; iter != m_pos.end(); iter++) {
				cout << data[*iter] << " ";
			}
			//cout << data[i];
			cout << endl;
			continue;
		}
		if (data[i] > target) {
			continue;
		}
		m_target -= data[i];
		m_pos.push_back(i);
		find_combo(data, m_pos, i, len, m_target);
	}
}

void AlgorithmOp::frog_step(Frog &frog)
{
	Frog one_step = frog;
	Frog two_step = frog;

	if (frog.m_total_steps == frog.m_cur_steps) {
		frog.print();
		return;
	}

	if (one_step.m_total_steps > one_step.m_cur_steps) {
		one_step.step_one();
		frog_step(one_step);
	}

	if (two_step.m_total_steps > two_step.m_cur_steps + 1) {
		two_step.step_two();
		frog_step(two_step);
	}
}

void AlgorithmOp::cut_tree()
{
	int len = 4;
	Tree trees[4] = {Tree(5), Tree(2), Tree(9), Tree(1)};
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (trees[i] < trees[j]) {
				trees[i].m_cut_len += (trees[j].m_high - trees[i].m_high);
			}
		}
	}

	quick_sort(trees, 0, len - 1);
	for (int i = 0; i < len; i++) {
		cout << "Tree high=" << trees[i].m_high << ", cut_len=" << trees[i].m_cut_len << endl;
	}
	int index = binary_find_first_larger(trees, 0, len - 1, 5);
	if (index < 0) {
		cout << "Found No Tree" << endl;
		return;
	}
	cout << "Final Tree index=" << index << ", high=" << trees[index].m_high << ", cut_len=" 
			<< trees[index].m_cut_len << endl;
}

void AlgorithmOp::multiply_and_plus_array(int data[], int len)
{
	int max = 0;
	int l[len];
	int r[len];
	int left, right, index;
	memset(l, 0, sizeof(int) * len);
	memset(r, 0, sizeof(int) * len);
	for(int i = 0; i < len; i++) {
		l[i] = i;
		r[i] = i;
		for (int j = i - 1; j >= 0; j--) {
			if (data[j] < data[i]) {
				break;
			} else {
				l[i] = j;
			}
		}

		for (int j = i + 1; j < len; j++) {
			if (data[j] < data[i]) {
				break;
			} else {
				r[i] = j;
			}
		}
	}

	for (int i = 0; i < len; i++) {
		int sum = 0;
		if (l[i] == r[i]) {
			sum = data[i];
		}

		for (int j = l[i]; j < r[i]; j++) {
			sum += data[j];
		}

		int cur = sum * data[i];
		if (cur > max) {
			left = l[i];
			right = r[i];
			index = i;
			max = cur;
		}
	}
	cout << "left:" << left << ", right:" << right << ", index:" << index << ",Max:" << max << endl;
}

//使用两个stack实现list功能
void AlgorithmOp::stack_for_list()
{
	ListByStack l;
	l.push(1);
	l.push(2);
	l.push(3);

	while (!l.empty()) {
		cout << l.top() << endl;
		l.pop();
	}
}

void AlgorithmOp::rotation_array_sort()
{
	
}

//生成只能创建在栈上的对象
void AlgorithmOp::object_on_stack()
{
	struct ObjectForStack object("object_for_stack");
	cout << object.m_name << endl;
	//struct ObjectForStack *o = new ObjectForStack("object_for_stack");
}

//生成只能创建在堆上的对象
void AlgorithmOp::object_on_heap()
{
	//struct ObjectForHeap object;
	struct ObjectForHeap *o = ObjectForHeap::create();
	cout << o->m_name << endl;
}

int AlgorithmOp::devide_apple(int data[], int len, int &count)
{
	int fetch_num = 2;
	int odd = data[0] % 2;

	if (len < 2) {
		return 0;
	}
	
	for (int i = 1; i < len; i++) {
		if ((data[i] % 2) != odd) {
			return -1;
		}
	}
	quick_sort(data, 0, len - 1);

	data[len - 1] -= 2;
	data[0] += 2;
	count++;

	int head_max = data[0] > data[1] ? data[1] : data[0];
	int tail_max = data[len - 1] > data[len - 2] ? data[len - 1] : data[len - 2];
	int gap = tail_max - head_max;
	if (gap > 2) {
		devide_apple(data, len, count);
	} else if (gap == 2) {
		return -1;
	}

	return 0;
}

void AlgorithmOp::circle_gas_station()
{}

void AlgorithmOp::chase_horse_road(list<pair<int, int> > steps, int x, int y)
{
	pair<int, int> iter = steps.back();
	int cur_x = iter.first, cur_y = iter.second;
	//cout << "cur_x=" << cur_x << ", cur_y=" << cur_y << endl;

	if (cur_x == x && cur_y == y) {
		cout << "Steps:" << endl;
		while (!steps.empty()) {
			pair<int, int> p = steps.front();
			cout << "x=" << p.first << ", y=" << p.second << endl;
			steps.pop_front();
		}
		return;
	}

	if (cur_x + 1 <= x) {
		if (cur_y - 2 >= 0) {
			list<pair<int, int> > cur_steps = steps;
			cur_steps.push_back(pair<int, int>(cur_x + 1, cur_y - 2));
			chase_horse_road(cur_steps, x, y);
		}

		if (cur_y + 2 <= 24) {
			list<pair<int, int> > cur_steps = steps;
			cur_steps.push_back(pair<int, int>(cur_x + 1, cur_y + 2));
			chase_horse_road(cur_steps, x, y);
		}
	}

	if (cur_x + 2 <= x) {
		if (cur_y - 1 >= 0) {
			list<pair<int, int> > cur_steps = steps;
			cur_steps.push_back(pair<int, int>(cur_x + 2, cur_y - 1));
			chase_horse_road(cur_steps, x, y);
		}
		
		if (cur_y + 1 <= 24) {
			list<pair<int, int> > cur_steps = steps;
			cur_steps.push_back(pair<int, int>(cur_x + 2, cur_y + 1));
			chase_horse_road(cur_steps, x, y);
		}
	}
}

void AlgorithmOp::force_string_match(string src, string dest, int start, int end)
{
	for (int i = start; i < src.length(); i++) {
		if (src[i] == dest[end]) {
			cout << "Found one, i=" << i << ", end=" << end << endl;
			if (end + 1 == dest.length()) {
				cout << "Found, start=" << start << ", end=" << end << endl;
				return;
			}
			force_string_match(src, dest, i + 1, end + 1);
		}
	}
	cout << "Not Found" << endl;
}

void AlgorithmOp::kmp_get_next(string data, map<int, int> &next)
{
	int k = 0;
	next[0] = 0;
	for(int q = 1; q < data.length(); q++) {
		while (k > 0 && data[q] != data[k]) {
			k = next[k - 1];
		}
		if (data[q] == data[k]) {
			k++;
		}
		next[q] = k;
	}
}

void AlgorithmOp::kmp(string src, string target)
{
	map<int, int> next;
	int i, q, start = 0;
	int src_len = src.length();
	int target_len = target.length();

	kmp_get_next(target, next);
	cout << "Next:" << endl;
	map<int, int>::iterator iter = next.begin();
	for (; iter != next.end(); iter++) {
		cout << iter->first << " " << iter->second << endl;
	}

	for (i = 0, q = 0; i < src_len; i++) {

		while (q > 0 && src[i] != target[q]) {
			q = next[q - 1];	
		}
		if (src[i] == target[q]) {
			if (start == 0) {
				start = i;
			}
			q++;
		}
		if (q == target_len) {
			cout << "Found, start=" << start << endl;
			start = 0;
			q = 0;
			//return;
		}
	}
}

void AlgorithmOp::two_num_plus(int data[], int len, int sum)
{
	quick_sort(data, 0, len - 1);
	int i = 0, j = len - 1;
	while (i < j) {
		if (data[i] + data[j] == sum) {
			cout << data[i] << " " << data[j] << endl;
			i++;
			j--;
		} else if (data[i] + data[j] < sum) {
			i++;
		} else {
			j--;
		}
	}
}

void AlgorithmOp::three_num_plus(int data[], int len, int sum)
{
	quick_sort(data, 0, len - 1);
	for (int i = 0; i < len - 3; i++) {
		int j = i + 1;
		int k = len - 1;
		int cur = sum - data[i];
		while (j < k) {
			if (data[j] + data[k] == cur) {
				cout << data[i] << " " << data[j] << " " << data[k] << endl;
				j++;
				k--;
			} else if (data[j] + data[k] < cur) {
				j++;
			} else {
				k--;
			}
		}
	}
}