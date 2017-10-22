// Completed by Andrew Phuoc Nguyen and Justin Chun-Sang Or
// Ranks pages
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readData.h"
#include "inverted.h"
#include "pagerank.h"
#include "set.h"
#include "queue.h"
#include "graph.h"

int PageRankW(double d, double diffPR, int maxIterations);

int main(int argc, char* argv[]){
    if(argc != 4){
        printf("Needs four inputs.");
    }
    else{
        double d = atof(argv[1]);
        double diffPR = atof(argv[2]);
        int maxIterations = atoi(argv[3]); 
        PageRankW(d, diffPR, maxIterations);
    }
}

int PageRankW(double d, double diffPR, int maxIterations) {
    // initialising variables and pointers
    int sizeUrl = LenCollection("collection.txt");
    char** urlList = GetCollection("collection.txt",sizeUrl,SIZEOFURL);
    Graph g = GetGraph(urlList);
    //CALLOC - urlPR to store the pageranks of every iteration.
    double** urlPR;     //[sizeUrl][maxIterations]
    urlPR = calloc(sizeUrl, sizeof(double *));
    int i,j,k;

    for (i = 0; i < sizeUrl; i++)
        urlPR[i] = calloc((maxIterations), sizeof(double));
    
    int noIter = 0;     //number of iterations
    for(i = 0; i < sizeUrl; i++)
        urlPR[i][noIter] = (double)1/(double)sizeUrl;

    // difference in page rank sum
    double diff = diffPR;  

    // inlinks = # of links that link into this page j
    int* inLinks;
    inLinks = calloc(sizeUrl, sizeof(int));

    // outlinks = # of links that this page j links to
    double* outLinks;
    outLinks = calloc(sizeUrl, sizeof(double));

    double** weightIn;// [sizeUrl][sizeUrl]
    weightIn = calloc(sizeUrl, sizeof (double *));
    for (i = 0; i < sizeUrl; i++) {
        weightIn[i] = calloc(sizeUrl, sizeof(double));
    }

    double** weightOut;// [sizeUrl][sizeUrl]
    weightOut = calloc(sizeUrl, sizeof (double *));
    for (i = 0; i < sizeUrl; i++) {
        weightOut[i] = calloc(sizeUrl, sizeof(double));
    }
                          
    // calculate inlinks and outlinks of all links
    int src, dest;
    for (src = 0; src < sizeUrl; src++) {
        for (dest = 0; dest < sizeUrl; dest++) {
            // if (src == dest) continue;
            if (isConnected(g, urlList[src], urlList[dest])==1) {
                outLinks[src]+= 1.0;            
                inLinks[dest]++;
            }
        }
    }
    for (i = 0; i < sizeUrl; i++) 
        if (outLinks[i] == 0) outLinks[i] = 0.5;
 
    // calculate weight in and weight out of all links
    for(i = 0; i < sizeUrl; i++) {          // For url i:
        for (j = 0; j < sizeUrl; j++) {     // For each other url
            // calculate weightIn and weightOut
            if (j == i || 
                isConnected(g,urlList[j],urlList[i]) == 0 || 
                !"is a selfloop/parallel edge") continue;
            // weightIn from j to i = (#inlinks of i)/(sum of inlinks of pages j links to)
            // weightOut from j to i = (#outlinks of i)/(sum of outlinks of pages j links to)
            double sumIn  = 0;
            double sumOut = 0;
            for (k = 0; k < sizeUrl; k++) {
                // calculate the sumIn and sumOut;
                if (isConnected(g,urlList[j],urlList[k]) == 1) {
                    sumIn  += inLinks[k];
                    sumOut += outLinks[k];
                }
            }
            weightIn[j][i]  = (double)(inLinks[i])/(double)(sumIn);     // j->i
            weightOut[j][i] = (double)(outLinks[i])/(double)(sumOut);   // j->i
        }
    }

    // PageRankWeighted algorithm
    while ((noIter < maxIterations-1 && diff >= diffPR) || noIter == 0) {
        noIter++;
        for(i = 0; i < sizeUrl; i++) {          //for url i:
            // calculate the pagerank
            urlPR[i][noIter] = (double)(1-d)/sizeUrl;
            for (j = 0; j < sizeUrl; j++) {     // for each other url
                urlPR[i][noIter] += d * (double)urlPR[j][noIter-1] * (double)weightIn[j][i] * (double)weightOut[j][i];
            }
        }
        //calculate diff
        diff = 0;
        for (i = 0; i < sizeUrl; i++) {
            double difference = urlPR[i][noIter] - urlPR[i][noIter-1];
            if (difference < 0) difference = difference * -1;
            diff += difference;
        }
    }

    int* seen = calloc(sizeUrl, sizeof(int));

    double maxurlPR = 0;
    int max = 0;
    FILE *fp = fopen("pagerankList.txt", "w");
    for (i = 0; i < sizeUrl; i++) {
        for (j = 0; j < sizeUrl; j++) {
            if ((urlPR[j][noIter] - maxurlPR) > 0) {
                if (seen[j] == 0) {
                    maxurlPR = urlPR[j][noIter];
                    max = j;
                }
            }
        }
        seen[max] = 1;
        fprintf(fp, "%s, %.0f, %.7f\n", urlList[max], outLinks[max], urlPR[max][noIter]);
        maxurlPR = 0;
        max = 0;
    }

    fclose(fp);

    // freeing used memory
    free(seen);
    disposeGraph(g);
    for(i = 0; i < sizeUrl; i++) free(urlPR[i]);
    free(urlPR);
    free(inLinks);
    free(outLinks);
    for(i = 0; i < sizeUrl; i++) free(weightIn[i]);
    free(weightIn);
    for(i = 0; i < sizeUrl; i++) free(weightOut[i]);
    free(weightOut);
    for(i = 0; i < sizeUrl; i++) free(urlList[i]);
    free(urlList);

    return 0;
}
