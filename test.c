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
    int cardinality = LenCollection("Sample1/collection.txt");
    int length = SIZEOFURL;
    char** urlList = GetCollection(cardinality, length);
    Graph g = GetGraph(urlList);
    PageRankW(0.850000,0.000010,1000);
    
    InvertedIndex(urlList);
    //double k = tf("mars", "url11");
    //printf("tf = %lf\n", k);
    //k = idf("mars");
    //printf("idf = %lf\n", k);
    //k = tfIdf("mars", "url11");
    //printf("tfidf = %lf\n", k);

//    double k = tf("mars", "url11");
//    double l = idf("mars");
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
    disposeGraph(g);
    i = 0;
    for (;i < cardinality;i++) {
        free(urlList[i]);
    }
    free(urlList);
    return 0;

}
