#include<stdio.h>
#include<string.h>
#include<windows.h>

int main()      //    Mapp1Child--> nadaje komunikaty do obcego procesu
{
HANDLE hMojeEvent = NULL, hMapFile = NULL;
char *pMapFile;	
char Komunikat[33];
int sizeF=sizeof Komunikat;

	hMojeEvent=OpenEvent(EVENT_ALL_ACCESS, FALSE, "MojeEvent");
	if(hMojeEvent==NULL) {  printf("OpenEvent error:"); getchar(); return 1; }

// Utworzenie obiektu reprezentujacego plik zmapowany 
	if(!(hMapFile=OpenFileMapping(FILE_MAP_WRITE,FALSE, "MojaMapp")))
	{  	printf("OpenFileMapping error: %d\n", GetLastError()); getchar(); return 1; 	}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE,  0, 0, 0);
//-------------------------------------------------------------------------
	do{
		printf("\nKomunikat dla obcego procesu : ");  gets(Komunikat);
        //scanf("%s", Komunikat);		
		memcpy(pMapFile, Komunikat, sizeF);    //zapis danych
		PulseEvent(hMojeEvent);
	  } while(strcmp(Komunikat, "koniec"));

UnmapViewOfFile (pMapFile); CloseHandle (hMapFile);
return 0;
}

