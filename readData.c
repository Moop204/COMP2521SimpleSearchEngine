//Completed by Justin Or and Andrew Phuoc Nguyen
//Implement code to read data
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "set.h"
#include "queue.h"
#include "graph.h"

int LenCollection(void) {
    int i = 0;
    char* tmp;
    tmp = (char*) malloc((7)*sizeof(char));
    FILE* collection = fopen("Sample1/collection.txt", "r");
    if (collection != NULL) {
        while(fscanf(collection,"%s",tmp) != EOF) {
            i++;
        }
    }
    fclose(collection);
    return i;
}


char** GetCollection(int elements, int length) {
    //initialising the char** list of strings
    char** list;
    list = malloc(elements * length);
    int i;
    for (i = 0; i < elements; i++) {
        list[i] = malloc((SIZEOFURL) * sizeof(char));
    }
    i = 0;
    char* tmp;
    tmp = (char*) malloc((7)*sizeof(char));
    FILE* collection;
    collection = fopen("Sample1/collection.txt", "r");
    if (collection != NULL) {
        fscanf(collection, "%s", tmp);
        while (fscanf(collection,"%s",tmp) != EOF) {
            //printf("%d: %s\n", i, tmp);
            strcpy(list[i],tmp);//list[i] = strdup(tmp);
            i++;
        }
    }
    fclose(collection);
    return list;
}


/*justin
pull wherever you want to merge
checkout where you want ot merge
merge justin*/
