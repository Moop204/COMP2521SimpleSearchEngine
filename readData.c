//Completed by Justin Or and Andrew Phuoc Nguyen
//Implement code to read data

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"

void GetCollection(void) {
    //read file "Sample1/collection.txt"
    char* array[10];
    int i = 0;
    printf("hello1");
    char *tmp;
    FILE* collection = fopen("Sample1/collection.txt", "r");
    printf("hello2\n");
    if (collection != NULL) {
        printf("hi\n");
        while(fscanf(collection,"%s",tmp) != EOF){
            //its working
            printf("%d:%s\n", i, tmp);

            array[i] = strdup(tmp);
            printf("%d ", i);
            printf("%s\n", array[i]);

            //printf("%s\n", array[i]);
            i++;

        }
    }
    int k = 0;
    for (k=0;k<i ;k++) {
        printf("%s\n", array[k]);
    }
    //}

}

/*justin
pull wherever you want to merge
checkout where you want ot merge
merge justin*/
