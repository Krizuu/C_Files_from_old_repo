#include<string.h>
#include<windows.h>
#include<stdio.h>

int main()          // Mapp1Parent   <-- odbiera polecenia
{
HANDLE hMojeEvent = NULL;
HANDLE hMapFile=NULL;	//uchwyt do obiektu reprezentujacego plik zmapowany
char *pMapFile;			//wskaznik na poczatek obszaru zmapowanego pliku
char Komunikat[33];
int sizeF = sizeof Komunikat;

	hMojeEvent = CreateEvent(NULL, TRUE,FALSE, "MojeEvent");
	if(hMojeEvent==NULL){  printf("CreateEvent error:");  getchar(); return 1;}

HANDLE hFile =(HANDLE)0xffffffff;  //wartosc -1
// Utworzenie obiektu reprezentujacego zmapowany plik 
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE, 0,1024, "MojaMapp");
	if(hMapFile==NULL) { printf("CreateFileMapping error:"); getchar(); return 1;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci 
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE, 0,0, 0);
//----------------------------------------------------------------------------
	do 	{
		WaitForSingleObject(hMojeEvent, INFINITE);
		memcpy(Komunikat, pMapFile, sizeF);
		printf("\nOdebrano Komunikat : %s", Komunikat);
		if(!strcmp(Komunikat,"koniec")) break;
	}	while(1);

UnmapViewOfFile (pMapFile);// zwolnienie pamieci przeznaczonej na odwzorowanie pliku 
CloseHandle (hMapFile);
return 0;
}
