#include<stdio.h>
#include<string.h>
#include<windows.h>
#define size_buff 10000
int main()      //    Mapp1Child  --> nadaje komunikaty do innego procesu
{
HANDLE hMojeEvent = NULL, hMapFile = NULL;
char *pMapFile;	
char Nazwapliku[99];
unsigned char buff[size_buff];

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
    //---------------------------------------------
    
DWORD readed = 0;
HANDLE hFile;
    hFile=CreateFile(Nazwapliku,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
   	if(hFile == INVALID_HANDLE_VALUE)
	{
        printf("File not found");
        UnmapViewOfFile (pMapFile); 
		CloseHandle (hMapFile);
		CloseHandle (hMojeEvent);
        return 1;
    }
    DWORD dwPtr=SetFilePointer(hFile,0,NULL,FILE_BEGIN);
    if (dwPtr == INVALID_SET_FILE_POINTER)
	{ 
        printf("SetFilePointer error %d.\n", GetLastError()) ;
        return 2;
	}
	BOOL bResult=ReadFile(hFile,buff,size_buff,&readed,NULL);
	if(!bResult)
	{ 
		printf("ReadFile error %d.\n", GetLastError());
        return 3;
	}
	memcpy(pMapFile, buff, sizeof(buff));    //zapis danych
	PulseEvent(hMojeEvent);

CloseHandle(hFile);
UnmapViewOfFile (pMapFile); 
CloseHandle (hMapFile);
CloseHandle (hMojeEvent);
return 0;
}
