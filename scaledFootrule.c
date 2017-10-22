//By Andrew Phuoc Nguyen and Justin Chun-Sang Or
// scales ranks from different sources
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"
#include "scaledFootrule.h"
#include "set.h"
#include "queue.h"
#include "graph.h"


//#define URL(i,j,k) (urlLists[dim2*dim3*i + dim3*j + k])
//const int dim1, dim2, dim3;  // Global variables, dimension
//double * array = (double *)malloc(dim1*dim2*dim3*sizeof(double));
//^found from https://stackoverflow.com/questions/2438142/dynamic-memory-allocation-for-3d-array

#define MAXVALUE 2000000000
//for WCP smart algo
#define W(x,y) WCP[(u-1)*x + y]
/*
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
        list[i] = (char**) GetCollection(argv[i+1],maxLength,SIZEOFURL);
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
    //CALLOC - localRank list [i][j] (in ith list, the jth term in this list
    //         has the value of its urlList union ranking (index+1).
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
                    insertInto(seen,list[i][j]);
                    insertInto(new,list[i][j]);
                    urlList[k] = list[i][j];
                    localRank[i][j] = k+1;
                    k++;
                } else {
                    for (l = 0; l < u; l++) {
                        if (strcmp(urlList[l],list[i][j])==0) localRank[i][j] = l+1;
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
    double W = 0;
    double Wmin = MAXVALUE;
    //CALLOC - saves the best ranking yet
    int* save = calloc(u, sizeof(int));
    //using Prank list
    //Heap's Algorithm (https://en.wikipedia.org/wiki/Heap%27s_algorithm)
    //Test Prank
    W = 0;
    for (j = 0; j < argc-1; j++) {//for each list
        for (k = 0; k < maxLength; k++) {//for every url
            if (k >= length[j]) continue;//ignore (outside of jth list)
            //find urlList index for this url
            W = W + fabs((double)(k+1)/(double)length[j] - (double)Prank[localRank[j][k]]/(double)u);
            if (W > Wmin) {//EARLY EXIT
                //break;
                k = maxLength;
                j = argc-1;
            }
        }
    }
    if (W < Wmin) {
        //save this list
        Wmin = W;
        //for (i = 0; i < u; i++) save[i] = Prank[i];
    }
    //printf("Wmin = %lf\nW = %lf\n", Wmin,W);
    //end test
    int tmp = 0;
    i = 0;
    while (i < u) {
        if (c[i] < i) {
            if (i%2 ==0) {
                //swap(Prank, Prank[0], Prank[i]);
                tmp = Prank[0];
                Prank[0] = Prank[i];
                Prank[i] = tmp;
            } else {
                //swap(Prank, Prank[c[i]],Prank[i]);
                tmp = Prank[c[i]];
                Prank[c[i]] = Prank[i];
                Prank[i] = tmp;
            }
            //Test Prank
            W = 0;
            for (j = 0; j < argc-1; j++) {//for each list
                for (k = 0; k < maxLength; k++) {//for every url
                    if (k >= length[j]) continue;//ignore (outside of jth list)
                    //find urlList index for this url
                    W = W + fabs((double)(k+1)/(double)length[j] - (double)Prank[localRank[j][k]-1]/(double)u);
                    if (W > Wmin) {//EARLY EXIT
                        //break;
                        k = maxLength;
                        j = argc-1;
                    }
                }
            }
            if (W < Wmin) {
                Wmin = W;
                //save this list
                for (l = 0; l < u; l++) {
                    save[l] = Prank[l];
                }
            }
            //printf("Wmin = %lf\n                W = %lf\n", Wmin,W);
            //end test
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    //finished with all arrangments
    printf("Best Arrangement: %d",save[0]);
    for (i = 1; i < u; i++) {
        printf(",%d",save[i]);
    }
    printf("\n");


    //Smart Algorithm
    //Based of Kruskal's Algorithm for graphs, the same idea made for PQueue
    //1. start with empty list
    //2. consider all single permutations of order in increasing W order
    //3. add the smallest ones, can only add one of each so ignore if the thing 
    //   has been added
    //4. stop when u elements have been added. 

    //1. 
    //CALLOC - the W table that stores the W for putting elem C at rank P
    double* WCP = (double*) calloc(u*u, sizeof(double));
    //use save that was used earlier;
    for (i = 0; i < u; i++) save[i] = 0;
    Queue q = newQueue();
    //2.a record all permutations for W in a u*u matrix.
    for (j = 0; j < argc-1; j++) {//for each list
        for (k = 0; k < maxLength; k++) {//for every url
            if (k >= length[j]) continue;//ignore (outside of jth list)
            //find urlList index for this url
            for (l = 0; l < u; l++) {//for each Possible final rank
                W((localRank[j][k]-1),l) += fabs(((double)(k+1)/(double)length[j])-((double)(l+1)/(double)u));
                //printf("@%dth urlList index, at place %d, WCP = %d/%d - %d/%d = %lf\n", 
                //        localRank[j][k]-1,l+1,
                //        (k+1),length[j],(l+1),u,
                //        fabs(((double)(k+1)/(double)length[j])-((double)(l+1)/(double)u)));
            }
        }
    }
    //show table
    printf("WCP:\n");
    for (i = 0; i < u; i++) {//for every url in urllist 
        for (j = 0; j < u; j++) {//for every place P
            printf("[%d][%d].%lf ",i,j+1,W(i,j));
        }
        printf("\n");
    }
    //2.b order all permutations for W in increasing order.
    //CALLOC - records the permutations for W in order
    int* orderW = calloc(u*u, sizeof(int));

    for(i = 0; i < u*u; i++) orderW[i] = -1;
    int sizeOrderW = u*u;

    for(i = 0; i < u*u; i++){    // Iterates INITIAL ORDER
        double val = WCP[i];
        printf("%d has %lf weight\n", i, val);
        int e;
        for(e = 0; e < sizeOrderW; e++){ // Iterates saving order until it finds a new place or finds a lower val
            int urlRef = orderW[e];
            if(urlRef == -1){
                orderW[e] = i;
                break;
            }
            else{
                if(val <= WCP[urlRef]){
                    shiftRight(orderW, e, sizeOrderW);
                    orderW[e] = i;
                    break;
                }
            }
        }
    }

    // Insert to final list
    
    int* visited = calloc(u, sizeof(int));
    int idx = 0;

    for(i = 0; i < u*u; i++){
        int setPos = orderW[i];
        if(visited[setPos%u] == 0){
            visited[setPos%u] = 1;
            Prank[idx] = orderW[i]/u + 1;
            idx++;
        } 
        if(idx == u) break;
    }

    // DEBUG
    for(idx = 0; idx < u; idx++) printf("%d ", Prank[idx]);
    printf("\n");

    //free
    free(orderW);
    free(WCP);
    disposeQueue(q);
    free(save);
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

int* swap(int* array, int a, int b) {
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
    return array;
}
*/
