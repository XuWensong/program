#ifndef S3FS_INTERVALSET_H
#define S3FS_INTERVALSET_H
#include <inttypes.h>
#include <iterator>
#include <map>
#include <iostream>

#include "Encoding.h"


template <class T>
class IntervalSet {
private:
	uint64_t m_size;
	std::map<T, T> m_inters;
public:
	IntervalSet(): m_size(0){}
	~IntervalSet(){}

	class iterator : public std::iterator<std::forward_iterator_tag, T> {
	protected:
		typename std::map<T, T>::iterator m_it;
	public:
		iterator(typename std::map<T, T>::iterator it):m_it(it){}
		bool operator==(const iterator &rhs) {
			return (m_it == rhs.m_it);
		}
		bool operator!=(const iterator &rhs) {
			return (m_it != rhs.m_it);
		}
		typename std::pair<T, T> &operator*(){
			return *m_it;
		}
		T get_start() {return m_it->first;}
		T get_len() {return m_it->second;}
		void set_len(T len) {m_it->second = len;}
		iterator &operator++() {
			++m_it;
			return *this;
		}
		iterator operator++(int) {
			iterator prev(m_it);
			++m_it;
			return prev;
		}
	};

	IntervalSet<T>::iterator begin() {
		return IntervalSet<T>::iterator(m_inters.begin());
	}
	IntervalSet<T>::iterator end() {
		return IntervalSet<T>::iterator(m_inters.end());
	}
private:
	typename std::map<T, T>::iterator find(T start) {
		typename std::map<T, T>::iterator it = m_inters.lower_bound(start);
		if (it != m_inters.begin() && 
			(it == m_inters.end() || it->first > start)) {
			it--;
			if (it->first + it->second <= start)
				it++;
		}
		return it;
	}

	typename std::map<T, T>::iterator find_adj(T start) {
		typename std::map<T, T>::iterator it = m_inters.lower_bound(start);
		if (it != m_inters.begin() &&
			(it == m_inters.end() || it->first > start)) {
			it--;
			if (it->first + it->second < start)
				it++;
		}
		return it;
	}
public:
	bool operator==(const IntervalSet<T> &rhs) {
		return m_size == rhs.m_size && m_inters == rhs.m_inters;
	}

	uint64_t size() {return m_size;}
	void encode(bufferlist &bl) {
		::encode(m_inters, bl);
	}
	void decode(bufferlist::iterator &bl) {
		::decode(m_inters, bl);
		m_size = 0;
		for(typename std::map<T, T>::const_iterator p=m_inters.begin();
			p!=m_inters.end();
			p++)
			m_size += p->second;
	}
	void clear() {
		m_inters.clear();
		m_size = 0;
	}
	bool contains(T s) {
		typename std::map<T, T>::iterator p = find(s);
		if (p == m_inters.end()) 
			return false;
		if (p->first > s)
			return false;
		if (p->first + p->second <= s)
			return false;
		return true;	
	}
	bool contains(T s, T l) {
		typename std::map<T, T>::iterator p = find(s);
		if (p == m_inters.end())
			return false;
		if (p->first > s)
			return false;
		if (p->first + p->second <= s)
			return false;
		if (p->first + p->second < s + l)
			return false;
		return true;
	}
	bool overlap(T s, T l) {
		typename std::map<T, T>::iterator p = find(s);
		if (p == m_inters.end())
			return false;
		if (p->first >= s + l)
			return false;
		if (p->first + p->second <= s)
			return false;
		return true;
	}
	bool empty() {
		return m_inters.empty();
	}
	void insert(T off, T len) {
		std::list<T> trims;
		T end = off + len;
		T new_off = off, new_len = len;

		if (!m_size) {
			m_inters[off] = len;
			m_size += len;
			return;
		}

		// contained in some gaps
		if (contains(off, len)) {
			return;
		}

		m_size += len;
		typename std::map<T, T>::iterator p = find_adj(off);
		for (; p != m_inters.end(); p++) {
			if (p->first > end)
				break;

			if (p->first == end) { //continugous
				new_len += p->second;
				trims.push_back(p->first);
				continue;
			}
			if (p->first <= off && p->first + p->second >= off) { // head overlap
				new_off = p->first;
				new_len += off - p->first;
				m_size -= (p->first + p->second - off);
				continue;
			}

			if (p->first <= end && p->first + p->second >= end) {// tail ovarlap
				new_len += p->first + p->second - end;
				trims.push_back(p->first);
				m_size -= (end - p->first);
				continue;
			}
			// contain this gap
			trims.push_back(p->first);
			m_size -= p->second;
		}

		m_inters[new_off] = new_len;
		while (!trims.empty()) {
			uint64_t o = trims.front();
			trims.pop_front();
			m_inters.erase(o);
		}
		
	}

	void erase(T off) {
		if (!contains(off))
			return;
		typename std::map<T, T>::iterator p = find(off);
		if (p->first == off) { //trim all
			m_size -= p->second;
			m_inters.erase(p);
			return;
		}
		// trim tail
		uint64_t l = p->second;
		p->second = off - p->first;
		m_size -= p->first + p->second - off;
	}
	void erase(T off, T len) {
		if (!overlap(off, len))
			return;
	}
	void dump() {
		std::cout << "dump:" << std::endl;
		typename std::map<T, T>::iterator p = m_inters.begin();
		for(; p != m_inters.end(); p++)
			std::cout << p->first << "   " << p->first + p->second << std::endl;
	}
};


#endif

