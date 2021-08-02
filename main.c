#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024

int addGraph(long d);

int main() {
    int i, j;
    int points;
    long d; //number of nodes for each graph
    long k; //first k graphs
    char *p;
    char buffer[BUFFERSIZE];
    fgets(buffer,BUFFERSIZE,stdin);
    d = strtol(buffer, &p, 10);
    k = strtol(p+1, &p, 10);
    char cmd[15];
    fgets(buffer, BUFFERSIZE, stdin);
    strcpy(cmd, buffer);
    if(strncmp(cmd, "AggiungiGrafo", 13)==0) {
        points = addGraph(d);
    }

    return 0;
}

int addGraph(long d) {
    long matrix[d][d];
    int i,j;
    char buffer[BUFFERSIZE];
    char *pnt;
    for(i=0; i<d; i++) {
        fgets(buffer, BUFFERSIZE, stdin);
        pnt = buffer;
        for(j=0; j<d; j++) {
            if(j==0)
                matrix[i][0] = strtol(pnt, &pnt, 10);
            else
                matrix[i][j] = strtol(pnt+1, &pnt, 10);
        }
    }

}
