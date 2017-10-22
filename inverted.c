// Completed by Justin Or and Andrew Nguyen
// Implemented with BST where key is a string and value is in a list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "inverted.h"
#include "set.h"

//prototypes in .h file

typedef struct IINode {         // Represents each word
    struct IINode  *next;
    char    *word;
    Queue   urls;               // Associated URLs are placed in a queue
} IINode;

typedef struct IIRep {
    IINode  *front;
    IINode  *end;
} IIRep;

//Function Signatures
void freeII (IIRep *r);
void AppendIINode(char *newWord, IIRep *rep);// Inserts node to word linked list in alphabetical order
void showIIRep(IIRep *rep);
IIRep *InitialiseRep(void);
Queue SearchIndex(char *word, IIRep *r);
int InvertedIndex(char **urlList);

int main(void) {
    int cardinality = LenCollection("collection.txt");
    int length = SIZEOFURL;
    char** urlList = GetCollection("collection.txt",cardinality, length);
    InvertedIndex(urlList);
    //free
    int i = 0;
    for (i = 0;i < cardinality;i++) {
        free(urlList[i]);
    }
    free(urlList);
    return 0;
}

void freeII (IIRep *r){         // Frees all memory associated with the InvertedIndex representation
    IINode *cur;
    // Remove memory of contents of IINodes  
    for(cur = r->front; cur != NULL; cur = cur->next){
        free(cur->word);
        disposeQueue(cur->urls);
    }
    // Remove memory of IINodes themselves
    while(cur != NULL){
        IINode *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(r);
}

// Adds a word to the Inverted Index
// Used when finding a new word
void AppendIINode(char *newWord, IIRep *rep){      // Inserts node to word linked list in alphabetical order
    IINode *newNode = malloc(sizeof(IINode));
    IINode *cur;

    newNode->word = malloc(strlen(newWord) + 1);
    strcpy(newNode->word, newWord);

    newNode->next = NULL;
    newNode->urls = newQueue();
    if(rep->end == NULL){
        rep->front = newNode;
        rep->end = newNode;
    }
    else{
        // Checks if it can be placed at the end
        if(isAlphaLess(rep->end->word, newWord) == 1){
            rep->end->next = newNode;
            rep->end = newNode;
        }
        // Checks if it can be placed in front
        else if(isAlphaLess(newWord, rep->front->word) == 1){
            newNode->next = rep->front;
            rep->front = newNode;
        }
        else{
            // Iterates through to find where to place
            for(cur = rep->front; cur != NULL; cur = cur->next){
                if(!isAlphaLess(cur->next->word, newWord)){
                    newNode->next = cur->next;
                    cur->next = newNode;
                    break;
                }
            }
        }
    }
}

// Displays the Inverted Index
void showIIRep(IIRep *rep) {
    if (rep == NULL) return;
    if (rep->front == NULL || rep->end == NULL) return;
    IINode *cur;
    for (cur = rep->front; ; cur = cur->next) {
        printf("<<%s>>",cur->word);
        showQueue(cur->urls);
        if (cur == rep->end) break;
    }
}

// Create Inverted Index
IIRep *InitialiseRep(void){
    IIRep *newRep = malloc(sizeof(IIRep));
    newRep->front = NULL;
    newRep->end = NULL;
    return newRep;
}

// Finds queue associated with a word
Queue SearchIndex(char *word, IIRep *r){
    IINode *cur; 
    for(cur = r->front; cur != NULL; cur = cur->next){
        if(strcmp(cur->word, word)==0){
            return cur->urls;
        }
    } 
    return NULL;
}

// Calculates and writes the inverted index to the invertedIndex.txt file
int InvertedIndex(char **urlList){
    int len = LenCollection("collection.txt");
    // Strings used for editing (strcat)
    char ** dupList = malloc(len * (SIZEOFURL + sizeof(".txt")));
    int p;
    for(p = 0; p < len; p++){
        dupList[p] = malloc(strlen(urlList[p]) + 1);
        strcpy(dupList[p], urlList[p]);
    }
    // Initialising variables
    IIRep *r = InitialiseRep();
    Set sGlobal = newSet();
    int i;
    char *tmp = calloc(MAXWORD, sizeof(char));
    char * hashtag; //where fscanf reads "#start" and "#end" 
    char * section; //where fscanf reads "Section-1" and "Section-2"
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    section = (char*) malloc((10)*sizeof(char));

    // Pointers to intial memory addresses
    // Holds initial memory location for freeing
    char* ftmp = tmp;           
    char* fhashtag = hashtag;
    char* fsection = section;

    // Generating Inverted Index    
    // Searches for all urls
    for(i = 0; i < len; i++){
        char urlname[sizeof("Sample1/") + SIZEOFURL + sizeof(".txt")] = "Sample1/";
        Set sLocal = newSet();
        strcat(urlname,strcat(dupList[i],".txt"));
        FILE *fptext = fopen(urlname, "r");                                                 // Opens up url
        if(fptext != NULL){
            if (!(fscanf(fptext,"%s %s",hashtag, section) == 2)) return 1;                  //error
            if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return 1;        //error
            while(!(fscanf(fptext,"%s",section) == 1 && strcmp(section,"Section-2") == 0));
            while ((fscanf(fptext,"%s",tmp) != EOF) && strcmp(tmp,"#end") != 0 ) {          // Reads by character
                tmp = RemoveSpecialCharacters(tmp);         // Removes special characters
                NormaliseWord(tmp);                         // Converts words to lowercase
                // For words never seen before, create a head node that holds all urls containing it
                if(!isElem(sGlobal, tmp)){            
                    insertInto(sGlobal, tmp);
                    AppendIINode(tmp, r);
                }
                if(!isElem(sLocal, tmp)) {
                    insertInto(sLocal, tmp);               // For words not seen before, insert url into the word node
                    Queue urlQ = SearchIndex(tmp,r);
                    enterQueue(urlQ, urlList[i]);
                }
                //^everything after works ok (frees are ok, when queue and IINode is used the frees dont match up (eg 2 more frees than usual)
            }
            // check if next word is "Section-2", and finish
            if (!(fscanf(fptext,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) {
                return 1;   //error
            }
        }
        fclose(fptext);
        disposeSet(sLocal);
    }

    disposeSet(sGlobal);    // Cleanup memory
    free(fhashtag);
    free(fsection);
    free(ftmp);
    free(hashtag);
    free(section);

    // Writing Process    
    FILE *fp = fopen("invertedIndex.txt", "w");
    IINode *cur;
    for(cur = r->front; cur != NULL; cur = cur->next){
        fprintf(fp, "%s  ", cur->word);                 // Writes word
        Queue url_q = cur->urls;
        char* url = malloc(sizeof(urlList[0]));
        char* furl = url;
        if (!emptyQueue(url_q)) {
            for(url = leavePriorQueue(url_q); ; url = leavePriorQueue(url_q)){
                fprintf(fp, "%s ", url);                // Writes urls
                if (emptyQueue(url_q)) break;         
            }
        }
        free(furl);
        fprintf(fp,"\n");
    }
    fclose(fp);     // Cleanup memory
    freeII(r);
    for(p = 0; p < len; p++) free(dupList[p]);
    free(dupList);
    return 0;
}


