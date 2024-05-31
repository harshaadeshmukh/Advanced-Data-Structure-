#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define the AVL tree node structure
struct AVLTreeNode {
    struct AVLTreeNode *left;
    int data;
    struct AVLTreeNode *right;
    int height;
};

// Define the stack node structure for AVL tree
struct AVLStackNode {
    struct AVLTreeNode *data;
    struct AVLStackNode *next;
};

// Define the stack structure for AVL tree
struct AVLStack {
    struct AVLStackNode *top;
    int size;
};

// Function to create an AVL stack
void createAVLStack(struct AVLStack *stack) {
    stack->size = 0;
    stack->top = NULL;
}

// Function to check if the AVL stack is empty
int isEmptyAVLStack(struct AVLStack *stack) {
    return stack->top == NULL;
}

// Function to push a node onto the AVL stack
void pushAVLStack(struct AVLStack *stack, struct AVLTreeNode *node) {
    struct AVLStackNode *newNode = (struct AVLStackNode*) malloc(sizeof(struct AVLStackNode));
    newNode->data = node;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

// Function to pop a node from the AVL stack
struct AVLTreeNode* popAVLStack(struct AVLStack *stack) {
    if (isEmptyAVLStack(stack)) {
        printf("Stack is Empty");
        exit(EXIT_FAILURE);
    }
    struct AVLStackNode *stackNode = stack->top;
    struct AVLTreeNode *treeNode = stackNode->data;
    stack->top = stackNode->next;
    stack->size--;
    free(stackNode);
    return treeNode;
}

// Function to peek the top element of the AVL stack
struct AVLTreeNode* peekAVL(struct AVLStack *stack) {
    if (isEmptyAVLStack(stack)) {
        printf("Stack is Empty");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// Function to calculate height of a node
int height(struct AVLTreeNode *root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

// Function to calculate the balance factor of a node
int getBalanceFactor(struct AVLTreeNode *root) {
    if (root == NULL) {
        return 0;
    } else {
        return (height(root->left) - height(root->right));
    }
}

// Function to perform right rotation
struct AVLTreeNode* rotateRight(struct AVLTreeNode *Y) {
    struct AVLTreeNode *X = Y->left;
    struct AVLTreeNode *T2 = X->right;
    X->right = Y;
    Y->left = T2;
    X->height = 1 + fmax(height(X->left), height(X->right));
    Y->height = 1 + fmax(height(Y->left), height(Y->right));
    return X;
}

// Function to perform left rotation
struct AVLTreeNode* rotateLeft(struct AVLTreeNode *Y) {
    struct AVLTreeNode *X = Y->right;
    struct AVLTreeNode *T2 = X->left;
    X->left = Y;
    Y->right = T2;
    X->height = 1 + fmax(height(X->left), height(X->right));
    Y->height = 1 + fmax(height(Y->left), height(Y->right));
    return X;
}

// Function to insert a node into AVL tree
struct AVLTreeNode* insertAVL(struct AVLTreeNode *root, int key) {
    if (root == NULL) {
        root = (struct AVLTreeNode*) malloc(sizeof(struct AVLTreeNode));
        root->data = key;
        root->height = 1;
        root->left = root->right = NULL;
        return root;
    } else if (root->data > key) {
        root->left = insertAVL(root->left, key);
    } else if (root->data < key) {
        root->right = insertAVL(root->right, key);
    } else {
        printf("Key already present in the tree");
        return root;
    }

    root->height = 1 + fmax(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);

    // Left-Left Rotation case
    if (balanceFactor > 1 && root->left->data > key) {
        return rotateRight(root);
    }
    // Right-Right Rotation case
    if (balanceFactor < -1 && root->right->data < key) {
        return rotateLeft(root);
    }
    // Left-Right Rotation case
    if (balanceFactor > 1 && root->left->data < key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right-Left Rotation case
    if (balanceFactor < -1 && root->right->data > key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Function to perform in-order traversal of AVL tree
void inOrderAVL(struct AVLTreeNode *root) {
    struct AVLStack stack;
    createAVLStack(&stack);

    while (1) {
        // Go to left-most child-node of the current root-node
        while (root != NULL) {
            pushAVLStack(&stack, root);
            root = root->left;
        }
        // If empty stack, exit
        if (isEmptyAVLStack(&stack)) {
            break;
        }
        // Print the current node
        root = popAVLStack(&stack);
        printf(" %d ", root->data);
        // Left tree and its root are processed, go to right tree
        root = root->right;
    }
}

// Function to perform pre-order traversal of AVL tree
void preOrderAVL(struct AVLTreeNode *root) {
    struct AVLStack stack;
    createAVLStack(&stack);

    while (1) {
        while (root != NULL) {
            printf(" %d ", root->data);
            pushAVLStack(&stack, root);
            root = root->left;
        }

        if (isEmptyAVLStack(&stack)) {
            break;
        }

        root = popAVLStack(&stack);
        root = root->right;
    }
}

// Function to perform post-order traversal of AVL tree
void postOrderAVL(struct AVLTreeNode *root) {
    struct AVLStack stack;
    createAVLStack(&stack);
    struct AVLTreeNode *prev = NULL;

    while (1) {
        while (root != NULL) {
            pushAVLStack(&stack, root);
            root = root->left;
        }

        if (isEmptyAVLStack(&stack)) {
            break;
        }

        root = peekAVL(&stack);

        if (root->right == NULL || root->right == prev) {
            printf(" %d ", root->data);
            popAVLStack(&stack);
            prev = root;
            root = NULL;
        } else {
            root = root->right;
        }
    }
}

int main() {
    struct AVLTreeNode *root = NULL;
    int total;
    printf("\nEnter the number of elements to insert into AVL tree : ");
    scanf("%d", &total);
	int i;
    for ( i = 0; i < total; i++) {
        int key;
        printf("\nEnter the %d element key : ", i + 1);
        scanf("%d", &key);
        root = insertAVL(root, key);
    }

    printf("\nPreOrder :");
    preOrderAVL(root);
    printf("\nInOrder :");
    inOrderAVL(root);
    printf("\nPostOrder :");
    postOrderAVL(root);
}

