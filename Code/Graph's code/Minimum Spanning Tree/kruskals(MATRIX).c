#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void Kruskals(int vertexes, int G[vertexes][vertexes]) {
    int parent[vertexes];
    int numEdges = 0 , i;
    int weight = 0 , j;

    for ( i = 0; i < vertexes; i++) {
        parent[i] = i;
    }

    while (numEdges < vertexes - 1) {
        int min = INT_MAX;
        int a = 0, b = 0;
        for ( i = 0; i < vertexes; i++) {
            for ( j = 0; j < vertexes; j++) {
                if (G[i][j] < min && findParentGraph(i, parent) != findParentGraph(j, parent)) {
                    min = G[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        unionNodes(a, b, parent);
        printf("\nEdge %d : %d->%d = %d", numEdges++, a, b, min);
        weight += min;
    }
    printf("\nMinimum weight of MST : %d", weight);
}

int main() {
    int vertexes, edges, v, u, weight;

    printf("Enter the number of vertexes : ");
    scanf("%d", &vertexes);

    int G[vertexes][vertexes];
    int i , j;

    for ( i = 0; i < vertexes; i++) {
        for ( j = 0; j < vertexes; j++) {
            G[i][j] = INT_MAX;
        }
    }

    printf("\nEnter the number of edges : ");
    scanf("%d", &edges);

    for ( i = 0; i < edges; i++) {
        printf("\nEnter the edge from/to : ");
        scanf("%d%d", &v, &u);
        printf("Enter the weight : ");
        scanf("%d", &weight);
        G[v][u] = G[u][v] = weight;
    }

    printf("\nThe Graph is : \n");
    for ( i = 0; i < vertexes; i++) {
        for ( j = 0; j < vertexes; j++) {
            if (G[i][j] == INT_MAX) {
                printf(" -1 ");
            } else {
                printf(" %d ", G[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n\nKruskal`s Algorithm : ");
    Kruskals(vertexes, G);
    return 0;
}

