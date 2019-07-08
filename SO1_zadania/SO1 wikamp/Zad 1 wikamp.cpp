#include <iostream>
#include <cmath>
#include <windows.h>
#include <process.h>
#include <sstream>
using namespace std;

UINT WINAPI Znak(LPVOID);

int main()
{
	string tekst;
	cout << "Podaj tekst\n";
	getline(cin,tekst);
	int l=tekst.length(),x=0;
    if (l>0) //zliczanie spacji, x = iloœæ spacji
	{
    	for(int i=0;i<l;i++)
    	{
    	    if(tekst[i]==' ')
    	    {
    	    	x++;
			}
    	}
    }
	istringstream iss( tekst ); //funckja zwracaj¹ca s³owa ze stringa
	string slowo;
	string a[100];
	int i=0;
	while( iss >> slowo ) //przypisanie s³ów do tablicy
	{
    	a[i]=slowo+" ";
    	i++;
	}
	i--;
	a[i]+="\n";
	HANDLE hthread[100];   //uchwyt do w¹tku
	UINT g=0;
	int j;
    for(j=0;j<=x;j++)
    {
    	hthread[j]=(HANDLE)_beginthreadex(NULL,0,Znak,&a[j],0,&g);  //przypisanie uchwytu i rozpoczêcie w¹tku
    	WaitForSingleObject(hthread[j],20);    //oczekiwanie na w¹tek
	}
    WaitForMultipleObjects(j,hthread,TRUE,INFINITE);    //oczekiwanie na w¹tki
	return 0;
}
UINT WINAPI Znak(LPVOID lpzn)
{
	string znak = *((string*) lpzn);
    for(int i=0;i<5;i++)
    {
		cout << znak;
    	cout.flush();
    	for (long k=0; k<900000; k++) pow(pow(pow(sin(k), 3.3), 2.2), 1.1 ); //spowalniacz
	}
}
