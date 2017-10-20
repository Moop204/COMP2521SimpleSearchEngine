#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"
#include "searchTfIdf.h"

#define DEBUGWORDSIZE  50
#define DEBUGNELEM     1

int main (void) {
/*    int cardinality = LenCollection();
    int length = SIZEOFURL;
    char** urlList = GetCollection(cardinality, length);
    GetGraph(urlList);
    PageRankW(0.850000,0.000010,1000);
    InvertedIndex(urlList);
*/
//    double k = tf("mars", "url11");
//    double l = idf("mars", "url11");
//    double m = tfIdf("mars", "url11");
//    printf("tf = %lf\n", k);
//    printf("idf = %lf\n", l);
//    printf("tfidf = %lf\n", m);
    
    char** list;
    list = malloc(DEBUGNELEM * DEBUGWORDSIZE);
    int i;
    for (i = 0; i < DEBUGNELEM; i++) {
        list[i] = malloc((DEBUGWORDSIZE) * sizeof(char));
    }
    list[0] = "mars";
    searchTfIdf(list, DEBUGNELEM);

    //for(int i = 0; i < cardinality; i++){
    //    printf("Line: %s\n", urlList[i]);
    //}
    //printf("%d", cardinality);
    return 0;

}
