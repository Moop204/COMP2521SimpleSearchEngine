#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"

int main (void) {
    int cardinality = LenCollection();
    int length = SIZEOFURL;
    char** urlList = GetCollection(cardinality, length);
    //GetGraph(urlList);
 //   PageRankW(0.850000,0.000010,1000);
 //   for(int i = 0; i < cardinality; i++){
 //       printf("Line: %s\n", urlList[i]);
 //   }
//    printf("%d", cardinality);
    InvertedIndex(urlList);
    return 0;

}
