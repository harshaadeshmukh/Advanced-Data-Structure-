#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct GraphNode{
    int vertex;
    int weight;
    struct GraphNode *next;
};

void displayMSTAdjList(int vertexes, int parent[], struct GraphNode *G[]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertexes; i++) {
        struct GraphNode *temp = G[parent[i]];
        int weight = -1;
        while (temp != NULL) {
            if (temp->vertex == i) {
                weight = temp->weight;
                break;
            }
            temp = temp->next;
        }
        printf("%d - %d \t%d\n", parent[i], i, weight);
    }
}

int findMinimumDistanceAdjList(int distance[], int visited[], int vertexes){
    int mini = INT_MAX, index;

    for(int i = 0; i<vertexes; i++){
        if(visited[i] == 0 && mini > distance[i]){
           mini = distance[i];
           index = i;
        }
    }

    return index;
}

void PrimsAdjList(struct GraphNode *G[], int vertexes){
    int visited[vertexes], parent[vertexes], dist[vertexes];
    int v;
    struct GraphNode *temp;

    for(int i = 0; i<vertexes; i++){
        visited[i] = 0;
        parent[i] = -1;
        dist[i] = INT_MAX;
    }

    dist[0] = 0;

    for(int i = 0; i<vertexes-1; i++){
        v = findMinimumDistanceAdjList(dist, visited, vertexes);
        visited[v] = 1;
        temp = G[v];
        while(temp !=  NULL){
            if(visited[temp->vertex] == 0 && temp->weight < dist[temp->vertex]){
                dist[temp->vertex] = temp->weight;
                parent[temp->vertex] = v;
            }
            temp = temp->next;
        }
    }

    displayMSTAdjList(vertexes, parent, G);
}


void createAdjListGraphExtended(struct GraphNode *G[], int vertexes){
    int v, u, weight;
    char choice;

    struct GraphNode *p, *newVertex;

    for(int i = 0; i<vertexes; i++){
        G[i] = NULL;
    }

    do{
        printf("\nEnter the edge from/to : ");
        scanf("%d%d",&v,&u);
        printf("Enter the weight : ");
        scanf("%d",&weight);

        // Create a new node for vertex v
        newVertex = (struct GraphNode*) malloc(sizeof(struct GraphNode));
        newVertex->vertex = u;
        newVertex->weight = weight;
        newVertex->next = NULL;

        if(G[v] == NULL){
            G[v] = newVertex;
        }else{
            p = G[v];
            while(p->next != NULL){
                p = p->next;
            }
            p->next = newVertex;
        }

        // Create a new node for vertex u
        newVertex = (struct GraphNode*) malloc(sizeof(struct GraphNode));
        newVertex->vertex = v;
        newVertex->weight = weight;
        newVertex->next = NULL;

        // Add newVertex to the adjacency list of vertex u
        if(G[u] == NULL){
            G[u] = newVertex;
        }else{
            p = G[u];
            while(p->next != NULL){
                p = p->next;
            }
            p->next = newVertex;
        }

        printf("\nDo you want to add more edges? [Y/N] : ");
        scanf(" %c", &choice);
        getchar();

    }while(choice == 'Y' || choice == 'y');
}

int main(){
    int vertexes;

    printf("Enter the number of vertexes : ");
    scanf("%d",&vertexes);

    struct GraphNode *p;
    struct GraphNode *G[vertexes];

    createAdjListGraphExtended(G, vertexes);

    printf("\nThe Graph is : \n");
    for(int i = 0; i<vertexes; i++){
        p = G[i];
        while(p != NULL){

            printf("%d ",p->vertex);
            p = p->next;
        }
        printf("\n");
    }

    printf("\nThe Minimum Spanning Tree of given graph using Prims : \n");
    PrimsAdjList(G, vertexes);
    return 0;
}
