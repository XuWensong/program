#include "prototype.hpp"

ProtoType* ConcreteProtoType::clone()
{
	return new ConcreteProtoType(*this);
}

