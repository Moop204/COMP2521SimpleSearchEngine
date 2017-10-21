// searchPagerank.c
// Given search terms (words) as commandline arguments, finds pages with one or more search terms 
// and outputs (to stdout) top 30 pages in descending order of number of search terms found and 
// then within each group, descending order of Weighted PageRank. If number of matches are less
// than 30, output all of them. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pageRank.h"
#include "readData.h"
#include "invertedIndex.h"

#define MAXPRINT 30

double readPageRank(char* url);

/*int main(int argc, char **argv){
    int cardinality = LenCollection("Sample1/collection.txt");
    int length = SIZEOFURL;
    char** urlList = GetCollection(cardinality, length);

    InvertedIndex(urlList);
*//*
    assert(argc > 1);

    int length = LenCollection();
    char **collection = GetCollection(length, SIZEOFURL);   // INITIAL ORDER reference
    int *listFreq = calloc(length, sizeof(int));            // INITIAL ORDER of frequency
    double *listPgRank = calloc(length, sizeof(int));

    PageRankW(0.850000, 0.000010, 1000);
 
    int idx;
    for(idx = 0; idx < argc; idx++){
        char *arg = argv[idx];
        int nUrls;
        for(nUrls = 0; nUrls < length; nUrls++){
            listFreq[nUrls] += wordFrequency(arg, collection[nUrls]); 
        }
    }

    // Inserts page rank of all pages
    int nUrls;
    for(nUrls = 0; nUrls < length; nUrls++){
        listPgRank[nUrls] = readPageRank(collection[nUrls]); 
    }

    int *listPrint = calloc(MAXOUTPUT, sizeof(int));        // order of printing, refers to INITIAL ORDER in order

    int i;

    for(i = 0; i < MAXOUTPUT; i++){
        listPrint[i] = -1;
    }

    // Selects order of printing
    for(i = 0; i < length; i++){                    // Iterates INITIAL ORDER
        int val = listFreq[i];
        int e;
        // Iterates printing order until it finds a new place or finds a lower val
        if(val != 0){
            for(e = 0; e < MAXOUTPUT; e++){         
                int printRef = listPrint[e];
                if(printRef == -1){                 // Top 30 has free spot
                    listPrint[e] = i;
                    break;
                }
                else{
                    // Compares ONLY frequency of term
                    if(val > listFreq[printRef]){ 
                        shiftRight(listPrint, e, MAXOUTPUT);
                        listPrint[e] = i;
                        break;
                    }
                    // Compares pagerank of those with equal frequency
                    else if(val == listFreq[printRef]){
                        if(listPgRank[i] > listPgRank[printRef]){
                            shiftRight(listPrint, e, MAXOUTPUT);
                            listPrint[e] = i; 
                            break;
                        }
                    }
                }
            }
        }
        else continue;
    }   

    for(i = 0; i < MAXOUTPUT; i++){
        if(listPrint[i] == -1)
            break;
        else{
            int ref = listPrint[i];
            printf("%s %d %.7lf\n", collection[ref], listFreq[ref], listPgRank[ref]);
        }
    }
 
    for(idx = 0; idx < length; idx++)free(collection[idx]);
    free(collection);
    free(listFreq);
*/
  /*  return 0;
}*/


double readPageRank(char* url){
    char* tmp = calloc(MAXWORD, sizeof(char));
    char* comparison = malloc(sizeof(url) + 1);
    comparison = strcat(strdup(url),",");
    FILE *open = fopen("pagerankList.txt", "r");    
    double result;
    if(open != NULL){
        while(fscanf(open, "%s", tmp) != EOF && strcmp(tmp, comparison) != 0){};
     	fscanf(open, "%s", tmp); //Passes output count
        if(fscanf(open, "%lf", &result) != EOF){
            free(tmp);
            free(comparison);
            return result;
        }
        else{
            printf("%s\n", tmp);
            return -1.0; // Error
        }
    }
    return -1.0; // Error     
}
