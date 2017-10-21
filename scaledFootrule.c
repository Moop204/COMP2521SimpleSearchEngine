// Completed by Andrew Phuoc Nguyen and Justin Chun-Sang Or
// scales ranks from different sources
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"
#include "set.h"
#include "queue.h"
#include "graph.h"

//#define URL(i,j,k) (urlLists[dim2*dim3*i + dim3*j + k])
//const int dim1, dim2, dim3;  /* Global variables, dimension*/
//double * array = (double *)malloc(dim1*dim2*dim3*sizeof(double));
//^found from https://stackoverflow.com/questions/2438142/dynamic-memory-allocation-for-3d-array

int main(int argc, char* argv[]) {
    if (argc == 1) return -1;
    //for each file, translate file to a real list
    int i,j,k,l;
    int maxLength = 0;
    //MALLOC - array of length for each file
    int* length = malloc((argc-1) * sizeof(int));
    for (i = 0; i < argc-1; i++) {
        length[i] = LenCollection(argv[i+1]);
        if (length[i] > maxLength) maxLength = length[i];
    }
    printf("malloc for arrays is ok\n");
    //MALLOC - array of arrays of char lists: urlList[argc][maxLength][SIZEOFURL]
    char*** list =(char***) malloc((argc-1)*maxLength*SIZEOFURL);
    for (i = 0; i < argc-1; i++) {
        list[i] = (char**) GetCollection(maxLength,SIZEOFURL);
    }
    printf("malloc for lists is ok\n");

    //NEW SET
    Set seen = newSet();//to count the |union|
    Set new = newSet();//to create localRanks

    //getting union of all lists = N
    printf("argc = %d\n", argc);
    for (i = 0; i < argc-1; i++) {
        printf("array %d: %s\n",i, argv[i+1]);
        for (j = 0; j < maxLength; j++) {
            if (j < length[i]) {
                printf("%d. %s\n",j,list[i][j]);
                insertInto(seen,list[i][j]);
            }
        }
    }
    
    //performing scaledFootrule
    //W(C,P) a ranking that places element C in pos P
    //for the kth list:
    //  W(C,P) = fabs(localrank - Prank)

    int u = nElems(seen);

    //MALLOC - url list union of everything
    char** urlList = (char**) malloc (u*SIZEOFURL);
    for (i = 0; i < u; i++) {
        urlList[i] = (char *) malloc (SIZEOFURL * sizeof(char));
    }
    //MALLOC - Prank list [n]-m (n is rank in the union, m is rank chosen(pos P)
    int* Prank = malloc(u * sizeof(int));
    for (i = 0; i < u; i++) Prank[i] = i+1;
    //CALLOC - c array for use in Heap's Algorithm for permutations.
    int* c = calloc(u, sizeof(int));
    //CALLOC - localRank list [i][j] (in ith list, the jth term in urlunion list
    //         has the value of its local rank.
    int** localRank = malloc((argc-1)*u);
    for (i = 0; i < argc-1; i++) {
        localRank[i] = calloc(u,sizeof(int));
    }


    k = 0;//the index of urlList
    for (i = 0; i < argc-1; i++) {
        for (j = 0; j < maxLength; j++) {
            if (j < length[i]) {
                if(!isElem(new,list[i][j])) {
                    printf("urlList[%d]. %s\n",k,list[i][j]);
                    insertInto(new,list[i][j]);
                    urlList[k] = list[i][j];
                    localRank[i][k] = j+1;
                    k++;
                } else {
                    for (l = 0; l < u; l++) {
                        if (strcmp(urlList[l],list[i][j])==0) localRank[i][l] = j+1;
                    } 
                }
            }
        }
    }

    for (i = 0; i < argc-1; i++) {
        for (j = 0; j < u; j++) {
            printf("[%d][%d]%d ",i,j,localRank[i][j]);
        }
        printf("\n");
    }


    //starting "brute force" method with smart algorithm techniques (early exit)
    //using Prank list
    //Test Prank
    i = 0;
    while (i < u) {
        if (c[i] < i) {
            if (i%2 ==0) {
                //swap(Pr[0], Pr[i])
            } else {
                //swap(Pr[c[i]],Pr[i])
            }
            //Test Prank
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    //finished with all arrangments
    //free
    free(Prank);
    free(c);
    for (i = 0; i < argc-1; i++) free(localRank[i]);
    free(localRank);
    disposeSet(seen);
    disposeSet(new);
    for (i = 0; i < u; i++) {
        free(urlList[i]);
    }
    free(urlList);
    free(length);
    for (i = 0; i < argc-1; i++) {
        for (j = 0; j < maxLength; j++) {
            free(list[i][j]);
        }
        free(list[i]);
    }
    free(list);
    return 0;
}

void swap(int* array, int a, int b) {
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
    return;
}
