#include <stdio.h>
#include <string.h>


int main()
{
    char b;
	int a;
    
    printf("Podaj imie ");
    scanf("%s", &b);
    a=strlen(&b);
    
    printf("%d",a);
    
    return 0;
    
}
