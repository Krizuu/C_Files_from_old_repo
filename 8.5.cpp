#include<stdio.h>
#include<stdlib.h>


int is_divisible_by_11(int number)
{
	
	if(number%11==0)
		return printf("TAK");
	else
		return printf("NIE");
	
}

int main(void)
{
	int number;
	
	printf("Podaj liczbe ");
	scanf("%d", &number);
	
	printf("%d",is_divisible_by_11(number));
	
	
	return 0;
}
