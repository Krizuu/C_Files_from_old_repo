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
    if (l>0) //zliczanie spacji, x = ilo�� spacji
	{
    	for(int i=0;i<l;i++)
    	{
    	    if(tekst[i]==' ')
    	    {
    	    	x++;
			}
    	}
    }
	istringstream iss( tekst ); //funckja zwracaj�ca s�owa ze stringa
	string slowo;
	string a[100];
	int i=0;
	while( iss >> slowo ) //przypisanie s��w do tablicy
	{
    	a[i]=slowo+" ";
    	i++;
	}
	i--;
	a[i]+="\n";
	HANDLE hthread[100];   //uchwyt do w�tku
	UINT g=0;
	int j;
    for(j=0;j<=x;j++)
    {
    	hthread[j]=(HANDLE)_beginthreadex(NULL,0,Znak,&a[j],0,&g);  //przypisanie uchwytu i rozpocz�cie w�tku
    	WaitForSingleObject(hthread[j],20);    //oczekiwanie na w�tek
	}
    WaitForMultipleObjects(j,hthread,TRUE,INFINITE);    //oczekiwanie na w�tki
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
