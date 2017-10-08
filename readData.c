//Completed by Justin Or and Andrew Phuoc Nguyen
//Implement code to read data

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "set.h"
#include "queue.h"

void GetCollection(void) {
    char array[7][7];
    //initialising the char** list of strings
    char** list;
    int elements = 7;
    int length = SIZEOFURL;
    
    list = malloc(elements * length);
    for (int i = 0; i < elements; i++) {
        list[i] = malloc((SIZEOFURL) * sizeof(char));
    }
    
    int i = 0;  
    char* tmp;
    FILE* collection;
    collection = fopen("Sample1/collection.txt", "r");
    printf("%p\n", collection);
    if (collection != NULL) {
        printf("if(collection) == TRUE\n");
        while (fscanf(collection,"%s",tmp) != EOF) {
            printf("%dth array list\n", i);
            printf("%d: %s\n", i, tmp);
            strcpy(list[i],tmp);
            i++;
        }
    }
    for (int k = 0; k < i; k++) {
        printf("%s\n", list[k]);
    }
    fclose(collection); 
}























/*int GetCardinality(void);

int GetCollection(int cardinality, int length, char array[cardinality][length]) {
    int i = 0;
    char* tmp;
    FILE* collection = fopen("Sample1/collection.txt", "r");
    if (collection == NULL) return 0;
    else {
        while(fscanf(collection,"%s",tmp) != EOF) {
            printf("%d:%s\n", i, tmp);
            strcpy(array[i],tmp);
            //enterQueue(q,tmp);
            i++;
        }
    }
    //for (int k = 0; k < i; k++) {
        //strcpy(array[k], leaveQueue(q));
        //printf("%s\n", array[k]);
    //}
    return 1;
}

int GetCardinality(void) {
    int i = 0;
    char* tmp;
    FILE* collection = fopen("Sample1/collection.txt", "r");
    if (collection == NULL) return 0;//error
    else {
        while(fscanf(collection,"%s",tmp) != EOF) {
            printf("%d:%s\n", i, tmp);
            i++;
        }
        return i;
    }
}*/

