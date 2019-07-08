#include<stdio.h>
#include<stdlib.h>


int is_prime_rec(int a, int divisor)
{	
int i;
	
	if(a<2)
    return 0;
     
	for(i = 2; i < a; i++) 
     {
          if(a*divisor % i == 0)
          {
               return 0;
          }
     }
     
     
     
     return 1;
}

int main(void)
{
	int k, a, b, divisor=1;
	
	printf("Podaj liczbe ");
	scanf("%d", &k);
	printf("Podaj liczbe ");
	scanf("%d", &b);
	
	if(k<2)
	k=2;
	
	for(a=k;a<=b;a++)
	{
	if(is_prime_rec(a,divisor)==1)
	printf("%d\n",a);
	
	}

}
