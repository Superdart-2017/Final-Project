#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>

#include "Busqueda_Binaria.h"
#include "grafos.h"

bool binary_search_it(int list[], int len, int key){
    int first= 0;
    int last= len-1;

    while (first <= last){
        int center = (first + last)/2;

        if(list[center] == key){
            return true;
        }

        if(first == last){
            return false;
        }

        if(key < list[center]){
            last = center -1;
        } else{
            first = center +1;
        }
    }
    return false;
}