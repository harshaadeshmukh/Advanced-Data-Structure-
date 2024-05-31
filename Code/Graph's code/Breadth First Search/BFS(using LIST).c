#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 200
struct node
{
	int vertex;
	struct node *next;
};

struct GraphQueue
{
	int arr[MAX_SIZE];
	int front , rear;
};

void initGraphQueue(struct GraphQueue *q)
{
	q->front = -1;
	q->rear = -1;
}
int isEmptyGraphQueue(struct GraphQueue *q)
{
	return (q->front == -1 && q->rear == -1);
}

void enQueue(struct GraphQueue *q , int vertex)
{
	if(q->rear == MAX_SIZE-1)
	{
		printf("Queue is full !!\n");
	}
	if(q->front == -1)
	{
		q->front = 0;
	}
	q->rear ++;
	
	q->arr[q->rear] = vertex;
}

int deQueue(struct GraphQueue *q)
{
	if(isEmptyGraphQueue(q))
	{
		printf("Queue is Empty!!\n");
		return -1;
	}
	int temp = q->arr[q->front];
	if(q->front == q->rear)
	{
		q->front = -1;
		q->rear = -1;
	}
	else
	{
		q->front++;
	}
	return temp;
}

void createAdjListGraph(struct node *g[],int vertex)
{
	char choice;
	int from , to;
	struct node *p , *newVertex;
	int i;
	for(i=0 ; i<vertex ; i++)
	{
		g[i] = NULL;
	}	
	do
	{
		printf("\nEnter the edge from / to : ");
		scanf("%d %d",&from,&to);
		
		// Create a new node for vertex from
		newVertex = (struct node*)malloc(sizeof(struct node));
		newVertex->vertex = to ; 
		newVertex->next = NULL;
		
		
		// Add newVertex to the adjacency list of vertex from
		if(g[from] == NULL)
		{
			g[from] = newVertex;
		}
		else
		{
			p = g[from];
			while(p->next != NULL)
			{
				p = p->next;
			}
			p->next = newVertex;
		}
		
		// Create a new node for vertex to
		newVertex = (struct node*)malloc(sizeof(struct node));
		newVertex->vertex = from ; 
		newVertex->next = NULL;
		
		// Add newVertex to the adjacency list of vertex to
		if(g[to] == NULL)
		{
			g[to] = newVertex;
		}
		else
		{
			p = g[to];
			while(p->next != NULL)
			{
				p = p->next;
			}
			p->next = newVertex;
		}
		
		printf("Do you want to add more edges [Y/N] : ");
		scanf(" %c",&choice);
		
	} while(choice == 'Y' || choice == 'y');
	
}

void BreadthFirstSearch(struct node *g[], int vertex)
{
	int visited[vertex];
	int start , temp ;
	struct GraphQueue q;
	struct node *p;
	
	initGraphQueue(&q);
	int i;
	for(i=0;i<vertex ; i++)
	{
		visited[i] = 0;
	}
	printf("\n\nEnter the starting vertex : ");
	scanf("%d",&start);
	
	enQueue(&q , start);
	visited[start] = 1;
	
	while(!isEmptyGraphQueue(&q))
	{
		temp = deQueue(&q);	
		printf("%d  ",temp);
		p = g[temp];
		
		while(p!=NULL)
		{
			if(visited[p->vertex] == 0)
			{
				enQueue(&q  ,p->vertex);
				visited[p->vertex] = 1;
			}
			p = p->next;
		}
	}
	printf("\n");
}

int main()
{
	int vertex;
	printf("Enter the number of vertex : ");
	scanf("%d",&vertex);
	
	struct node *p , *g[vertex];
	
	createAdjListGraph(g,vertex);
	
	printf("\nThe Graph is : \n");
	int i;
	for(i=0;i<vertex;i++)
	{	
		p= g[i];
		while(p!=NULL)
		{
			printf("%d  ",p->vertex);
			p=p->next;
		}
		printf("\n");
	}
	
	printf("The BFS traversal of given graph ....");
	BreadthFirstSearch(g,vertex);
	
	return 0;
}
