#include<stdio.h>
#include<string.h>
#include<windows.h>
#define size_buff 10000
int main()      //    Mapp1Child  --> nadaje komunikaty do innego procesu
{
HANDLE hMojeEvent = NULL, hMapFile = NULL;
char *pMapFile;	
char Nazwapliku[99];

	hMojeEvent=OpenEvent(EVENT_ALL_ACCESS, FALSE, "MojeEvent");
	if(hMojeEvent==NULL) {  printf("OpenEvent error:"); getchar(); return 4; }

// Utworzenie obiektu reprezentujacego plik zmapowany 
	if(!(hMapFile=OpenFileMapping(FILE_MAP_WRITE,FALSE, "MojaMapp")))
	{  	printf("OpenFileMapping error: %d\n", GetLastError()); getchar(); return 5;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE,  0, 0, 0);
	if(pMapFile==NULL) { printf("Blad przydzielenia PAO"); getchar();  return 6;}
//-------------------------------------------------------------------------
	printf("Podaj nazwe pliku do skopiowania: \n");
	char *fPath=Nazwapliku;
    scanf("%c",fPath);
    fPath++;
    while(*fPath!='\n')
    {
        scanf("%c",fPath);
        if(*fPath=='\n')
        {
            break;
        }
        fPath++;
    }
    *fPath='\0';
    fPath=Nazwapliku;
    if(strstr(Nazwapliku,".bin")==NULL&&strstr(Nazwapliku,".txt")==NULL)
    {
        printf("Unsupported File Format");
        return 2;
    }
    int i;
    for(i=0;Nazwapliku[i]!='\0';i++){}
    i--;
    FILE *f;
    if(Nazwapliku[i]=='t')
    {
    	f=fopen(Nazwapliku,"r");
	}
	else
	{
    	f=fopen(Nazwapliku,"rb");
	}
    if(f==NULL)
    {
        printf("File not found");
        UnmapViewOfFile (pMapFile); 
		CloseHandle (hMapFile);
		CloseHandle (hMojeEvent);
        return 1;
    }
    size_t n;
    unsigned char buff[size_buff];
    n=fread(buff,1,sizeof (buff),f);
		memcpy(pMapFile, buff, sizeof(buff));    //zapis danych
		PulseEvent(hMojeEvent);

UnmapViewOfFile (pMapFile); 
CloseHandle (hMapFile);
CloseHandle (hMojeEvent);
return 0;
}

