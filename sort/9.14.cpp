#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include <stdio.h>
#include "vector_utils.h"
#include "bubble_sort.h"

int main(void)
{
    printf("Cos");

    int vec[150];
    int s = read_vector(vec,150,0);
    
    bubble_sort(vec, s, 1);
    bubble_sort(vec, s, 2);


    display_vector(vec, s);

    return 0;
}