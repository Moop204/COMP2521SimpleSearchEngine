// Completed by Justin Or and Andrew Nguyen
// Implemented with BST where key is a string and value is in a list

#include <stdio.h>
#include <string.h>

void NormaliseWord(char* word);             // Taken from lab08 of COMP2521 
//void RemoveSpecialCharacters(char* word);   // Returns a string without special characters
char *RemoveSpecialCharacters(char *word);


typedef struct IINode {
    IINode  *next;
    char    *word;
    URLNode *next_url;
} IINode;

typedef struct URLNode {
    char    *url;
    URLNode *next_url;
} URLNode;

IINode AppendIINode(char *word, IINode *prev){
    IINode newNode = malloc(sizeof(IINode)); 
    newNode->word = word;
    newNode->next = NULL;
    newNode->next_url = NULL;
    prev->next = newNode;
    return newNode;
}

IINode InitialiseNode(char *word){
    IINode newNode = malloc(sizeof(IINode)); 
    newNode->word = word;
    newNode->next_url = NULL;
    newNode->next = NULL;
    return newNode;
}

int InvertedIndex(char **urlList){
    
    Queue q = newQueue();
    Set   s = newSet();
    int len = LenCollection();
    char *tmp;
    IINode headNode = NULL; 
    IINode currNode;
    
    for(int i = 0; i < len; i++){
        FILE *fptext = fopen(urlList[i], "r");

        while (fscanf(fptext,"%s",tmp) != EOF) {
            tmp = RemoveSpecialCharacters(tmp);
            NormalizeWord(tmp);
            if(!isElem(s, tmp)){
                insertInto(s, tmp);
                enterQueue(q, tmp);
                if(headNode == NULL){
                    currNode = InitialiseNode(tmp);
                    headNode = *currNode;
                    addUrl(currNode, urlList[i]);
                }
                else{
                    currNode = AppendIINode(tmp, currNode);
                    addUrl(currNode, urlList[i]);
                }
                

            }
        }
    }    

    

    FILE *fp = fopen("invertedIndex.txt", "w");
    fwrite(invertedIdx, 1, sizeof(invertedIdx), fp);
    fclose(fp)    
    return 0;

}

void writeInvertedIndex(IINode *head){

    for(IINode *currNode = head; currNode != NULL; currNode = currNode->next){
        fprint(//Output to file
} 

void addUrl(IINode curr, char* url){
    for(URLNode *tmp = curr->next_url; tmp != NULL; tmp = tmp->next_url){
        //COMPARE STRINGS
        if( /*TODO*/){
        }
    } 
}  

char *RemoveSpecialCharacters(char* str){
    char *standardStr;
    int len = strlen(str);
    int idx = 0;
    for(int i = 0; i < len; i++){
        if(str[i] != '.' && str[i] != ';' && str[i] != '?'){
            standardStr[idx] = str[i];
        }
        
    }    
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

void NormalizeWord(char* word)
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

/*

