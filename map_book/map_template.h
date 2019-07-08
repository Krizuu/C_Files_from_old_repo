#ifndef __MAP_TEMPLATE_H_
#define __MAP_TEMPLATE_H_
#include <iostream>
#include <vector>
#include "employee.h"

template <class T, class C>
class map_template
{
private:
	struct empVec;
	vector <struct empVec> arr;
public:
	map_template();
	~map_template();
	void Add(T, C);
	C * Find(T);
	template <class F, class G>
	friend ostream & operator<< ( ostream & o, const map_template<F, G> & e );

};

template <class T, class C>
struct map_template<T, C>::empVec
{
	C emp;
	T id;

	empVec(T Id, C p)
	{
		emp = p;
		id = Id;
	}
	~empVec()
	{		
	}
};

template <class T, class C>
map_template<T, C>::map_template()
{
}

template <class T, class C>
map_template<T, C>::~map_template()
{
}

template <class T, class C>
void map_template<T, C>::Add(T id, C p)
{
	arr.push_back(empVec(id, p));
}

template <class T, class C>
C * map_template<T, C>::Find(T id)
{
	for(unsigned int i = 0;i < arr.size();i++)
	{
		if(id == arr[i].id)
		{
			return &arr[i].emp;
		}
	}
	throw std::invalid_argument("Not found");
}

template <class F, class G>
ostream & operator << (ostream & o, const map_template<F, G> & e)
{
	for(unsigned int i = 0;i < e.arr.size();i++)
		o << e.arr[i].id << " " << e.arr[i].emp << endl;
	return o;
}

	

#endif