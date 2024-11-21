#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <omp.h>

#include "QuickSort.h"
#include "grafos.h"

void quick_sort(int list[], size_t left, size_t right){
    if(left < right){
        int pivot = partition(list, left, right);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                quick_sort(list, left, pivot - 1);
            }
            #pragma omp section
            {
                quick_sort(list, pivot + 1, right);
            }
        }
    }
}

int partition(int list[], int left, int right){
    int pivot = list[right];
    int i = left - 1;

    for(int j = left; j < right; j++){
        if(list[j] <= pivot){
            i++;
            int tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
        }
    }

    int temp = list[i + 1];
    list[i + 1] = list[right];
    list[right] = temp;

    return i + 1;
}
