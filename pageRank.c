// Completed by Andrew Phuoc Nguyen and Justin Chun-Sang Or
// Ranks pages
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pageRank.h"
#include "set.h"
#include "queue.h"
#include "graph.h"

int PageRankW(double d, double diffPR, int maxIterations) {
    //initialising
    int sizeUrl = LenCollection();//sizeof(listOfUrls[0]);
    char** urlList = GetCollection(sizeUrl,SIZEOFURL);
    Graph g = GetGraph(urlList);
    double** urlPR;//[sizeUrl][maxIterations]
    urlPR = calloc(sizeUrl, sizeof(double *));
    int i,j,k,l;
    for (i = 0; i < sizeUrl; i++) {
        urlPR[i] = calloc((maxIterations), sizeof(double));
    }

    int noIter = 0;     //number of iterations
    for(i = 0; i < sizeUrl; i++){
        urlPR[i][noIter] = (double)1/(double)sizeUrl;
    }

    double diff = diffPR;  //difference in page rank sum
    
    int* inLinks;//inlinks = # of links that link into this page j
    inLinks = calloc(sizeUrl, sizeof(int));
    
    double* outLinks;//outlinks = # of links that this page j links to
    outLinks = calloc(sizeUrl, sizeof(double));
    
    double** weightIn;//[sizeUrl][sizeUrl]
    weightIn = calloc(sizeUrl, sizeof (double *));
    for (i = 0; i < sizeUrl; i++) {
        weightIn[i] = calloc(sizeUrl, sizeof(double));
    }

    double** weightOut;//[sizeUrl][sizeUrl]
    weightOut = calloc(sizeUrl, sizeof (double *));
    for (i = 0; i < sizeUrl; i++) {
        weightOut[i] = calloc(sizeUrl, sizeof(double));
    }

    double sumIn, sumOut;
                          
    //calculate inlinks and outlinks of all links
    int src, dest;
    for (src = 0; src < sizeUrl; src++) {
        for (dest = 0; dest < sizeUrl; dest++) {
            //if (src == dest) continue;
            if (isConnected(g, urlList[src], urlList[dest])==1) {
                outLinks[src]+= 1.0;            
                inLinks[dest]++;
            }
        }
    }
    for (i = 0; i < sizeUrl; i++) {
        if (outLinks[i] == 0) outLinks[i] = 0.5;
        printf("for %d aka %s: ", i, urlList[i]);
        printf("in: %d out: %1f\n", inLinks[i], outLinks[i]);
    }

    //calculate weight in and weight out of all links

    for(i = 0; i < sizeUrl; i++) {//for url i:
        for (j = 0; j < sizeUrl; j++) {//for each other url
            //calculate weightIn and weightOut
            if (j == i || 
                isConnected(g,urlList[j],urlList[i]) == 0 || 
                !"is a selfloop/parallel edge") continue;//HELP how do i find if its a selfloop/parallel edge?
            printf("%s and %s isConnected?:%d\n", urlList[j], urlList[i], isConnected(g,urlList[j],urlList[i]));
            //weightIn from j to i = (#inlinks of i)/(sum of inlinks of pages j links to);
            //weightOut from j to i = (#outlinks of i)/(sum of outlinks of pages j links to);
            double sumIn = sumOut = 0;
            for (k = 0; k < sizeUrl; k++) {
                //calculate the sumIn and sumOut;
                if (isConnected(g,urlList[j],urlList[k]) == 1) {
                    sumIn += inLinks[k];
                    sumOut += outLinks[k];
                }
            }
            weightIn[j][i] = (double)(inLinks[i])/(double)(sumIn);    //j->i
            weightOut[j][i] = (double)(outLinks[i])/(double)(sumOut); //j->i
            printf("i = %d j = %d\nsumIn: %lf\nsumOut: %lf\nweight in: %lf\nweight out: %lf\n\n",i,j,sumIn,sumOut,weightIn[j][i],weightOut[j][i]);
        }
    }
    printf("Weight In (j,i)\n");
    for (j = 0; j < sizeUrl; j++) {
        for(i = 0; i < sizeUrl; i++) {
            if (weightIn[j][i] == 0) {
                printf("                ");
                continue;
            }  
            printf("[%d][%d]%.7f ", j,i,weightIn[j][i]);
        }
        printf("\n");
    }

    printf("Weight Out (j,i)\n");
    for (j = 0; j < sizeUrl; j++) {
        for(i = 0; i < sizeUrl; i++) {
            if (weightOut[j][i] == 0) {
                printf("                ");
                continue;
            }   
            printf("[%d][%d]%.7f ", j,i,weightOut[j][i]);
        }
        printf("\n");
    }
    //PageRankWeighted algorithm
    while ((noIter < maxIterations-1 && diff >= diffPR) || noIter == 0) {
        noIter++;
        printf("ITERATION: %d\n", noIter);
        for(i = 0; i < sizeUrl; i++) {//for url i:
            //calculate the pagerank
            urlPR[i][noIter] = (double)(1-d)/sizeUrl;
            ////printf("i = %d      PR of %s is %lf\n",i,urlList[i],urlPR[i][noIter]);
            for (j = 0; j < sizeUrl; j++) {//for each other url
                urlPR[i][noIter] += d * (double)urlPR[j][noIter-1] * (double)weightIn[j][i] * (double)weightOut[j][i];
            }
        }
        diff = 0;
        for (i = 0; i < sizeUrl; i++) {
            //printf("before: %lf, after %lf\n", urlPR[i][noIter], urlPR[i][noIter-1]);
            //printf("Difference: %lf\n", urlPR[i][noIter] - urlPR[i][noIter-1]);
            double difference = urlPR[i][noIter] - urlPR[i][noIter-1];
            if (difference < 0) difference = difference * -1;
            //printf("final difference: %lf\n", difference);
            diff += difference;
        }
        //printf("diff = %lf\n", diff);
    }
    int seen[7] = {0,0,0,0,0,0,0};
    double maxurlPR = 0;
    int max = 0;
    for (i = 0; i < sizeUrl; i++) {
        for (j = 0; j < sizeUrl; j++) {
            if ((urlPR[j][noIter] - maxurlPR) > 0) {
                if (seen[j] == 0) {
                    maxurlPR = urlPR[j][noIter];
                    max = j;
                    //printf("    maxurlPR = %lf max = %d\n   urlPR[%d][%d] = %lf, yes thats right j = %d\n",maxurlPR,max,j,noIter,urlPR[j][noIter],j);
                }
            }
        }
        //printf("    max = %d, maxPR = %lf\n", max, maxurlPR);
        seen[max] = 1;
        printf("%s, %.0f, %.7f", urlList[max], outLinks[max], urlPR[max][noIter]);
        //for (k = 0; k < noIter; k++) printf("[%d]%lf", k,urlPR[max][k]);
        printf("\n");
        maxurlPR = 0;
        max = 0;
    }
    // Calculate Page Rank
    // Type? listUrlPageRank = calculatePageRank(g, d, diffPR, maxIterations);
    //char *orderedListUrlsPageRank = order(listUrlPageRank);
    //int size = strlen(orderedListUrlsPageRank);
    //FILE *fp;
    //fp = fopen("pagerankList.txt","w");
    //fwrite(orderedListUrlsPageRank,1,  sizeof(orderedListUrlsPageRank), fp); 
    return 0;
}
