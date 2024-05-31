#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode *next;
};

int findParentGraph(int i, int parent[]) {
    while (i != parent[i]) {
        i = parent[i];
    }
    return i;
}

void unionNodes(int i, int j, int parent[]) {
    int x = findParentGraph(i, parent);
    int y = findParentGraph(j, parent);
    parent[y] = x;
}

void KruskalsAdjList(int vertexes, struct GraphNode *G[]) {
    int parent[vertexes];
    struct GraphNode *temp;
    int numEdges = 0;
    int weight = 0;
    
    int i;

    for ( i = 0; i < vertexes; i++) {
        parent[i] = i;
    }

    while (numEdges < vertexes - 1) {
        int min = INT_MAX;
        int a = 0, b = 0 , i;
        for ( i = 0; i < vertexes; i++) {
            temp = G[i];
            while (temp != NULL) {
                if (temp->weight < min && findParentGraph(i, parent) != findParentGraph(temp->vertex, parent)) {
                    min = temp->weight;
                    a = i;
                    b = temp->vertex;
                }
                temp = temp->next;
            }
        }
        unionNodes(a, b, parent);
        printf("\nEdge %d : %d->%d = %d", numEdges++, a, b, min);
        weight += min;
    }

    printf("\nMinimum weight of MST : %d", weight);
}

void createAdjListGraphExtended(struct GraphNode *G[], int vertexes) {
    int v, u, weight , i;
    char choice;

    struct GraphNode *p, *newVertex;

    for ( i = 0; i < vertexes; i++) {
        G[i] = NULL;
    }

    do {
        printf("\nEnter the edge from/to : ");
        scanf("%d%d", &v, &u);
        printf("Enter the weight : ");
        scanf("%d", &weight);

        // Create a new node for vertex v
        newVertex = (struct GraphNode *)malloc(sizeof(struct GraphNode));
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

        // Create a new node for vertex u
        newVertex = (struct GraphNode *)malloc(sizeof(struct GraphNode));
        newVertex->vertex = v;
        newVertex->weight = weight;
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

	int i;
    createAdjListGraphExtended(G, vertexes);

    printf("\nThe Graph is : \n");
    for ( i = 0; i < vertexes; i++) {
        p = G[i];
        while (p != NULL) {
            printf("%d ", p->vertex);
            p = p->next;
        }
        printf("\n");
    }

    printf("\nThe Minimum Spanning Tree of given graph using Kruskals : ");
    KruskalsAdjList(vertexes, G);
    return 0;
}

