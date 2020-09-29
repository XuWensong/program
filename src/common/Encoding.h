#ifndef S3FS_ENCODING_H
#define S3FS_ENCODING_H

#include <string.h>
#include <map>
#include <list>
#include <vector>
#include <set>
#include "Buffer.h"

template<class T>
inline void encode_raw(const T& t, bufferlist &bl)
{
	bl.append((char*)&t, sizeof(t));
}

template<class T>
inline void decode_raw(T& t, bufferlist::iterator &p)
{
	p.copy(sizeof(t), (char*)&t);
}

#define WRITE_RAW_ENCODER(type) \
	inline void encode(const type &v, bufferlist &bl, uint64_t features=0) {encode_raw(v, bl);} \
	inline void decode(type &v, bufferlist::iterator &p) {decode_raw(v, p);}

// int types
WRITE_RAW_ENCODER(uint8_t)
WRITE_RAW_ENCODER(int8_t)
WRITE_RAW_ENCODER(uint16_t)
WRITE_RAW_ENCODER(int16_t)
WRITE_RAW_ENCODER(uint32_t)
WRITE_RAW_ENCODER(int32_t)
WRITE_RAW_ENCODER(uint64_t)
WRITE_RAW_ENCODER(int64_t)
WRITE_RAW_ENCODER(char)
WRITE_RAW_ENCODER(float)
WRITE_RAW_ENCODER(double)

inline void encode(const bool &v, bufferlist &bl) 
{
	uint8_t vv = v;
	encode_raw(vv, bl);
}

inline void decode(bool &v, bufferlist::iterator &p) {
	uint8_t vv;
	decode_raw(vv, p);
	v = vv;
}

// class type
#define WRITE_CLASS_ENCODER(cl) \
	inline void encode(cl &c, bufferlist &bl, uint64_t features=0) {c.encode(bl);} \
	inline void decode(cl &c, bufferlist::iterator &p) {c.decode(p);}

inline void encode(const std::string &s, bufferlist &bl, uint64_t features=0)
{
	uint32_t len = s.length();
	encode(len, bl);
	bl.append(s.data(), len);
}

inline void decode(std::string &s, bufferlist::iterator &p)
{
	uint32_t len;
	decode(len, p);
	s.clear();
	p.copy(len, s);
}

inline void encode(const char* c, bufferlist &bl)
{
	uint32_t len = strlen(c);
	encode(len, bl);
	bl.append(c, len);
}

// bufferlist type
inline void encode(bufferlist &s, bufferlist &bl)
{
	uint32_t len = s.length();
	encode(len, bl);
	bl.append(s);
}

inline void decode(bufferlist &s, bufferlist::iterator &p)
{
	uint32_t len;
	decode(len, p);
	s.clear();
	p.copy(len, s);
}

// pair type
template<class A, class B>
inline void encode(std::pair<A, B> &s, bufferlist &bl, uint64_t features=0)
{
	encode(s.first, bl);
	encode(s.second, bl);
}

template<class A, class B>
inline void decode(std::pair<A, B> &s, bufferlist::iterator &p)
{
	decode(s.first, p);
	decode(s.second, p);
}

// list type
template<class T>
inline void encode(std::list<T> &l, bufferlist &bl)
{
	uint32_t len = l.size();
	encode(len, bl);

	typename std::list<T>::iterator it = l.begin();
	for (; it != l.end(); it++)
		encode(*it, bl);
}

template<class T>
inline void decode(std::list<T> &l, bufferlist::iterator &p)
{
	uint32_t len;
	decode(len, p);
	for (; len > 0; len--) {
		T t;
		decode(t, p);
		l.push_back(t);
	}
}

// set type
template<class T>
inline void encode(std::set<T> &s, bufferlist &bl)
{
	uint32_t len = s.size();
	encode(len, bl);

	typename std::set<T>::iterator it = s.begin();
	for (; it != s.end(); it++)
		encode(*it, bl);
}

template<class T>
inline void decode(std::set<T> &s, bufferlist::iterator &p)
{
	uint32_t len;
	decode(len, p);

	for (; len > 0; len--) {
		T t;
		decode(t, p);
		s.insert(t);
	}
}

// map type
template<class A, class B>
inline void encode(std::map<A, B> &m, bufferlist &bl)
{
	uint32_t len = m.size();
	encode(len, bl);

	typename std::map<A, B>::iterator it = m.begin();
	for(; it != m.end(); it++) {
		encode(it->first, bl);
		encode(it->second, bl);
	}
}

template<class A, class B>
inline void decode(std::map<A, B>& m, bufferlist::iterator &p)
{
	uint32_t len;
	decode(len, p);
	for (; len > 0; len--) {
		A a;
		decode(a, p);
		decode(m[a], p);
		
	}
}

// vector type
template<class T>
inline void encode(std::vector<T> &v, bufferlist &bl)
{
	uint32_t len = v.size();
	encode(len, bl);

	for(int i = 0; i < len; i++)
		encode(v[i], bl);
}

template<class T>
inline void decode(std::vector<T> &v, bufferlist::iterator &p)
{
	uint32_t len;
	decode(len, p);
	v.resize(len);

	for (int i = 0; i < len; i++)
		decode(v[i], p);
}

#define ENCODE_START(v, compat, bl) \
	uint32_t struct_v = v, compat_v = compat; \
	::encode(struct_v, bl); \
	::encode(compat_v, bl);

#define DECODE_START(v, bl) \
	uint32_t struct_v, compat_v; \
	::decode(struct_v, bl); \
	::decode(compat_v, bl); \
	if (v < compat_v) \
		throw malformed_input();

#endif
