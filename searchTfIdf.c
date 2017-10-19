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
#include "tfIdf.h"
#include "set.h"
#include "queue.h"
#include "graph.h"

#define MAXCHAR 1000


//TF = term frequency
//     f of the term
//   = ------------- in a doc/url
//      total words

double tf(char* word, char* url) {
    int N = 0; //# of total words
    int f = 0; //f of the term

    //open inverted index
    char line[MAXCHAR];
    char* file_name = "invertedIndex.txt";
    FILE *open = fopen(file_name, "r");
    tmp = (char*) malloc((SIZEOFURL)*sizeof(char));
    hashtag = (char*) malloc((SIZEOFURL)*sizeof(char));
    section = (char*) malloc((10)*sizeof(char));
    if(open != NULL){
        if (!(fscanf(open,"%s %s",hashtag, section) == 2)) return NULL;//error
        if (strcmp(hashtag,"#start")+strcmp(section,"Section-1") != 0) return NULL;//error
        //printf("%s %s:\n",hashtag,section);
        while((fscanf(open,"%s", tmp) != EOF) && strcmp(tmp,"#end") != 0) {
            //printf("WHILE: tmp = %s\n", tmp);
            for (k = 0; k < graphSize; k++){
                //printf("FOR k = %d\n", k);
                if (strcmp(urlList[k], tmp) == 0) {
                    //printf("Adding an edge between %s and %s\n", urlList[i], urlList[k]);
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
    
    //calculating

    return (double)(f)/(double)(N);
}

//IDF = Inverse document frequency
//                   total words
//    = log  (---------------------------)
//         10  # of docs containing word

double idf(char* word, char* url) {
    int N = 0; //# of total words
    int f = 0; //# of docs containing word
    
    //calculating

    return log10((double)(N)/(double)(f));
}
