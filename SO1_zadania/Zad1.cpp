#include <process.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

VOID Tekst(LPVOID);

int main()
{
	char tab[30];
	char *txt = tab;
	char temp[10];
	char *word = temp;
	int i = 0, j = 0;
	HANDLE watek = NULL;
	int count = 0;
	
	printf("Podaj tekst: ");
	fgets(txt, 30, stdin);
	
	do {
		if(*(txt + i) == ' ' || *(txt + i) == '\n') {
			count++;
		}
		i++;	
	} while(*(txt + i) != '\0');
	
	
	for(int k = 0; k < count; k++) {
		i = 0;
		do {
			if(*(txt + i) == ' ' || *(txt + i) == '\n') {
				watek = (HANDLE)_beginthread(Tekst, 0, word);
				Sleep(10);
				memset(word, 0, sizeof(word));
				j = 0;
			}
			*(word + j) = *(txt + i);
			i++;
			j++;
		} while(*(txt + i) != '\0');	
	}
	
	return 0;	
}

void Tekst(LPVOID parm)
{
	char *tekst = (char*)parm;
	printf("%s", tekst);
	fflush(stdin);
	_endthread(); // Not needed
}
