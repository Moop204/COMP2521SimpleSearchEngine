// Completed by Andrew Nguyen and Justin Or
// Given search terms (words) as command line arguments,
// outputs (stdout) top 30 pages in descending order of number of search terms found
// and then within each group,
// descending order of summation of tf-idf values of all search terms found. 

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"
#include "searchTfIdf.h"
#include "set.h"
#include "queue.h"
#include "graph.h"

#define MAXCHAR   1000
#define MAXOUTPUT 30
//(MAXWORD = 45)
//(SIZEOFURL = 7)

void shiftRight(int *list, int pos, int max);

//TF = term frequency
//     f of the term
//   = ------------- in a doc/url
//      total words

double tf(char* word, char* url) {
    int N = 0; //# of total words
    int f = 0; //f of the term
    
    //open inverted index, find N
    char file_name[8+SIZEOFURL+4] = "Sample1/";
    strcat(strcat(file_name,url),".txt");
    //printf("filename %s\n",file_name);

    FILE *open = fopen(file_name, "r");
    char* tmp;
    tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* hashtag;
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* section;
    section = (char*) malloc((MAXWORD)*sizeof(char));

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
            N++;
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
    free(tmp);
    free(hashtag);
    free(section);
    //calculating f
    printf("f = %d\nN = %d\n", f, N);

    return (double)(f)/(double)(N);
}

//IDF = Inverse document frequency
//                   total docs
//    = log  (---------------------------)
//         10  # of docs containing word

double idf(char* word, char* url) {
    int N = 0; //# of docs
    int f = 0; //# of docs containing word

    N = LenCollection();
    //open inverted index, find N
    //char line[MAXCHAR];
    char* file_name = "invertedIndex.txt";
    FILE *open = fopen(file_name, "r");
    //char* tokenWord = (char*) malloc((MAXWORD)*sizeof(char));
    //char* tokenUrl = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* tmp = calloc(MAXWORD, sizeof(char));

    if(open != NULL){
        while(fscanf(open, "%s", tmp) != EOF && strcmp(tmp, word) == 0);
        // 
        while(fscanf(open, "%s", tmp) != EOF 
              && (tmp[0] == 'u' 
              &&  tmp[1] == 'r' 
              &&  tmp[2] == 'l')){
            f++;
        }
   }     

/*        while (fgets(line,sizeof(line),open)) {
            //read the word
            tokenWord = strtok(line," ");
//            printf("tokenWord = %s\n", tokenWord);
            NormaliseWord(tokenWord); 
            if (strcmp(word,tokenWord) != 0) continue;
            //read the urls
            while (1) {
                tokenUrl = strtok(NULL, " ");
                if ((tokenUrl == NULL)) break;// || (strcmp(tokenUrl,"url") < 0)) break;
                f++;
 //               printf("tokenUrl = %s\n", tokenUrl);
            }
            f++;
        }

    }
    if (tokenWord) printf(" ");;
*/
    fclose(open);
    //calculating
    printf("N = %d\n f = %d\n", N, f);
    return log10((double)(N)/(double)(f));
}

double tfIdf(char*word, char*url) {
    return tf(word,url) * idf(word,url);
}


/* UNUSED CODE THAT MAY BE USEFUL
char line[MAXCHAR];
    char* file_name = "invertedIndex.txt";
    FILE *open = fopen(file_name, "r");
    char* tokenWord = (char*) malloc((MAXWORD)*sizeof(char));
    //char* tokenUrl = (char*) malloc((SIZEOFURL)*sizeof(char));
    if(open != NULL){
        while (fgets(line,sizeof(line),open)) {
            //read the word
            tokenWord = strtok(line," ");
            //printf("tokenWord = %s\n", tokenWord);
            f++;
            if (strcmp(word,tokenWord) != 0) continue;
            //read the urls
            while (1) {
                tokenUrl = strtok(NULL, " ");
                if ((tokenUrl == NULL)) break;// || (strcmp(tokenUrl,"url") < 0)) break;
                f++;
                printf("tokenUrl = %s\n", tokenUrl);
            }
        }
    }
    if (tokenWord);
    fclose(open);
*/


int word_frequency(char* word, char* url) {
    int f = 0; //f of the term
    
    //open inverted index, find N
    char file_name[8+SIZEOFURL+4] = "Sample1/";
    strcat(strcat(file_name,url),".txt");
    //printf("filename %s\n",file_name);

    FILE *open = fopen(file_name, "r");
    char* tmp;
    tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* hashtag;
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    char* section;
    section = (char*) malloc((MAXWORD)*sizeof(char));

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
    free(tmp);
    free(hashtag);
    free(section);

    return (f);
}

void searchTfIdf(char **argv, int argc){

    int length = LenCollection();
    char **collection = GetCollection(length, SIZEOFURL); 
    int *listFreq = calloc(length, sizeof(int));
//    int *listTfIdf = calloc(length, sizeof(int));

    int idx;
    for(idx = 0; idx < argc; idx++){
        char *arg = argv[idx];
        int nUrls;
        for(nUrls = 0; nUrls < length; nUrls++){
            listFreq[nUrls] += word_frequency(arg, collection[nUrls]); 
        }
    }
    

    int *listPrint = calloc(MAXOUTPUT, sizeof(int));
    int i;
    for(i = 0; i < length; i++){
        listPrint[i] = -1;
    }

    for(i = 0; i < length; i++){
        int val = listFreq[i];

        int e;
        if(val != 0){
            for(e = 0; e < MAXOUTPUT; e++){
                int printRef = listPrint[e];
                if(printRef == -1){
                    listPrint[e] = i;
                    break;
                }
                else{
                    if(val > listFreq[printRef]){
                        shiftRight(listPrint, e, MAXOUTPUT);
                        listPrint[e] = i;
                        break;
                    }
                }
            }
        }
        else continue;
    }

url32 0
url34 2
url22 2
url21 1
url23 2
url11 1
url31 1


    for(i = 0; i < MAXOUTPUT; i++){
        if(listPrint[i] == -1)
            break;
        else
            printf("%s %d\n", collection[listPrint[ ]], listFreq[i]);
    }

}

void shiftRight(int *list, int pos, int max){
    int cur;
    for(cur = max-1; cur > pos; cur --){
        list[cur] = list[cur-1];
    }
}
