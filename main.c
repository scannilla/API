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
    graph *temp, *new;
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
            if(graphIndex>=k && tail!=NULL && tail->totalScore>points) {
                tail->prev->next = NULL;
                temp=tail;
                tail=temp->prev;
                free(temp);
            }
            if(head==NULL || (head -> totalScore)>points) {
                //TODO inserimento in testa
                temp=head;
                head = (graph*)malloc(sizeof (graph));
                head->totalScore = points;
                head->index = graphIndex;
                head->next = temp;
                head->prev = NULL;
                if (tail==NULL)
                    tail = head;

            }
            else if((tail->totalScore)<=points) {
                if(tail!=head) {
                    temp = tail;
                    tail = (graph*)malloc(sizeof(graph));
                    tail->totalScore = points;
                    tail->index = graphIndex;
                    tail->next = NULL;
                    tail->prev = temp;
                    temp->next = tail;
                }
                else {
                    tail = (graph*)malloc(sizeof(graph));
                    tail->totalScore = points;
                    tail->index = graphIndex;
                    tail->next = NULL;
                    tail->prev = head;
                    head->next = tail;
                }

            }
            else {
                temp = head;
                while(temp->totalScore <= points)
                    temp = temp->next;
                new = (graph*) malloc(sizeof(graph));
                new->totalScore = points;
                new->index = graphIndex;
                new->prev=temp->prev;
                temp->prev=new;
                new->next=temp;
            }
            graphIndex++;
        }
        else if(strncmp(cmd, "TopK", 4)==0) {
            for(temp=head;temp!=NULL;temp=temp->next) {
                if(temp->next!=NULL)
                    printf("%d ",temp->index);
                else
                    printf("%d", temp->index);
            }
        }
        //printf("%d", points);
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

