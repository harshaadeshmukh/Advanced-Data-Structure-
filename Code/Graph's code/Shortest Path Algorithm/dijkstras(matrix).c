#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

int findMinimumDistanceVertex(int dist[], int visited[], int vertexes) {
    int mini = INT_MAX, index = -1;
	int i;
    for( i = 0; i < vertexes; i++) {
        if(visited[i] == 0 && dist[i] < mini) {
            mini = dist[i];
            index = i;
        }
    }
    return index;
}

void display(int vertexes, int dist[], int visited[], int start) {
    printf("\nSource - Vertex -> Distance\n");
    int minWeight = 0 , i;
    for( i = 0; i < vertexes; i++) {
        printf("%d - %d -> %d\n", start, i, dist[i]);
        minWeight += dist[i];
    }
}

void Dijkstras(int vertexes, int G[vertexes][vertexes]) {
    int visited[vertexes], dist[vertexes];
    int v , i , j;
    int start;

    for( i = 0; i < vertexes; i++) {
        visited[i] = 0;
        dist[i] = INT_MAX;
    }

    printf("\nEnter the source vertex : ");
    scanf("%d", &start);

    dist[start] = 0;

    for( i = 0; i < vertexes - 1; i++) {
        v = findMinimumDistanceVertex(dist, visited, vertexes);
        visited[v] = 1;
        for( j = 0; j < vertexes; j++) {
            if(visited[j] == 0 && G[v][j] != 0 && dist[j] > dist[v] + G[v][j]) {
                dist[j] = dist[v] + G[v][j];
            }
        }
    }

    display(vertexes, dist, visited, start);
}

int main() {
    int vertexes, edges, v, u, weight;

    printf("Enter the number of vertexes : ");
    scanf("%d",&vertexes);

    int G[vertexes][vertexes];
    int i, j;

    for( i = 0; i < vertexes; i++) {
        for( j = 0; j < vertexes; j++) {
            G[i][j] = 0;
        }
    }

    printf("\nEnter the number of edges : ");
    scanf("%d",&edges);

    for( i = 0; i < edges; i++) {
        printf("\nEnter the edge from/to : ");
        scanf("%d%d",&v, &u);
        printf("Enter the weight of edge : ");
        scanf("%d",&weight);
        G[v][u] = weight;
    }

    printf("\nThe Graph is : \n");
    for( i = 0; i < vertexes; i++) {
        for( j = 0; j < vertexes; j++) {
            printf(" %d ", G[i][j]);
        }
        printf("\n");
    }

    Dijkstras(vertexes, G);
}
