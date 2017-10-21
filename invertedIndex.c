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


void freeII (IIRep *r){
    IINode *cur;
    for(cur = r->front; cur != NULL; cur = cur->next){
        free(cur->word);
        disposeQueue(cur->urls);
        free(cur->urls); 
    }
    while(cur != NULL){
        IINode *tmp = cur;
        cur = cur->next;
        free(tmp->next);
        free(tmp);
    }
    free(r->front);
    free(r->end);
    free(r);
}

void AppendIINode(char *newWord, IIRep *rep){      // Inserts node to word linked list in alphabetical order
    IINode *newNode = malloc(sizeof(IINode));
    IINode *cur;
    newNode->word = strdup(newWord);
    newNode->next = NULL;
    newNode->urls = newQueue();
    if(rep->end == NULL){
//        printf("it nulled?\n");
        rep->front = newNode;
        rep->end = newNode;
//        printf("True %d\n\n", (rep->front == NULL));
    }
    else{
        //printf("%s\n",rep->front->word);
        if(isAlphaLess(rep->end->word, newWord) == 1){
//            printf("end:is %s less than %s? 1\n",rep->end->word,newWord);
            rep->end->next = newNode;
            rep->end = newNode;
        }
        else if(isAlphaLess(newWord, rep->front->word) == 1){
//            printf("start:is %s less than %s? 1\n",rep->front->word,newWord);
            newNode->next = rep->front;
            rep->front = newNode;
        }
        else{
            for(cur = rep->front; cur != NULL; cur = cur->next){
//                printf("is %s less than %s? %d\n",cur->next->word,newWord,isAlphaLess(cur->next->word, newWord));
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

void showIIRep(IIRep *rep) {
    if (rep == NULL) return;
    if (rep->front == NULL || rep->end == NULL) return;
    IINode *cur;
    for (cur = rep->front; ; cur = cur->next) {
        printf("<<%s>>",cur->word);
        //showQueue(cur->urls);
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

    int len = LenCollection("Sample1/collection.txt");

    char ** dupList = malloc(sizeof(urlList));
    int p;
    /*for(p = 0; p < len; p++){
        dupList[p] = malloc(sizeof(urlList[0]));
    }*/

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

    char* ftmp = tmp;
    char* fhashtag = hashtag;
    char* fsection = section;

    Set sGlobal = newSet();                 // 
    for(i = 0; i < len; i++){
        char urlname[sizeof("Sample1/") + SIZEOFURL + sizeof(".txt")] = "Sample1/";
        Set sLocal = newSet();
        strcat(urlname,strcat(dupList[i],".txt"));
        printf("%s\n",urlname);
        FILE *fptext = fopen(urlname, "r");      // Opens up url
        if(fptext != NULL){
            if (!(fscanf(fptext,"%s %s",hashtag, section) == 2)) return 1;                 //error
            if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return 1;     //error
            while(!(fscanf(fptext,"%s",section) == 1 && strcmp(section,"Section-2") == 0));
            while ((fscanf(fptext,"%s",tmp) != EOF) && strcmp(tmp,"#end") != 0 ) {    // Reads by character
                //printf("IVE ENTERED THE NEXT WHILE LOOP \n");
                tmp = RemoveSpecialCharacters(tmp);     // Removes special characters
                NormaliseWord(tmp);                     // Converts words to lowercase
                //printf("toptmp=%s\n",tmp);

                if(!isElem(sGlobal, tmp)){              // For words never seen before, create a head node that holds all urls containing it
                    //printf("PRE");
                    insertInto(sGlobal, tmp);
                    //printf("is an element of sGlobal now 131 inv\n");           
                    AppendIINode(tmp, r);
                }
//                printf("%d\n", isElem(sGlobal,tmp));
//                printf("%d\n", isElem(sLocal,tmp));
                if(!isElem(sLocal, tmp)) {
                    printf("%s   ", urlList[i]   );
                    printf("%s\n", tmp);

                    insertInto(sLocal, tmp);               // For words not seen before, insert url into the word node
                    Queue urlQ = SearchIndex(tmp,r);
                    enterQueue(urlQ, urlList[i]);
                    //showQueue(urlList);
                    //showIIRep(r);
                    //printf("show me\n");
                }
            }
            //check if next word is "Section-2", and finish
            //printf("bottmp=%s\n",tmp);
            if (!(fscanf(fptext,"%s",section) == 1 && strcmp(section,"Section-2") == 0)) {
                printf("YOU SCREWED UP\n");                
                return 1;//error
            }
        }
        fclose(fptext);
        disposeSet(sLocal);
    }
    disposeSet(sGlobal);
    free(fhashtag);
    free(fsection);
    free(ftmp);
    free(hashtag);
    free(section);
    //free(tmp); 
    
    FILE *fp = fopen("invertedIndex.txt", "w");
    IINode *cur;
    for(cur = r->front; cur != NULL; cur = cur->next){
        fprintf(fp, "%s  ", cur->word);
        //printf("for %s:\n", cur->word);
        Queue url_q = cur->urls;
        //showQueue(url_q);
        //fwrite(invertedIdx, 1, sizeof(invertedIdx), fp);
        char* url = malloc(sizeof(urlList[0]));
        char* furl = url;
        for(url = leavePriorQueue(url_q); ; url = leavePriorQueue(url_q)){
            fprintf(fp, "%s ", url);    
            //showQueue(url_q);   
            if (emptyQueue(url_q)) break;         
        }
        free(furl);
        fprintf(fp,"\n");
    }
    fclose(fp);
    freeII(r);

    for(p = 0; p < len; p++) free(dupList[p]);
    return 0;

}
