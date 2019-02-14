#include "builder.hpp"

void PrimarySchool::phase_one()
{
	GradeOne *p = new GradeOne();
	delete p;
	p = NULL;
}

void PrimarySchool::phase_two()
{
	GradeTwo *p = new GradeTwo();
	delete p;
	p = NULL;
}

void PrimarySchool::phase_three()
{
	GradeThree *p = new GradeThree();
	delete p;
	p = NULL;
}

void PrimarySchool::study()
{
	phase_one();
	phase_two();
	phase_three();
	cout << "Graduated from " << name << endl;
}

void JuniorSchool::phase_one()
{
	SeniorOne *p = new SeniorOne();
	delete p;
	p = NULL;
}

void JuniorSchool::phase_two()
{
	SeniorTwo *p = new SeniorTwo();
	delete p;
	p = NULL;
}

void JuniorSchool::phase_three()
{
	SeniorThree *p = new SeniorThree();
	delete p;
	p = NULL;
}

void JuniorSchool::study()
{
	phase_one();
	phase_two();
	phase_three();
	cout << "Graduated from " << name << endl;
}