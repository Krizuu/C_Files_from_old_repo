#include <iostream>
using namespace std;

#include "employee.h"			//defines class Employee
#include "book.h"
#include "map_template.h"		//defines template map_template<Key,Value>

int main(void)
{

	typedef unsigned int ID; 							//Identification number of Employee
	map_template<ID, Employee> Database;					//Database of employees
	Database.Add(761028073,Employee("Jan Kowalski","salesman",28)); 	//Add first employee: name: Jan Kowalski, position: salseman, age: 28,
	Database.Add(510212881,Employee("Adam Nowak","storekeeper",54)); 	//Add second employee: name: Adam Nowak, position: storekeeper, age: 54
	Database.Add(730505129,Employee("Anna Zaradna","secretary",32)); 	//Add third employee: name: Anna Zaradna, position: secretary, age: 32

	cout << Database << endl;							//Print databese

	map_template<ID,Employee> NewDatabase = Database;	//Make a copy of database
	
	Employee* pE;
	try
	{
		pE = NewDatabase.Find(51021288);	//Find employee using its ID
		pE->Position = "salesman";			//Modify the position of employee
	}catch(std::invalid_argument & o)
	{
		cout << o.what() << endl;
	}
						
	try
	{
		pE = NewDatabase.Find(761028073);			//Find employee using its ID
		pE->Age = 29;								//Modify the age of employee
	}catch(std::invalid_argument & o)						
	{
		cout << o.what() << endl;
	}								

	Database = NewDatabase;								//Update original database
	
	cout << Database << endl;							//Print original databese



	typedef string Title;
	map_template<Title, Book> BookBase;
	BookBase.Add("Tytul 1",Book("Autor 1", "Sci-Fi", 500, 0));
	BookBase.Add("Tytul 2",Book("Author 2", "Document", 940, 0)); 
	BookBase.Add("Tytul 3",Book("Author 3", "Novel", 300, 0));

	cout << BookBase << endl;

	map_template<Title,Book> NewBookBase = BookBase;
	
	Book* pB;
	try
	{
		pB = NewBookBase.Find("Tytul 1");
		pB->Category = "New Category";
	}catch(std::invalid_argument & o)
	{
		cout << o.what() << endl;
	}
						
	try
	{
		pB = NewBookBase.Find("Tytul 2");
		pB->Pages = 300;
	}catch(std::invalid_argument & o)						
	{
		cout << o.what() << endl;
	}								

	BookBase = NewBookBase;
	
	cout << BookBase << endl;

	return 0;
}
