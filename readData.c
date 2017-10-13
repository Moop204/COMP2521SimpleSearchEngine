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
    free(tmp);
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
        while (fscanf(collection,"%s",tmp) != EOF) {
            //printf("%d: %s\n", i, tmp);
            strcat(tmp, "\0");
            strcpy(list[i],tmp);//list[i] = strdup(tmp);
            i++;
        }
    }
    fclose(collection);
    free(tmp);
    return list;
}

void GetGraph(char** urlList){
    int graphSize = LenCollection();
    Graph g = newGraph(graphSize);
    int i,k,connection;
    for(i = 0; i < graphSize; i++){
        for(connection = 0; connection < graphSize; connection++){
            printf("@connection=%d\n", connection);
            char file_name[8+SIZEOFURL] = "Sample1/";
            if (urlList[i] == " ") continue;
            strcat(file_name, urlList[i]);
            strcat(file_name, ".txt");
            printf("filename: %s\n", file_name);
            FILE *open = fopen(file_name, "r");
            char * tmp;
            tmp = (char*) malloc((7)*sizeof(char));
            if(open != NULL){
                //printf("HELLO\n");
                while(fscanf(open,"%s", tmp) != EOF){
                    //printf("WHILE\n");
                    for (k = 0; k < graphSize; k++){
                        //printf("FOR\n");
                        if (strcmp(urlList[k], tmp) == 0) {
                            printf("Adding an edge between %s and %s\n", urlList[i], urlList[k]);
                            addEdge(g, urlList[i], urlList[k]);
                            break;
                        }
                    }
                }
            }
            fclose(open);
        }
    }
    showGraph(g,0);
}

/*justin
pull wherever you want to merge
checkout where you want ot merge
merge justin*/
