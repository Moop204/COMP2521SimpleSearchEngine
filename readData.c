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
    tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
    FILE* collection = fopen("Sample1/collection.txt", "r");//"Sample1/collection.txt", "r");
    //FILE* collection = fopen("Sample1/collection.txt", "r");
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
    tmp = (char*) malloc((SIZEOFURL) * sizeof(char));
    FILE* collection;
    collection = fopen("Sample1/collection.txt", "r");//"Sample1/collection.txt", "r");
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

Graph GetGraph(char** urlList) {
    int graphSize = LenCollection();
    Graph g = newGraph(graphSize);
    //return g;
    int i, k; //i is for each url.txt, k is for each link in url.
    char * tmp;     //where fscanf reads the urlnames
    char * hashtag; //where fscanf reads "#start" and "#end" 
    char * section; //where fscanf reads "Section-1" and "Section-2"
    for(i = 0; i < graphSize; i++){
        //printf("@i=%d\n", i);
        //char file_name[8+SIZEOFURL+4] = "Sample1/";
        char file_name[8+SIZEOFURL+4] = "Sample1/";
        strcat(strcat(file_name, urlList[i]),".txt");
        //printf("filename: %s\n", file_name);
        FILE *open = fopen(file_name, "r");
        tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
        hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
        section = (char*) malloc((10)*sizeof(char));
        if(open != NULL){
            if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return NULL;                 //error
            if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return NULL;     //error
            //printf("%s %s:\n",hashtag,section);
            while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0) {
                //printf("WHILE: tmp = %s\n", tmp);
                for (k = 0; k < graphSize; k++){
                    //printf("FOR k = %d\n", k);
                    if (strcmp(urlList[k], tmp) == 0) {
                        //printf("Adding an edge between %s and %s\n", urlList[i], urlList[k]);
                        if (i == k) continue;
                        addEdge(g, urlList[i], urlList[k]);
                        //break;
                    }
                }
            }
            //tmp == #end, make sure Section-1 is next and then close
            if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-1") == 0)) return NULL;//error
            //printf("%s %s. closing\n", tmp, section);
            //done, close and break to next iteration of connection.
        }
        fclose(open);
    }
    free(tmp);
    free(hashtag);
    free(section);
    showGraph(g,1);
    showGraph(g,0);
    return g;
}

int wordFrequency(char* word, char* url) {
    int f = 0; //f of the term
    
    //open inverted index, find N
    char file_name[8+SIZEOFURL+4] = "Sample1/";
    strcat(strcat(file_name,url),".txt");
    //printf("filename %s\n",file_name);

    FILE *open = fopen(file_name, "r");
    char* tmp;
    tmp = (char*) malloc((MAXWORD)*sizeof(char));
    char* hashtag;
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* section;
    section = (char*) malloc((MAXWORD)*sizeof(char));

    char *ftmp = tmp;
    char *fhashtag = hashtag;
    char *fsection = section;

    if(open != NULL){
        //scan through to Section-2
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return -1;                 //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return -2;     //error
        //printf("%s %s:\n",hashtag,section);
        while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0);
        //tmp == #end, make sure Section-1 is next and then close
        if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-1") == 0)) return -3;//error
        //check if at Section-2
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return -4;                 //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-2") != 0) return -5;     //error

        while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0) {
            //printf("tmp = %s\n",tmp);
            //normalise the word 
            tmp = RemoveSpecialCharacters(tmp);     // Removes special characters
            NormaliseWord(tmp); 
            if (strcmp(word, tmp) == 0) f++;
        }
        //tmp == #end, make sure Section-2 is next and then close
        if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) return -6;//error
        //done, close file
    }
    fclose(open);
    free(ftmp);
    free(fhashtag);
    free(fsection);

    return (f);
}


/*justin
pull wherever you want to merge
checkout where you want ot merge
merge justin*/
