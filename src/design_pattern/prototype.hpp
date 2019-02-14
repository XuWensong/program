#ifndef SONGZI_PROTOTYPE_H
#define SONGZI_PROTOTYPE_H

/**
*Deep Copy:reallocate new space for members, espacially pointers, need contruct
*		   function support copy
*Shallow Copy:not allocate new space, pointers in different instances point to the same
*            area, so pointer may be released twice or more
*
**/
#include <iostream>

using namespace std;

class ProtoType {
protected:
	ProtoType(){}
public:
	~ProtoType(){}
	virtual ProtoType* clone() = 0;
};

class ConcreteProtoType : public ProtoType {
public:
	ConcreteProtoType(){}
	ConcreteProtoType(const ConcreteProtoType &p) {
		cout << "ConcreteProtoType deep copy" << endl;
	}
	~ConcreteProtoType(){}

	ProtoType* clone();
};

#endif
