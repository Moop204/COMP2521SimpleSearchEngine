//Completed by Justin Or and Andrew Phuoc Nguyen
//Implement code to read data

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "set.h"

void GetCollection(void) {
    char array[7][6];
    int i = 0;
    char* tmp;
    FILE* collection = fopen("Sample1/collection.txt", "r");
    if (collection != NULL) {
        while(fscanf(collection,"%s",tmp) != EOF) {
            printf("%d:%s\n", i, tmp);
            strcpy(array[i],tmp);
            i++;
        }
    }
    for (int k = 0; k < i; k++) {
        printf("%s\n", array[k]);
    }
}
