#include<windows.h>
#include<cstring>
#include<cstdio>
using namespace std;
struct num
{
	int numbers[10];
	int n;
}liczby;
struct next
{
	int suma=0;
	int n;
}nextf;
int main()          // Mapp1Parent   <-- odbiera polecenia
{
HANDLE hMojeEvent = NULL;
HANDLE hMapFile=NULL;	//uchwyt do obiektu reprezentujacego plik zmapowany
char *pMapFile;			//wskaznik na poczatek obszaru zmapowanego pliku

	hMojeEvent = CreateEvent(NULL, TRUE,FALSE, "MojeEvent");
	if(hMojeEvent==NULL){  printf("CreateEvent error:");  getchar(); return 1;}

HANDLE hFile = INVALID_HANDLE_VALUE; 

// Utworzenie obiektu reprezentujacego zmapowany plik 
	hMapFile = CreateFileMapping(hFile,NULL,PAGE_READWRITE, 0, sizeof(num), "MojaMapp");
	if(hMapFile==NULL) { printf("CreateFileMapping error %d:",GetLastError()); 
	getchar(); return 2;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci 
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE, 0,0, 0);
	if(pMapFile==NULL) { printf("Blad przydzielenia PAO"); getchar();  return 3;}
//----------------------------------------------------------------------------
		WaitForSingleObject(hMojeEvent, INFINITE);
		memcpy(&liczby, pMapFile, sizeof(num));
		for(int i=0;i<liczby.n;i++)
		{
			nextf.suma+=liczby.numbers[i];
		}
		nextf.n=liczby.n;
		printf("\nOdebrano liczby");
		printf("\nSuma = %d",nextf.suma);
		printf("\nIlosc liczb = %d",liczby.n);
		Sleep(5000);
BOOL ind = UnmapViewOfFile(pMapFile);  // zwolnienie pamieci na odwzorowanie pliku 
			if(ind==NULL) { printf("Blad Unmap"); getchar();  return 33;}
//CloseHandle(hMapFile);
//CloseHandle(hMojeEvent);
/*
	hMojeEvent=OpenEvent(EVENT_ALL_ACCESS, FALSE, "przekaz sumy");
	if(hMojeEvent==NULL) {  printf("OpenEvent error:"); getchar(); return 4; }

// Utworzenie obiektu reprezentujacego plik zmapowany 
	if(!(hMapFile=OpenFileMapping(FILE_MAP_WRITE,FALSE, "MojaMapp")))
	{  	printf("OpenFileMapping error: %d\n", GetLastError()); getchar(); return 5;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE,  0, 0, 0);
	if(pMapFile==NULL) { printf("Blad przydzielenia PAO"); getchar();  return 6;}
//-------------------------------------------------------------------------

	printf("\nPrzekazanie sumy do innego procesu : ");
	memcpy(pMapFile,&nextf, sizeof(next));    //zapis danych
	PulseEvent(hMojeEvent);

UnmapViewOfFile (pMapFile);*/
CloseHandle (hMapFile);
CloseHandle (hMojeEvent);
return 0;
}
