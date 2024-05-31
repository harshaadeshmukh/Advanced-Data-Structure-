#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct GraphNode {
    int vertex;
    struct GraphNode *next;
};

void DepthFirstSearch(struct GraphNode *G[], int vertexes, int start, int visited[]) {
    struct GraphNode *p = G[start];
    visited[start] = 1;
    printf(" %d ", start);

    while (p != NULL) {
        int nextVertex = p->vertex;
        if (visited[nextVertex] == 0) {
            DepthFirstSearch(G, vertexes, nextVertex, visited);
        }
        p = p->next;
    }
}

void createAdjListGraph(struct GraphNode *G[], int vertexes) {
    int v, u;
    char choice;
    struct GraphNode *p, *newVertex;
	int i;
    for ( i = 0; i < vertexes; i++) {
        G[i] = NULL;
    }
    do {
        printf("\nEnter the edge from/to : ");
        scanf("%d%d", &v, &u);
        // Create a new node for vertex v
        newVertex = (struct GraphNode *)malloc(sizeof(struct GraphNode));
        newVertex->vertex = u;
        newVertex->next = NULL;
        // Add newVertex to the adjacency list of vertex v
        if (G[v] == NULL) {
            G[v] = newVertex;
        } else {
            p = G[v];
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = newVertex;
        }

        // Create a new node for vertex u
        newVertex = (struct GraphNode *)malloc(sizeof(struct GraphNode));
        newVertex->vertex = v;
        newVertex->next = NULL;

        // Add newVertex to the adjacency list of vertex u
        if (G[u] == NULL) {
            G[u] = newVertex;
        } else {
            p = G[u];
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = newVertex;
        }

        printf("\nDo you want to add more edges? [Y/N] : ");
        scanf(" %c", &choice);
        getchar();

    } while (choice == 'Y' || choice == 'y');
}

int main() {
    int vertexes;

    printf("Enter the number of vertexes : ");
    scanf("%d", &vertexes);

    struct GraphNode *p;
    struct GraphNode *G[vertexes];

    createAdjListGraph(G, vertexes);
int i;
    printf("\nThe Graph is : \n");
    for ( i = 0; i < vertexes; i++) {
        p = G[i];
        while (p != NULL) {
            printf("%d ", p->vertex);
            p = p->next;
        }
        printf("\n");
    }
    printf("\nThe DFS traversal of given graph is : ");
    int visited[vertexes];
    for ( i = 0; i < vertexes; i++) {
        visited[i] = 0;
    }
    printf("\nEnter the starting vertex : ");
    int start;
    scanf("%d", &start);
    DepthFirstSearch(G, vertexes, start, visited);
    // Free allocated memory
    for ( i = 0; i < vertexes; i++) {
        struct GraphNode *current = G[i];
        while (current != NULL) {
            struct GraphNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    return 0;
}
