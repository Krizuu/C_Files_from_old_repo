#include <iostream>
#include <windows.h>
#include <process.h>
using namespace std;
int main()
{
	bool bAlreadyRunning;
    HANDLE hMutexOneInstance=CreateMutex(NULL,TRUE,"SINGLE PROCESS");
    bAlreadyRunning=(GetLastError()==ERROR_ALREADY_EXISTS);
    if(bAlreadyRunning)
    {
    	return 1;
	}
	while(1)
	{
		cout <<"Jedyny proces"<<endl;
	}
    if(hMutexOneInstance)
	{
        ReleaseMutex(hMutexOneInstance);
    	CloseHandle(hMutexOneInstance);
    }
	return 0;
}
