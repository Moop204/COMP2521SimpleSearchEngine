#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"


int main (void) {
    int cardinality = LenCollection();
    int length = SIZEOFURL;
    //if (!cardinality) return 1;
    //char array[cardinality][URLNAMELEN];
    //if (!GetCollection(cardinality, URLNAMELEN, array[cardinality][URLNAMELEN])) return 1;
    char** urlList = GetCollection(cardinality, length);
    int k;
    GetGraph(urlList);
    PageRankW(0.85,0.00001,10);
    return 0;
}
