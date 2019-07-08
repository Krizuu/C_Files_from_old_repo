#include<windows.h>
#include<cstring>
#include<cstdio>
#define size_buff 10000
using namespace std;

int main()          // Mapp1Parent   <-- odbiera polecenia
{
HANDLE hMojeEvent = NULL;
HANDLE hMapFile=NULL;	//uchwyt do obiektu reprezentujacego plik zmapowany
char *pMapFile;			//wskaznik na poczatek obszaru zmapowanego pliku
char Nazwapliku[99];
unsigned char buff[size_buff];

	hMojeEvent = CreateEvent(NULL, TRUE,FALSE, "MojeEvent");
	if(hMojeEvent==NULL){  printf("CreateEvent error:");  getchar(); return 1;}

//HANDLE hFile = (HANDLE)0xFFFFFFFF   lub  (HANDLE)0xFFFFFFFFFFFFFFFF;
HANDLE hFile = INVALID_HANDLE_VALUE; 

// Utworzenie obiektu reprezentujacego zmapowany plik 
	hMapFile = CreateFileMapping(hFile,NULL,PAGE_READWRITE, 0, sizeof(buff), "MojaMapp");
	if(hMapFile==NULL) { printf("CreateFileMapping error %d:",GetLastError()); 
	getchar(); return 2;}

// Przydzielenie pamieci na odwzorowanie pliku w pamieci 
	pMapFile = (char *)MapViewOfFile (hMapFile, FILE_MAP_WRITE, 0,0, 0);
	if(pMapFile==NULL) { printf("Blad przydzielenia PAO"); getchar();  return 3;}
//----------------------------------------------------------------------------
	printf("Podaj nazwe pliku docelowego: \n");
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
    	f=fopen(Nazwapliku,"w");
	}
	else
	{
    	f=fopen(Nazwapliku,"wb");
	}
    if(f==NULL)
    {
        printf("Can't create file");
        UnmapViewOfFile (pMapFile); 
		CloseHandle (hMapFile);
		CloseHandle (hMojeEvent);
        return 1;
    }
		WaitForSingleObject(hMojeEvent, INFINITE);
		memcpy(buff, pMapFile, sizeof(buff));
		printf("Odebrano dane do kopii");
    size_t m;
    for(i=0;buff[i]!='\0';i++){}
	m=fwrite(buff,1,i,f);

BOOL ind = UnmapViewOfFile(pMapFile);  // zwolnienie pamieci na odwzorowanie pliku 
			if(ind==NULL) { printf("Blad Unmap"); getchar();  return 33;}
CloseHandle(hMapFile);
CloseHandle(hMojeEvent);
return 0;
}
