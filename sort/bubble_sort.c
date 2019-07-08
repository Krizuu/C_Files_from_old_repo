#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "vector_utils.h"
#include "bubble_sort.h"

int przez(int x)
{
    int a;
    int b=0;

    for(a=1;a<=x;a++)
    {
        if(x%a==0)
        {
            b++;
        }
    }
    return b;
}

int sum(int liczba)
{
    if(liczba<10)
    {
    return liczba;
    }
return (liczba%10+sum(liczba/10));  
}

void bubble_sort(int tab[], int size, int dir, int odl){
    if(dir==1)
        bubble_sort_asc(tab, size);
    if(dir==2)
        bubble_sort_desc(tab, size);
    if(dir==3)
        bubble_sort_licz(tab,size,odl);
}

void bubble_sort_asc(int tab[], int size){
    int a=size-1, c=0;

    while(c==0)
    {
        int d, c=0;

        for(d=0;d<a;d=d+1)
        {
            if(sum(abs(tab[d+1]))<sum(abs(tab[d])))
            {
                int temp=tab[d];
                tab[d]=tab[d+1];
                tab[d+1]=temp;
                c=1;
            }
        }
        a--;
        if(c==0)
            return;
    }
}

void bubble_sort_licz(int tab[], int size, int licz){
    int a=size-1, c=0;

    while(c==0)
    {
        int d, c=0;
        for(d=0;d<a;d=d+1)
        {
            if((abs(tab[d+1]-licz))<abs((tab[d]-licz)))
            {
                int go=tab[d];
                tab[d]=tab[d+1];
                tab[d+1]=go;
                c=1;
            }
        }
        a--;
        if(c==0)
            return;
    }
}

void bubble_sort_desc(int tab[], int size){
    int a=size-1, c=0;

    while(c==0)
    {
        int d, c=0;
        for(d=1;d<a-1;d=d+2)
        {
            if(tab[d+2]>tab[d])
            {
                int temp=tab[d];
                tab[d]=tab[d+2];
                tab[d+2]=temp;
                c=1;
            }
        }
        a--;
        if(c==0)
            return;
    }
}






void bubble_sort_rec(int tab[], int size, int dir)
{
    if(dir==1)
        bubble_sort_asc_rec(tab, size);
    if(dir==2)
        bubble_sort_desc_rec(tab, size);
}
void bubble_sort_asc_rec(int tab[], int size)
{
      int b=size-1,c=0;
  
        int a;
        for(a=0;a<b-1;a++)
        {
            if(tab[a+1]<tab[a])
            {
                int temp=tab[a];
                tab[a]=tab[a+1];
                tab[a+1]=temp;
                c=1;
            }
        
        }
        if (c==1)
            bubble_sort_asc_rec(tab, size-1);
}
void bubble_sort_desc_rec(int tab[], int size)
{
      int c=0;
      if(size>1)
      {
        int a;
        for(a=0;a<size-1;a++)
        {
            if(tab[a+2]>tab[a])
            {
                int temp=tab[a];
                tab[a]=tab[a+1];
                tab[a+1]=temp;
                c=1;
            }

        }
        if(c==1)
            bubble_sort_desc_rec(tab, size-1);
}}