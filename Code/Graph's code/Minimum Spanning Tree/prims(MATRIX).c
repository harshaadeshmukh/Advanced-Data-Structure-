#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void display(int vertex ,int parent[] ,int G[vertex][vertex])
{
    printf("Edges \tWeight\n");
    for(int i=1;i<vertex;i++)
    {
        printf("%d - %d \t%d\n", parent[i] , i , G[i][parent[i]]);
    }
}

int findMinimumDistance(int distance[] ,int visited[] ,int vertex)
{
    int index , mini = INT_MAX;
    for(int i =0;i<vertex;i++)
    {
        if(visited[i] == 0 && mini>distance[i])
        {
            mini = distance[i];
            index = i;
        }
    }
    return index;
}


void prims(int vertex , int G[vertex][vertex])
{
    int visited[vertex] , parent[vertex] , distance[vertex];
    int v;

     for(int i = 0; i<vertex; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }
    distance[0] = 0;

    for(int i = 0; i<vertex - 1; i++)
    {
        v = findMinimumDistance(distance , visited , vertex);
        visited[v] = 1;
        for(int j = 0; j<vertex ;j++)
        {
            if(visited[j] == 0 && G[v][j]<distance[j])
            {
                distance[j] = G[v][j];
                parent[j] = v;
            }
        }
    }
    display(vertex , parent , G);

}

int main()
{
    int vertex , edges , v , u , weight;
    printf("Enter the number of vertex : ");
    scanf("%d",&vertex);

    int G[vertex][vertex];

    for(int i = 0; i<vertex; i++)
    {
        for(int j = 0; j<vertex; j++)
        {
            G[i][j] = INT_MAX;
        }
    }

    printf("Enter the number of edges : ");
    scanf("%d",&edges);

    printf("\n");
    for(int i=0; i<edges; i++)
    {
        printf("Enter the edges from/to : ");
        scanf("%d%d",&v,&u);
        printf("Enter the weight : ");
        scanf("%d",&weight);
        G[v][u] = G[u][v] = weight;
    }

    printf("\nThe Graph is : \n");
    for(int i = 0; i<vertex; i++)
    {
        for(int j = 0; j<vertex; j++)
        {
            if(G[i][j] == INT_MAX)
            {
                printf(" -1 ");
            }
            else
            {
                printf(" %d ",G[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nMinimum spanning Tree (using Adjacency Matrix) : \n");
    prims(vertex , G);

    return 0;
}
