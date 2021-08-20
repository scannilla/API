#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024
#define INFINITY 99999999

long d = 0; //number of nodes for each graph
long k; //first k graphs
typedef struct node {
    int index;
    long totalScore;
    struct node *next;
    struct node *prev;
} graph;
graph *head, *tail;

int addGraph();

int dijkstra(long matrix[d][d]);

int main() {
    int i, j;
    int points = 0;
    char *p;
    char buffer[BUFFERSIZE];
    int graphIndex = 0;
    fgets(buffer,BUFFERSIZE,stdin);
    d = strtol(buffer, &p, 10);
    k = strtol(p+1, &p, 10);
    char cmd[15];
    while(1) {
        if(fgets(buffer, BUFFERSIZE, stdin)==NULL)
            return 0;
        strcpy(cmd, buffer);
        if(strncmp(cmd, "AggiungiGrafo", 13)==0) {
            points = addGraph();
            if(head==NULL || (head -> totalScore)>points)
                //TODO inserimento in testa
                ;
            else if((tail->totalScore)<points)
                //TODO inserimento in coda
                ;
            else
                //TODO inserimento in mezzo, valutare puntatori
                ;
        }
        printf("%d", points);
    }
}

int addGraph() {
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
    return dijkstra(matrix);

}

int dijkstra(long matrix[d][d]) {
    int cost[d][d]; //cost of each arch
    int pred[d]; //the precedent node for each node
    int distance[d]; //distance for each node
    int i, j;
    int checked[d]; //boolean array to check if a node has already been marked
    int counter = 0;
    int minimumDistance; //stores the minimum distance from the current node
    int bestNode; //stores the nearest node from the current one
    int score = 0;

    for(i = 0; i < d; i++) {
        for (j = 0; j < d; j++) {
            if(matrix[i][j]==0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = matrix[i][j];
        }
    }
    distance[0] = 0;
    checked[0] = 1;
    pred[0] = 0;
    for(i=1; i<d; i++) {
        distance[i] = cost[0][i];
        checked[i] = 0;
        pred[i] = 0;
    }
    while(counter<d-1) {
        minimumDistance = INFINITY;
        for(i=0; i<d; i++) {
            if(distance[i] < minimumDistance && !checked[i]) {
                minimumDistance = distance[i];
                bestNode = i;
            }
        }
        checked[bestNode] = 1;
        for (i = 0; i < d; i++) {
            if(!checked[i]) {
                if(minimumDistance + cost[bestNode][i] < distance[i]) {
                    distance[i] = minimumDistance + cost[bestNode][i];
                    pred[i] = bestNode;
                }
            }
        }
        counter++;
    }
    for(i=0; i<d; i++) {
        score += distance[i];
    }
    return score;
}

