#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#include <iostream>

using namespace std;
class Employee
{
public:
	string Name;
	string Position;
	int Age;
	Employee();
	Employee(const char*, const char*, int);
	~Employee();
	friend ostream & operator << (ostream &, const Employee &);
};
Employee::Employee()
{
}
Employee::Employee(const char* Nam, const char* Pos, int ag)
{
	Name = Nam;
	Position = Pos;
	Age = ag;
}
Employee::~Employee()
{
}
ostream & operator << (ostream & o, const Employee & e)
{
	o << e.Name << " " << e.Position << " " << e.Age;
	return o;
}

#endif