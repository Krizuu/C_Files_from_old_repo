#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
using namespace std;
DWORD GetProcessCount(const char *szProcessName) 
{
    DWORD dwCount = 0;
    HANDLE hSnap = NULL;
    PROCESSENTRY32 proc32;
    if((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
    {
    	return -1;
	}
    proc32.dwSize=sizeof(PROCESSENTRY32);
    while((Process32Next(hSnap, &proc32)) == TRUE)
    {
        if(stricmp(proc32.szExeFile,szProcessName) == 0)
        {
        	++dwCount;
		}
	}
    CloseHandle(hSnap);
    return dwCount;
}
int main()
{
    char tab[20]="Zad 6 wikamp.exe";
    DWORD x=GetProcessCount(tab);
	while(1)
	{
		x=GetProcessCount(tab);
		cout <<x<<endl;
	}
    return 0;
}
