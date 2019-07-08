#include<stdio.h>
#include<string.h>
#include<windows.h>
struct num
{
	int numbers[10];
	int n;
}liczby;
int main()      //    Mapp1Child  --> nadaje komunikaty do innego procesu
{
HANDLE hMojeEvent = NULL, hMapFile = NULL;
char *pMapFile;

	hMojeEvent=OpenEvent(EVENT_ALL_ACCESS, FALSE, "MojeEvent");
	if(hMojeEvent==NULL) {  printf("OpenEvent error:"); getchar(); return 4; }

// Utworzenie obiektu reprezentujacego plik zmapowany 
	if(!(hMapFile=OpenFileMapping(FILE_MAP_WRITE,FALSE, "MojaMapp")))
	{  	printf("OpenFileMapping error: %d\n", GetLastError()); getchar(); return 5;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE,  0, 0, 0);
	if(pMapFile==NULL) { printf("Blad przydzielenia PAO"); getchar();  return 6;}
//-------------------------------------------------------------------------
	printf("Ile liczby chcesz podac(max 10)?\n");
	int a;
	scanf("%d",&a);
	
    for(int i=0;i<a;i++)
	{	
		printf("%d liczba: ", i+1);
		scanf("%d",&liczby.numbers[i]);
	}
	liczby.n=a;
	memcpy(pMapFile, &liczby, sizeof(num));    //zapis danych
	PulseEvent(hMojeEvent);

UnmapViewOfFile (pMapFile);
CloseHandle (hMapFile);
CloseHandle (hMojeEvent);
return 0;
}	
