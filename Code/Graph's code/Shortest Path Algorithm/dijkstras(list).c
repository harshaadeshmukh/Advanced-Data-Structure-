#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode *next;
};

void createAdjListDirectedGraph(struct GraphNode *G[], int vertexes) {
    int v, u, weight , i;
    char choice;

    struct GraphNode *p, *newVertex;

    for ( i = 0; i < vertexes; i++) {
        G[i] = NULL;
    }

    do {
        printf("Enter the edge from/to : ");
        scanf("%d%d", &v, &u);
        printf("Enter the weight : ");
        scanf("%d", &weight);
        
        newVertex = (struct GraphNode*) malloc(sizeof(struct GraphNode));
        newVertex->vertex = u;
        newVertex->weight = weight;
        newVertex->next = NULL;

        if (G[v] == NULL) {
            G[v] = newVertex;
        } else {
            p = G[v];

            while (p->next != NULL) {
                p = p->next;
            }

            p->next = newVertex;
        }

        printf("\nDo you want to add more edges? [Y/N] : ");
        scanf(" %c", &choice);
        getchar();

    } while (choice == 'y' || choice == 'Y');
}

int findMinimumDistanceVertex(int dist[], int visited[], int vertexes) {
    int mini = INT_MAX, index = -1 , i;
    for ( i = 0; i < vertexes; i++) {
        if (visited[i] == 0 && dist[i] < mini) {
            mini = dist[i];
            index = i;
        }
    }
    return index;
}

void display(int vertexes, int dist[], int visited[], int start) {
    printf("\nSource : Vertex -> Distance\n");
    int minWeight = 0 , i;
    for ( i = 0; i < vertexes; i++) {
        printf("%d : %d -> %d\n", start, i, dist[i]);
        minWeight += dist[i];
    }
}

void DijkstrasAdjList(int vertexes, struct GraphNode *G[]) {
    int visited[vertexes], dist[vertexes];
    int v, start , i;
    struct GraphNode *p;

    for ( i = 0; i < vertexes; i++) {
        visited[i] = 0;
        dist[i] = INT_MAX;
    }

    printf("Enter the source vertex : ");
    scanf("%d", &start);
    dist[start] = 0;

    for ( i = 0; i < vertexes - 1; i++) {
        v = findMinimumDistanceVertex(dist, visited, vertexes);
        p = G[v];
        visited[v] = 1;
        while (p != NULL) {
            if (visited[p->vertex] == 0 && dist[p->vertex] > dist[v] + p->weight) {
                dist[p->vertex] = dist[v] + p->weight;
            }
            p = p->next;
        }
    }
    display(vertexes, dist, visited, start);
}

int main() {
    int vertexes , i;

    printf("Enter the number of vertexes : ");
    scanf("%d", &vertexes);

    struct GraphNode *p;
    struct GraphNode *G[vertexes];

    createAdjListDirectedGraph(G, vertexes);

    printf("\nThe Graph is : \n");
    for ( i = 0; i < vertexes; i++) {
        p = G[i];
        while (p != NULL) {
            printf("%d ", p->vertex);
            p = p->next;
        }
        printf("\n");
    }

    DijkstrasAdjList(vertexes, G);

    return 0;
}

