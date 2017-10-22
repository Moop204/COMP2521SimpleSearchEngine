//Completed by Justin Or and Andrew Phuoc Nguyen
//Implement code to read data
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "inverted.h"
#include "set.h"
#include "queue.h"
#include "graph.h"


int LenCollection(char* file) {
    int i = 0;
    char* tmp;
    tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
    FILE* collection = fopen(file, "r");
    if (collection != NULL) {
        while(fscanf(collection,"%s",tmp) != EOF) {
            i++;
        }
    }
    fclose(collection);
    free(tmp);
    return i;
}


char** GetCollection(char* file, int elements, int length) {
    // initialising the char** list of strings
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
    collection = fopen(file, "r");
    if (collection != NULL) {
        while (fscanf(collection,"%s",tmp) != EOF) {
            strcat(tmp, "\0");
            strcpy(list[i],tmp);       
            i++;
        }
    }
    fclose(collection);
    free(tmp);
    return list;
}

Graph GetGraph(char** urlList) {
    // initialising variables
    int graphSize = LenCollection("collection.txt");
    Graph g = newGraph(graphSize);
    int i, k;   // i is for each url.txt, k is for each link in url.
    char * tmp;     // where fscanf reads the urlnames
    char * hashtag; // where fscanf reads "#start" and "#end" 
    char * section; // where fscanf reads "Section-1" and "Section-2"

    // searches in specific url
    for(i = 0; i < graphSize; i++){
        // setup pointers
        char file_name[sizeof("")+SIZEOFURL+sizeof(".txt")] = "";
        strcat(strcat(file_name, urlList[i]),".txt");
        FILE *open = fopen(file_name, "r");
        tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
        hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
        section = (char*) malloc((10)*sizeof(char));

        if(open != NULL){
            if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return NULL;                 //error
            if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return NULL;     //error
            // searches file for url
            while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0) {
                for (k = 0; k < graphSize; k++){
                    if (strcmp(urlList[k], tmp) == 0) {
                        if (i == k) continue;
                        addEdge(g, urlList[i], urlList[k]);
                    }
                }
            }

            // tmp == #end, make sure Section-1 is next and then close
            if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-1") == 0)) 
                return NULL;    //error
            // done, close and break to next iteration of connection.
        }
        fclose(open);
        free(tmp);
        free(hashtag);
        free(section);
    }
    return g;
}

int wordFrequency(char* word, char* url) {
    // initialise variables
    int f = 0; // frequency of the term
    // open inverted index, find N
    char file_name[sizeof("")+SIZEOFURL+sizeof(".txt")] = "";
    strcat(strcat(file_name,url),".txt");
    FILE *open;
    if( (open = fopen(file_name, "r")) == NULL ) return -10;
    char* tmp;
    tmp = (char*) malloc((MAXWORD)*sizeof(char));
    char* hashtag;
    hashtag = (char*) malloc((MAXWORD)*sizeof(char));
    char* section;
    section = (char*) malloc((MAXWORD)*sizeof(char));

    char *ftmp = tmp;
    char *fhashtag = hashtag;
    char *fsection = section;

    if(open != NULL){

        // scan through to Section-2
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return -1;                 //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return -2;     //error
        while((fscanf(open,"%s", hashtag) != EOF) && strcmp(hashtag,"#end") != 0);
        // tmp == #end, make sure Section-1 is next and then close
        if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-1") == 0)) 
            return -3;      //error

        // check if at Section-2
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return -4;                 //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-2") != 0) 
            return -5;      //error

        // finds and counts instances of the word
        while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0){
            RemoveSpecialCharacters(tmp);     // Removes special characters
            NormaliseWord(tmp); 
            if (strcmp(word, tmp) == 0) f++;            
        }

        // tmp == #end, make sure Section-2 is next and then close
        if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) return -6;    //error
        // done, close file

    }
    // freeing memory
    fclose(open);
    free(ftmp);
    free(fhashtag);
    free(fsection);
    return (f);
}

int wordTotal( char* url) {
    int f = 0; // frequency of the term    
    // open inverted index, find N
    char file_name[sizeof("")+SIZEOFURL+sizeof(".txt")] = "";
    strcat(strcat(file_name,url),".txt");
    FILE *open = fopen(file_name, "r");
    char* tmp;
    tmp = (char*) malloc((MAXWORD)*sizeof(char));
    char* hashtag;
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* section;
    section = (char*) malloc((MAXWORD)*sizeof(char));
    // pointers to initial memory
    char *ftmp = tmp;
    char *fhashtag = hashtag;
    char *fsection = section;

    if(open != NULL){

        // scan through to Section-2
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) 
            return -1;              //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0)  
            return -2;              //error
        while((fscanf(open,"%s", hashtag) != EOF) && strcmp(hashtag,"#end") != 0);
        // tmp == #end, make sure Section-1 is next and then close
        if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-1") == 0)) 
            return -3;              //error

        // check if at Section-2
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) 
            return -4;              //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-2") != 0) 
            return -5;              //error

        // begins counting number of words
        while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0){
            f++;            
        }

        // tmp == #end, make sure Section-2 is next and then close
        if (!(fscanf(open,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) return -6;//error
        // done, close file

    }
    // freeing memory
    fclose(open);
    free(ftmp);
    free(fhashtag);
    free(fsection);

    return (f);
}


char *RemoveSpecialCharacters(char* str){
    int len = strlen(str);
    int i;
    for(i = 0; i < len; i++){
        if(str[i] == '.' || str[i] == ';' || str[i] == '?' || str[i] == ','){
            str[i] = '\0';
        }
    }
    return str;
}


/*
// Code obtained from lab08 of COMP2521 course provided by UNSW CSE Faculty 
// and edited by Andrew Phuoc Nguyen
*NormalizeWord*
---------------
Description: Make sure all the Roman letters in the URL are
of lower cases, for ease of carrying out string comparison in
the future when trying to decide if two URL are the same or not.
Basically a linear scan, starting from the beginning of the URL,
is performed. Whenever a capital letter character is encountered
(by checking its ASCII code value), it is replaced by the
corresponding lower case letter.
Input: input_url
** Pseudo Code **
(1) FOR (every character in the input string) DO
      IF (this character is a capital letter) DO
        Change this letter to lower case
      END
    DONE
*****
*/

void NormaliseWord(char* word)
{
  int i = 0;
  while (word[i] != '\0') {
      // NEW
    if (word[i] <= 'Z' && word[i] >= 'A') // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 'a' - 'A';
    i++;
    if(word[i] == '\0') break;
  }
}

void shiftRight(int *list, int pos, int max){
    int cur;
    for(cur = max-1; cur > pos; cur --){
        list[cur] = list[cur-1];
    }
}

