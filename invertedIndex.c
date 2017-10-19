// Completed by Justin Or and Andrew Nguyen
// Implemented with BST where key is a string and value is in a list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "set.h"


void NormaliseWord(char* word);             // Taken from lab08 of COMP2521
//void RemoveSpecialCharacters(char* word);   // Returns a string without special characters
char *RemoveSpecialCharacters(char *word);


typedef struct IINode {
    struct IINode  *next;
    char    *word;
    Queue   urls;
} IINode;

typedef struct IIRep {
    IINode  *front;
    IINode  *end;
} IIRep;


/*
typedef struct URLNode {
    char    *url;
    URLNode *next_url;
} URLNode;
*/


void AppendIINode(char *word, IIRep *rep){      // Inserts node to word linked list in alphabetical order
    IINode *newNode = malloc(sizeof(IINode));
    IINode *cur;
    newNode->word = word;
    newNode->next = NULL;
    newNode->urls = newQueue();
    if(rep->end == NULL){
        rep->front = newNode;
        rep->end = newNode;
    }
    else{
        if(isAlphaLess(rep->end->word, word)){
            rep->end->next = newNode;
            rep->end = newNode;
        }
        else if(isAlphaLess(word, rep->front->word)){
            newNode->next = rep->front;
            rep->front = newNode;
        }
        else{
            for(cur = rep->front; cur != NULL; cur = cur->next){
                if(!isAlphaLess(cur->next->word, word)){
                    newNode->next = cur->next;
                    cur->next = newNode;
                    break;
                }
            }
        }
    }
}

IIRep *InitialiseRep(void){
    IIRep *newRep = malloc(sizeof(IIRep));
    newRep->front = NULL;
    newRep->end = NULL;
    return newRep;
}

Queue SearchIndex(char *word, IIRep *r){
    IINode *cur;
    for(cur = r->front; cur != NULL; cur = cur->next){
        if(strcmp(cur->word, word)){
            return cur->urls;
        }
    } 
    printf("YOU DONE MESSED UP MATE");
    return NULL;
}


int InvertedIndex(char **urlList){

    Set sGlobal = newSet();                 // 
    Set  sLocal = newSet();
    int len = LenCollection();
    char *tmp;
    IIRep *r = InitialiseRep();
    int i;
    for(i = 0; i < len; i++){
        FILE *fptext = fopen(strcat(urlList[i],".txt"), "r");      // Opens up url
        while (fscanf(fptext,"%s",tmp) != EOF) {    // Reads by character
            tmp = RemoveSpecialCharacters(tmp);     // Removes special characters
            NormaliseWord(tmp);                     // Converts words to lowercase
            if(!isElem(sGlobal, tmp)){              // For words never seen before, create a head node that holds all urls containing it
                insertInto(sGlobal, tmp);           
                AppendIINode(tmp, r);
            }
            if(!isElem(sLocal, tmp)){
                insertInto(sLocal, tmp);           
                Queue url_list = SearchIndex(tmp,r);
                enterQueue(url_list, tmp);
            }
        }
        fclose(fptext);
        disposeSet(sLocal);
    }



    FILE *fp = fopen("invertedIndex.txt", "w");
    IINode *cur;
    for(cur = r->front; cur != NULL; cur = cur->next){
        fprintf(fp, "%s  ", cur->word);
        Queue url_q = cur->urls;
        
        //fwrite(invertedIdx, 1, sizeof(invertedIdx), fp);
        char* url;
        for(url = leavePriorQueue(url_q); !emptyQueue(url_q); url = leavePriorQueue(url_q)){
            fprintf(fp, "%s ", url);            
        }
    }
    fclose(fp);
    return 0;

}

char *RemoveSpecialCharacters(char* str){
    char *standardStr = malloc(sizeof(str));
    int len = strlen(str);
    int idx = 0;
    int i;
    for(i = 0; i < len; i++){
        if(str[i] != '.' && str[i] != ';' && str[i] != '?'){
            standardStr[idx] = str[i];
            idx++;
        }

    }
    standardStr[idx] = '\0';
    return standardStr;
}


/*
// Code obtained from lab08 of COMP2521 course provided by UNSW CSE Faculty

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
  while (word[i]) {
      // NEW
    if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 32;
    i++;
  }
}
