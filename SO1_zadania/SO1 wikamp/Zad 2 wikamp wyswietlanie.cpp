#include<windows.h>
#include<cstring>
#include<cstdio>
using namespace std;
int main()          // Mapp1Parent   <-- odbiera polecenia
{
HANDLE hMojeEvent = NULL;
HANDLE hMapFile=NULL;	//uchwyt do obiektu reprezentujacego plik zmapowany
char *pMapFile;			//wskaznik na poczatek obszaru zmapowanego pliku
float dzielenie;

	hMojeEvent = CreateEvent(NULL, TRUE,FALSE, "przekaz wyniku");
	if(hMojeEvent==NULL){  printf("CreateEvent error:");  getchar(); return 1;}

HANDLE hFile = INVALID_HANDLE_VALUE; 

// Utworzenie obiektu reprezentujacego zmapowany plik 
	hMapFile = CreateFileMapping(hFile,NULL,PAGE_READWRITE, 0, sizeof(dzielenie), "MojaMapp");
	if(hMapFile==NULL) { printf("CreateFileMapping error %d:",GetLastError()); 
	getchar(); return 2;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci 
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE, 0,0, 0);
	if(pMapFile==NULL) { printf("Blad przydzielenia PAO"); getchar();  return 3;}
//----------------------------------------------------------------------------
		WaitForSingleObject(hMojeEvent, INFINITE);
		memcpy(&dzielenie, pMapFile, sizeof(dzielenie));
		printf("Srednia to : %f",dzielenie);
		Sleep(3000);
BOOL ind = UnmapViewOfFile(pMapFile);  // zwolnienie pamieci na odwzorowanie pliku 
			if(ind==NULL) { printf("Blad Unmap"); getchar();  return 33;}
CloseHandle(hMapFile);
CloseHandle(hMojeEvent);
return 0;
}
