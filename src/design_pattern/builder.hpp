#ifndef SONGZI_BUILDER_H
#define SONGZI_BUILDER_H

#include <string>
#include <iostream>

using namespace std;

class Phase {
private:
	string name;
public:
	Phase(string n):name(n) {
		cout << "phase " << name << endl;
	}
	~Phase(){}
};

class GradeOne : public Phase {
public:
	GradeOne():Phase("GradeOne") {}
	~GradeOne(){}
};

class GradeTwo : public Phase {
public:
	GradeTwo():Phase("GradeTwo") {}
	~GradeTwo(){}
};

class GradeThree : public Phase{
public:
	GradeThree():Phase("GradeThree"){}
	~GradeThree(){}
};

class SeniorOne : public Phase {
public:
	SeniorOne():Phase("SeniorOne"){}
	~SeniorOne(){}
};

class SeniorTwo : public Phase {
public:
	SeniorTwo():Phase("SeniorTwo"){}
	~SeniorTwo(){}
};

class SeniorThree : public Phase {
public:
	SeniorThree():Phase("SeniorThree"){}
	~SeniorThree(){}
};

class PrimarySchool;
class JuniorSchool;
class School{
private:
	string name;
	friend class PrimarySchool;
	friend class JuniorSchool;
	School(string n):name(n){}
public:
	~School(){}
	virtual void phase_one() = 0;
	virtual void phase_two() = 0;
	virtual void phase_three() = 0;

	virtual void study(){}
	
};

class PrimarySchool : public School{
public:
	PrimarySchool():School("PrimarySchool"){}
	~PrimarySchool(){}
	virtual void phase_one();
	virtual void phase_two();
	virtual void phase_three();
	void study();
};

class JuniorSchool : public School{
public:
	JuniorSchool():School("JuniorSchool"){}
	~JuniorSchool(){}
	virtual void phase_one();
	virtual void phase_two();
	virtual void phase_three();
	void study();
};

class Student {
private:
	School *school;
public:
	Student(School *sc):school(sc){}
	~Student() {
		if (school) {
			delete school;
			school = NULL;
		}
	}

	void study() {school->study();}
};

#endif
