#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"


void GetCollection(int elements, int length);

int main (void) {
    int cardinality = 7;//GetCardinality();
    int length = SIZEOFURL;
    //if (!cardinality) return 1;
    //char array[cardinality][URLNAMELEN];
    //if (!GetCollection(cardinality, URLNAMELEN, array[cardinality][URLNAMELEN])) return 1;
    GetCollection(cardinality, length);
    //for (int k = 0; k < cardinality; k++) {
        //printf("%s\n", array[k]);
    //}
    return 0;
}


