#ifndef _BOOK_H_
#define _BOOK_H_
#include <iostream>

using namespace std;
class Book
{
public:
	string Author;
	string Category;
	int Pages;
	bool Loaned;
	Book();
	Book(const char*, const char*, int, bool);
	~Book();
	friend ostream & operator << (ostream &, const Book &);
};
Book::Book()
{
}
Book::Book(const char* Auth, const char* Cat, int pag, bool loa)
{
	Author = Auth;
	Category = Cat;
	Pages = pag;
	Loaned = loa;
}
Book::~Book()
{
}
ostream & operator << (ostream & o, const Book & e)
{
	o << e.Author << " " << e.Category << " " << "Pages: " << e.Pages << " Loaned: " << e.Loaned;
	return o;
}

#endif