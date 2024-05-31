#include<stdio.h>
#define MAX_SIZE 100

struct GQueue
{
	int arr[MAX_SIZE];
	int front , rear;
};

void initQueue(struct GQueue *que)
{
	que -> front = -1;
	que->rear = -1;
}

int isEmptyQueue(struct GQueue *que)
{
	return (que->front == -1 && que->rear == -1);
}

void enqueue(struct GQueue *que , int data)
{
	if(que->rear == MAX_SIZE-1)
	{
		printf("Queue is full !!\n");
		
	}
	else if(isEmptyQueue(que))
	{
		que->front = 0;
		que->rear = 0;
	}
	else
	{
		que->rear ++; 
	}
	que->arr[que->rear] = data;
}

int dequeue(struct GQueue *que)
{
	if(isEmptyQueue(que))
	{
		printf("Queue is Empty !!");
		return -1;
	}
	else if(que->front == que->rear)
	{
		int data = que->arr[que->front];
		que->front = -1;
		que->rear = -1;
		return data;
	}
	else
	{
		int data = que->arr[que->front];
		que->front ++;
		return data;
	}
}

void BreadthFSearch(int vertex, int g[vertex][vertex])
{
	int visited[vertex];
	int start , i , temp;
	
	struct GQueue que;
	initQueue(&que);
	
	
	printf("\nEnter starting vertex : ");
	scanf("%d",&start);
	enqueue(&que,start);
	
	for(i=0;i<vertex;i++)
	{
		visited[i] = 0;
	}
	visited[start] = 1;
	
	
	while(!isEmptyQueue(&que))
	{
		temp = dequeue(&que);
		printf("%d\t",temp);
		
		for(i =0;i<vertex;i++)
		{
			if(g[temp][i]==1 && visited[i]==0)
			{
				enqueue(&que,i);
				visited[i] = 1;
			}
		}
	}
	
}
int main()
{
	int edges , vertex ;
	int from,to;
	
	printf("Enter the number of vertex : ");
	scanf("%d",&vertex);
	
	int g[vertex][vertex];
	//setting all matrices to 0
	int i,j;
	for(i=0;i<vertex;i++)
	{
		for(j=0;j<vertex;j++)
		{
			g[i][j] = 0;	
		}
	}
	
	printf("\nEnter the number of edges : ");
	scanf("%d",&edges);

	for(i=0;i<edges;i++)
	{
		printf("\nEnter the edges From/To : ");
		scanf("%d %d",&from,&to);
		
		g[from][to] = 1;
		g[to][from] = 1;
	//	printf("\n");
	}
	  printf("\nGraph  : \n");
	for(i=0;i<vertex;i++)
	{
	    for(j=0;j<vertex;j++)
	    {
	        printf("%d ", g[i][j]);
	    }
	    printf("\n");
	}

	BreadthFSearch(vertex,g);
	
	return 0;
}
