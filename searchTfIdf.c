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

void shiftRight(int *list, int pos, int max);

//TF = term frequency
//     f of the term
//   = ------------- in a doc/url
//      total words

double tf(char* word, char* url) {
    int N = 0; //# of total words
    int f = 0; //f of the term

    // obtain values
    f = wordFrequency(word, url);
    N = wordTotal(url);
    return (double)(f)/(double)(N);
}

//IDF = Inverse document frequency
//                   total docs
//    = log  (---------------------------)
//         10  # of docs containing word

double idf(char* word) {
    int N = 0; //# of docs
    int f = 0; //# of docs containing word

    N = LenCollection("collection.txt");
    char* file_name = "invertedIndex.txt";
    FILE *open = fopen(file_name, "r");
    char* tmp = calloc(MAXWORD, sizeof(char));
    char* ftmp = tmp;
    if(open != NULL){
        while(fscanf(open, "%s", tmp) != EOF && strcmp(tmp, word) != 0);
        while(fscanf(open, "%s", tmp) != EOF 
              && (tmp[0] == 'u' 
              &&  tmp[1] == 'r' 
              &&  tmp[2] == 'l')){
            f++;
        }
    }     
    free(ftmp);
    fclose(open);
    //calculating
    return log10((double)(N)/(double)(f));
}

double tfIdf(char*word, char*url) {
    return tf(word,url) * idf(word);
}


int main(int argc, char **argv){

    if(!(argc > 1)){
        perror("Please select one or more words to search");
        return 1;
    }


    int length = LenCollection("collection.txt");
    char **collection = GetCollection("collection.txt",length, SIZEOFURL);   // INITIAL ORDER reference
    int *listFreq = calloc(length, sizeof(int));            // INITIAL ORDER of frequency
    double *listTfIdf = malloc(length * sizeof(double));
    InvertedIndex(collection);

    int idx;
    int nUrls;

    for(nUrls = 0; nUrls < length; nUrls++){
        listTfIdf[nUrls] = 0.0;         
    }
    
    for(idx = 1; idx < argc; idx++){
        char *arg = argv[idx];
        int nUrls;
        for(nUrls = 0; nUrls < length; nUrls++){
            listFreq[nUrls] += wordFrequency(arg, collection[nUrls]); 
        }
    }

    for(idx = 1; idx < argc; idx++){
        char *arg = argv[idx];
        for(nUrls = 0; nUrls < length; nUrls++){
            double value = tfIdf(arg, collection[nUrls]);
            listTfIdf[nUrls] += value;             
        }
    }

    int *listPrint = calloc(MAXOUTPUT, sizeof(int));        // order of printing, refers to INITIAL ORDER in order
    int i;
    for(i = 0; i < MAXOUTPUT; i++){
        listPrint[i] = -1;
    }

    for(i = 0; i < length; i++){    // Iterates INITIAL ORDER
        int val = listFreq[i];
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
            printf("%s  %.6lf\n", collection[listPrint[i]], listTfIdf[listPrint[i]]);
    }

    for(idx = 0; idx < length; idx++)free(collection[idx]);
    free(collection);
    free(listFreq);
    free(listTfIdf);
    free(listPrint);
    return 0;
}

