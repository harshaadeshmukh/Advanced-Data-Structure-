#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

struct GraphStack {
    int arr[MAX_SIZE];
    int top;
};

void initializeGraphStack(struct GraphStack *stack) {
    stack->top = -1;
}

int isEmptyGraphStack(struct GraphStack *stack) {
    return (stack->top == -1);
}

void pushGraphStack(struct GraphStack *stack, int data) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack is full !!!\n");
        return;
    }

    stack->arr[++stack->top] = data;
}

int popGraphStack(struct GraphStack *stack) {
    if (isEmptyGraphStack(stack)) {
        printf("Stack is empty !!!\n");
        return -1;
    }

    return stack->arr[stack->top--];
}

int peekGraphStack(struct GraphStack *stack) {
    if (isEmptyGraphStack(stack)) {
        printf("Stack is empty !!!\n");
        return -1;
    }

    return stack->arr[stack->top];
}

void DFS(int vertexes, int G[vertexes][vertexes]) {
    struct GraphStack stack;
    int visited[vertexes];
    int start, v, i;
	int j;
    initializeGraphStack(&stack);
    for ( j = 0; j < vertexes; j++) {
        visited[j] = 0;
    }

    printf("\nEnter the starting vertex : ");
    scanf("%d", &start);

    pushGraphStack(&stack, start);
    visited[start] = 1;
    v = start;
    printf(" %d ", start);

    while (!isEmptyGraphStack(&stack)) {
        for (i = 0; i < vertexes; i++) {
            if (G[v][i] == 1 && visited[i] == 0) {
                printf(" %d ", i);
                pushGraphStack(&stack, i);
                visited[i] = 1;
                v = i;
                break;
            }
        }

        if (i == vertexes) {
            popGraphStack(&stack);
            if (!isEmptyGraphStack(&stack)) {
                v = peekGraphStack(&stack);
            }
        }
    }
}

int main() {
    int vertexes, edges, v, u;

    printf("Enter the number of vertexes : ");
    scanf("%d", &vertexes);

    int G[vertexes][vertexes];
	int i , j;
    for ( i = 0; i < vertexes; i++) {
        for ( j = 0; j < vertexes; j++) {
            G[i][j] = 0;
        }
    }

    printf("\nEnter the number of edges : ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("\nEnter the edge from/to : ");
        scanf("%d%d", &v, &u);
        G[v][u] = G[u][v] = 1;
    }

    printf("\nThe Graph is : \n");
    for (i = 0; i < vertexes; i++) {
        for (j = 0; j < vertexes; j++) {
            printf(" %d ", G[i][j]);
        }
        printf("\n");
    }

    printf("\nDepth First Traversal of given Graph : ");
    DFS(vertexes, G);

    return 0;
}

