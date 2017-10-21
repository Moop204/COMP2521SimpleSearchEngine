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
#define SIZEOFDIR 10
#define SIZEOFEXT 4
#define TERMINATING 1
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
    

/*
    //open inverted index, find N
    char file_name[SIZEOFDIR+SIZEOFURL+SIZEOFEXT+TERMINATING] = "Sample1/";
    strcat(strcat(file_name,url),".txt");
    //printf("filename %s\n",file_name);
    printf("FILE %s\n", file_name);
    FILE *open = fopen(file_name, "r");
    char* tmp;
    tmp = (char *) malloc((SIZEOFURL)*sizeof(char));
    char* hashtag;
    hashtag = (char *) malloc((SIZEOFURL)*sizeof(char));
    char* section;
    section = (char *) malloc((MAXWORD)*sizeof(char));

    //char* ftmp = tmp;
    //char* fhashtag = hashtag;
    char* fsection = section;  

    if(open != NULL){
        //scan through to Section-2
        if (!(fscanf(open,"%s %s", hashtag, section) == 2)) return -1;                 //error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return -2;     //error
        //printf("%s %s:\n",hashtag,section);
        while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0);
        //tmp == #end, make sure Section-1 is next and then close
        if (!(fscanf(open,"%s", section) == 1 && strcmp(section,"Section-1") == 0)) return -3;//error
        //check if at Section-2
        if (!(fscanf(open,"%s %s", hashtag, section) == 2)) return -4;                 //error
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
    //free(ftmp);
    //free(fhashtag);
    free(fsection);
*/
    f = wordFrequency(word, url);
    N = wordTotal(url);
    //calculating f
    printf("f = %d\nN = %d\n", f, N);

    return (double)(f)/(double)(N);
}

//IDF = Inverse document frequency
//                   total docs
//    = log  (---------------------------)
//         10  # of docs containing word

double idf(char* word) {
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
    char* ftmp = tmp;
    //printf("%s", ftmp);
    if(open != NULL){
        while(fscanf(open, "%s", tmp) != EOF && strcmp(tmp, word) != 0);
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
    free(ftmp);

    fclose(open);
    //calculating
    printf("N = %d\n f = %d\n", N, f);
    return log10((double)(N)/(double)(f));
}

double tfIdf(char*word, char*url) {
    //printf("tf %.7lf \nidf %.7lf\n",tf(word,url), idf(word));
    return tf(word,url); //* idf(word);
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



int main(int argc, char **argv){

    if(!(argc > 1)){
        perror("Please select one or more words to search");
        return 1;
    }

    int length = LenCollection();
    char **collection = GetCollection(length, SIZEOFURL);   // INITIAL ORDER reference
    int *listFreq = calloc(length, sizeof(int));            // INITIAL ORDER of frequency
    double *listTfIdf = calloc(length, sizeof(int));
    int idx;

    
    int debug;    

    for(idx = 1; idx < argc; idx++){
        char *arg = argv[idx];
        int nUrls;
        for(nUrls = 0; nUrls < length; nUrls++){
            listFreq[nUrls] += wordFrequency(arg, collection[nUrls]); 
            printf("%s  %d\n", collection[nUrls], listFreq[nUrls]);
        }
    }

    for(idx = 0; idx < argc; idx++){
        char *arg = argv[idx];
        int nUrls;
        for(nUrls = 0; nUrls < length; nUrls++){
            listTfIdf[nUrls] += tfIdf(arg, collection[nUrls]); 
            printf("%s  %.7lf\n", collection[nUrls], listTfIdf[nUrls]);
        }
    }


    for(debug = 0; debug < length; debug++){
        printf("%d ", listFreq[debug]);
    }
        printf("\n");
    

    int *listPrint = calloc(MAXOUTPUT, sizeof(int));        // order of printing, refers to INITIAL ORDER in order
    int i;
    for(i = 0; i < MAXOUTPUT; i++){
        listPrint[i] = -1;
    }



    for(i = 0; i < length; i++){    // Iterates INITIAL ORDER
        int val = listFreq[i];
        printf("%d has %d freq\n", i, val);




        int e;
        if(val != 0){
            for(e = 0; e < MAXOUTPUT; e++){ // Iterates printing order until it finds a new place or finds a lower val
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
                    else if(val == listFreq[printRef]){
                        if(listTfIdf[i] > listTfIdf[printRef]){
                            shiftRight(listPrint, e, MAXOUTPUT);
                            listPrint[e] = i; 
                            break;
                        }
                    }
                }
            }
        }
        else continue;
    }

    for(i = 0; i < MAXOUTPUT; i++){
        if(listPrint[i] == -1)
            break;
        else
            printf("%s %d %.7lf\n", collection[listPrint[i]], listFreq[i+1], listTfIdf[i+1]);
    }
 
    for(idx = 0; idx < length; idx++)free(collection[idx]);
    free(collection);
    free(listFreq);
    free(listTfIdf);
    free(listPrint);
    return 0;
}

void shiftRight(int *list, int pos, int max){
    int cur;
    for(cur = max-1; cur > pos; cur --){
        list[cur] = list[cur-1];
    }
}
