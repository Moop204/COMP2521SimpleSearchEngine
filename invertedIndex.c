// Completed by Justin Or and Andrew Nguyen
// Implemented with BST where key is a string and value is in a list

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "invertedIndex.h"
#include "set.h"

//prototypes in .h file


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


void AppendIINode(char *newWord, IIRep *rep){      // Inserts node to word linked list in alphabetical order
    IINode *newNode = malloc(sizeof(IINode));
    IINode *cur;
    newNode->word = strdup(newWord);
    newNode->next = NULL;
    newNode->urls = newQueue();
    printf("ive done nothing\n");
    if(rep->end == NULL){
        printf("it nulled?\n");
        rep->front = newNode;
        rep->end = newNode;
        printf("True %d\n\n", (rep->front == NULL));
    }
    else{
        printf("%s\n",rep->front->word);
        printf("invertedIndex.c 52\n");
        if(isAlphaLess(rep->end->word, newWord) == 1){
            printf("end:is %s less than %s? 1\n",rep->end->word,newWord);
            rep->end->next = newNode;
            rep->end = newNode;
        }
        else if(isAlphaLess(newWord, rep->front->word) == 1){
            printf("past the first COND\n");
            printf("start:is %s less than %s? 1\n",rep->front->word,newWord);
            newNode->next = rep->front;
            rep->front = newNode;
        }
        else{
            printf("THIRD COND\n");
            for(cur = rep->front; cur != NULL; cur = cur->next){
                printf("is %s less than %s? %d\n",cur->next->word,newWord,isAlphaLess(cur->next->word, newWord));
	//	printf("check %s",cur->next->word);
                if(!isAlphaLess(cur->next->word, newWord)){
                    newNode->next = cur->next;
                    cur->next = newNode;
                    break;
                }
            }
        }
    }
}

/*void showIIRep(IIRep *rep){      // Inserts node to word linked list in alphabetical order
    IINode *newNode = malloc(sizeof(IINode));
    IINode *cur;
    if(rep->end == NULL){
        printf("it nulled?\n");
        rep->front = newNode;
        rep->end = newNode;
        printf("True %d\n\n", (rep->front == NULL));
    }
}*/
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

IIRep *InitialiseRep(void){
    IIRep *newRep = malloc(sizeof(IIRep));
    newRep->front = NULL;
    newRep->end = NULL;
    return newRep;
}

Queue SearchIndex(char *word, IIRep *r){
    IINode *cur;
    //printf("YOU DONE MESSED UP MATE1\n");
    for(cur = r->front; cur != NULL; cur = cur->next){
            //printf("YOU DONE MESSED UP MAT\n");
        if(strcmp(cur->word, word)==0){
            return cur->urls;
        }
    } 
    //printf("YOU DONE MESSED UP MATE\n");
    return NULL;
}


int InvertedIndex(char **urlList){

    int len = LenCollection();

    char ** dupList = malloc(sizeof(urlList));
    int p;
/*    for(p = 0; p < len; p++){
        dupList[p] = malloc(sizeof(urlList[0]));
    }
*/
    for(p = 0; p < len; p++){
        dupList[p] = strdup(urlList[p]);
    }

    char *tmp = calloc(MAXWORD, sizeof(char));
    IIRep *r = InitialiseRep();
    int i;
    char * hashtag; //where fscanf reads "#start" and "#end" 
    char * section; //where fscanf reads "Section-1" and "Section-2"
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    section = (char*) malloc((10)*sizeof(char));

    Set sGlobal = newSet();                 // 
    for(i = 0; i < len; i++){
        char urlname[8+6+4+1] = "Sample1/";
        Set sLocal = newSet();
        strcat(urlname,strcat(urlList[i],".txt"));
        printf("%s\n",urlname);
        FILE *fptext = fopen(urlname, "r");      // Opens up url
        if(fptext != NULL){
            if (!(fscanf(fptext,"%s %s",hashtag, section) == 2)) return 1;                 //error
            if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return 1;     //error
            while(!(fscanf(fptext,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) printf("hi");
            while ((fscanf(fptext,"%s",tmp) != EOF) && strcmp(tmp,"#end") != 0 ) {    // Reads by character
                printf("IVE ENTERED THE NEXT WHILE LOOP \n");
                printf("bug %s\n", tmp);
                tmp = RemoveSpecialCharacters(tmp);     // Removes special characters
                NormaliseWord(tmp);                     // Converts words to lowercase
                printf("toptmp=%s\n",tmp);

                if(!isElem(sGlobal, tmp)){              // For words never seen before, create a head node that holds all urls containing it
                    printf("PRE");
                    insertInto(sGlobal, tmp);
                    printf("is an element of sGlobal now 131 inv\n");           
                    AppendIINode(tmp, r);
                }
                printf("ASD\n");
                printf("%d\n", isElem(sGlobal,tmp));
                printf("%d\n", isElem(sLocal,tmp));
                if(!isElem(sLocal, tmp)) {
                    insertInto(sLocal, tmp);               // For words not seen before, insert url into the word node
                    Queue url_list = SearchIndex(tmp,r);
                    enterQueue(url_list, dupList[i]);
                    showQueue(url_list);
                    showIIRep(r);
                    printf("show me\n");
                }
                printf("HELLO\n");
            }
            //check if next word is "Section-2", and finish
            printf("ghasdtmp=%s\n",tmp);
            if (!(fscanf(fptext,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) {
                printf("YOU FUCKED UP\n");                
                return 1;//error
            }
        }
        fclose(fptext);
        disposeSet(sLocal);
    }
    disposeSet(sGlobal);

/*
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

*/
    FILE *fp = fopen("invertedIndex.txt", "w");
    IINode *cur;
    for(cur = r->front; cur != NULL; cur = cur->next){
        fprintf(fp, "%s  ", cur->word);
        printf("%s WORD\n", cur->word);
        Queue url_q = cur->urls;
        printf("DA QUEUE\n");
        showQueue(url_q);
        //fwrite(invertedIdx, 1, sizeof(invertedIdx), fp);
        char* url = malloc(sizeof(urlList[0]));
	    printf("dicks\n");
        for(url = leavePriorQueue(url_q); ; url = leavePriorQueue(url_q)){
            printf("Look at me im mr meeseeks\n");
            fprintf(fp, "%s ", url);   
            if (emptyQueue(url_q)) break;         
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    return 0;

}

char *RemoveSpecialCharacters(char* str){
    int len = strlen(str);
    int i;
    for(i = 0; i < len; i++){
        printf("str[%d] = %c\n", i, str[i]);
        if(str[i] == '.' || str[i] == ';' || str[i] == '?'){
            str[i] = '\0';
        }

    }
    printf("stridx = %s\n", str);
    return str;
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
