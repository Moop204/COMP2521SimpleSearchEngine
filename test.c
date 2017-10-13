#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"


int main (void) {
    int cardinality = LenCollection();
    int length = SIZEOFURL;
    //if (!cardinality) return 1;
    //char array[cardinality][URLNAMELEN];
    //if (!GetCollection(cardinality, URLNAMELEN, array[cardinality][URLNAMELEN])) return 1;
    char** urlList = GetCollection(cardinality, length);
    int k;
    for (k = 0; k < cardinality; k++) {
        printf("%s\n", urlList[k]);
    }
    GetGraph(urlList);
    return 0;
}
