//Completed by Justin Or and Andrew Phuoc Nguyen
//Implement code to read data

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "set.h"

void LenCollection(void) {
    int i = 0;
    char* tmp;
    FILE* collection = fopen("Sample1/collection.txt", "r");
    if (collection != NULL) {
        while(fscanf(collection,"%s",tmp) != EOF) {
            printf("%d:%s\n", i, tmp);
            i++;
        }
    }
    fclose(collection)
    return i;
}

void GetCollection(void) {
    int i = 0;
    int len = LenCollection();
    char** list = (char**) malloc(len);
    for(int j = 0; j < len; j ++){
        list[j] = (char*) malloc(7)
    }
    char* tmp;
    FILE* collection = fopen("Sample1/collection.txt", "r");
    if (collection != NULL) {
        while(fscanf(collection,"%s",tmp) != EOF) {
            printf("%d:%s\n", i, tmp);
            strcpy(list[i],tmp);
            i++;
        }
    }
    for (int k = 0; k < i; k++) {
        printf("%s\n", array[k]);
    }   
    fclose(collection)
}


void GetGraph(char *urlList){
    graphSize = LenCollection();
    
    Graph g = newGraph(graphSize);
    
    for(int i = 0; i < graphSize; i++){
        for(int connection = 0; connection < graphSize; connection++){
            char *file_name = strdup(urlList[i]);
            FILE *open = fopen(file_name, "r");
            char * tmp;
            if( open != NULL){
                while(fscanf(open,"%s", tmp) != EOF){
                    for( int k = 0; k < graphSize; k++){
                        if (strcmp(urlList[k], tmp){
                            addEdge(g, urlList[i], urlList[k]);
                            break;
                        }
                    }
                }
            }
        }
    }
    showGraph(g);
}
