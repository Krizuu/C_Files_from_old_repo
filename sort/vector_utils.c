#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "vector_utils.h"

int read_vector(int vec[], int size, int stop_value){
    int a;
    
    for(a=0;a<size;a++)
    {
        int b;
        scanf("%d", &b);
        if(b!=stop_value)
        {
            vec[a]=b;
        }
        else
        {
            break;
        }
    }
    return a;
}

void display_vector(int vec[], int size){
    int a;

    for(a=0;a<size;a++)
    {
        printf("%d ", vec[a]);
    }
    printf("\n");
}