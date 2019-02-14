#ifndef SONGZI_BRIDGE_H
#define SONGZI_BRIDGE_H

/**
*In Bridge pattern, the interface "Abstraction" and the implement "Implement" are separated
**/

// beigin intergface
class BridgeImplement;
class BridgeInterface {
private:
	BridgeImplement *_imp;
public:
	BridgeInterface(BridgeImplement *imp):_imp(imp) {}
	~BridgeInterface();

	void operation();
};
//end interface

//begin implement
class BridgeImplement {
public:
	BridgeImplement(){}
	virtual ~BridgeImplement(){}
	virtual void operation(){};
};

class BridgeImplementA : public BridgeImplement {
public:
	BridgeImplementA():BridgeImplement(){}
	~BridgeImplementA(){}

	virtual void operation();
};

class BridgeImplementB : public BridgeImplement {
public:
	BridgeImplementB():BridgeImplement(){}
	~BridgeImplementB(){}

	virtual void operation();
};
//end implement


#endif
