#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *left;
	struct node *right;	
};
struct stack
{
	struct node *T;
	struct stack *next;
};

struct QueueTree 
{ 
    struct node * T; 
    struct QueueTree * next; 
}; 
struct Queue
{
    struct QueueTree * front, * rear; 
};

//Function Prototype
int isEmpty(struct stack *);
void push(struct stack **,struct node *);
struct node *pop(struct stack **);

int isEmptyQueue(struct Queue* );
void enqueue(struct Queue* , struct node *); 
struct node *dequeue(struct Queue*); 



void create(struct node**,int);
void inorder(struct node*);
void inorder2(struct node *);

void preorder(struct node*);
void preorder2(struct node*);

void postorder(struct node*);
void postorder2(struct node*);

void mirrorTree(struct node**);
int findHeight(struct node*);

struct node* deletion(struct node*,int);
void displayLeaf(struct node *);
void Level_order(struct node *);
struct node *insert(struct node*,int);


int main()
{
	struct node *root;
	root =NULL;
	int option,num,height , key1,key;
	int n1;
//	(Numbers entered are …. 23 , 20 , 34 , 11 , 21 , 30 , 67 , 5 , 14 ,  50)
	printf("********BINARY SEARCH TREE*********\n");
	while(1)
	{
		printf("\n\n1.Create\n2.Inorder\n3.Preorder\n4.Postorder\n5.Mirror tree\n6.Height of the tree\n7.Delete of the node\n8.Level order of tree\n");
		printf("9.Display leaf of nodes\n10.Insert of the node\nChoose the operation : ");
		scanf("%d",&option);
		
		switch(option)
		{
			case 1:
				printf("Enter the number : ");
				scanf("%d",&num);
				create(&root,num);
				break;
			
			case 2:
				printf("Select the option to see inorder traversal either 1.recursion or 2.iteration function : ");
				scanf("%d",&n1);
				switch(n1)
				{
					case 1:
						printf("Displaying in recursive inorder traversal..\n");
						inorder(root);
						break;
						
					case 2:
						printf("Displaying in iterative inorder traversal..\n");
						inorder2(root);
						break;
			
					default:
						printf("Invalid Inorder Option..\n");				
				}
				break;
		
			case 3:
				printf("Select the option to see preorder traversal either 1.recursion or 2.iteration function : ");
				scanf("%d",&n1);
				switch(n1)
				{
					case 1:
						printf("Displaying in recursive preorder traversal..\n");
						preorder(root);
						break;
						
					case 2:
						printf("Displaying in iterative preorder traversal..\n");
						preorder2(root);
						break;
			
					default:
						printf("Invalid Preorder Option..\n");				
				}
				break;
			
			case 4:
				printf("Select the option to see postorder traversal either 1.recursion or 2.iteration function : ");
				scanf("%d",&n1);
				switch(n1)
				{
					case 1:
						printf("Displaying in recursive preorder traversal..\n");
						postorder(root);
						break;
						
					case 2:
						printf("Displaying in iterative preorder traversal..\n");
						postorder2(root);
						break;
			
					default:
						printf("Invalid Preorder Option..\n");				
				}
				break;
			
			case 5:
				mirrorTree(&root);
				break;
				
			case 6:
				height = findHeight(root);
				printf("\nThe height of the tree is %d",height);
				break;

			case 7:
				printf("Enter an element to delete in tree : "); 
      			scanf("%d",&key1); 
      			root = deletion(root ,key1); 
      			break;
      			
      		case 8:
      			printf("\nThe level nodes of the tree traversal from right to left \n"); 
      			Level_order(root);
      			break;
      			
      		case 9:
      			printf("\nThe leaf nodes of the tree from left to right..\n"); 
      			displayLeaf(root);
      			break;
      			
      		case 10:
			   printf("\nEnter an element to insert in tree : ");
			   scanf("%d",&key); 
      		    root = insert(root ,key);
      		    break;
			   	
					
			default :
				printf("Invalid Option..\n");
		}
	}
	return 0;
}

int isEmpty(struct stack *top) 
{
    return top == NULL; // Returns 1 if stack is empty (top is NULL), otherwise returns 0
}

void push(struct stack **top,struct node *temp)		//push operation
{
	struct stack *s = (struct stack*)malloc(sizeof(struct stack));
	s->next = *top;
	s->T = temp;
	*top = s;
}

struct node *pop(struct stack **top)	//pop operation
{
	struct stack *temp = *top;
	struct node * n = temp->T;
	*top = (*top)->next;
	
	return (n);
}

struct Queue* createQueue() 
{ 
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL; 
    return q; 
}

int isEmptyQueue(struct Queue* q) 
{ 
    if(q->front == NULL) 
        return 1; 
    else 
        return 0; 
} 

void enqueue(struct Queue* q, struct node* root) 
{ 
    struct QueueTree * newNode = (struct QueueTree*)malloc(sizeof(struct QueueTree)); 
    newNode->T = root; 
    newNode->next = NULL; 
 
    if(isEmptyQueue(q)) 
    { 
        q->front = q->rear = newNode;
    } 
    else 
    { 
        q->rear->next = newNode; 
        q->rear = q->rear->next; 
    } 
} 
 
struct node * dequeue(struct Queue* q) 
{ 
    if (isEmptyQueue(q)) 
    { 
        printf("Queue is empty.\n"); 
        return NULL; 
    } 
    struct QueueTree* temp = q->front; 
    struct node* root = temp->T; 
    q->front = q->front->next; 
    free(temp); 
    return root; 
}

void inorder2(struct node *root)	//iterative function of inorder traversal
{
	struct stack *top = NULL;
	struct node *temp;
	temp = root;
	while(temp!=NULL)
	{
		push(&top,temp);	
		temp = temp->left;
	}
	while(!isEmpty(top))
	{
		temp = pop(&top);
		printf("%d  ",temp->data);
		temp = temp->right;
		while(temp!=NULL)
		{
			push(&top,temp);	
			temp = temp->left;
		}
	}
}

void preorder2(struct node *root)		//non-recursive function of preorder function
{
	struct stack *top = NULL;
	struct node *temp;
	temp = root;
	while(temp!=NULL)
	{
		printf("%d  ",temp->data);
		push(&top,temp);
		temp = temp->left;
	}
	while(!isEmpty(top))
	{
		temp = pop(&top);
		temp = temp->right;
		while(temp!=NULL)
		{
			printf("%d  ",temp->data);
			push(&top,temp);
			temp = temp->left;	
		}	
	}
}

void postorder2(struct node *root)		//non-recursive function of postorder function
{
    if (root == NULL)
        return;

    struct stack *top = NULL;
    struct node *temp = root;
    struct node *prev = NULL;

    while (temp != NULL)
    {
        push(&top, temp);
        temp = temp->left;
    }

    while (!isEmpty(top))
    {
        temp = pop(&top);

        if (temp->right == NULL || temp->right == prev)
        {
            printf("%d  ", temp->data); // Print data of current node
            prev = temp; // Update prev to current node
        }
        else
        {
            push(&top, temp); // Push current node again
            temp = temp->right; // Move to the right child
            while (temp != NULL)
            {
                push(&top, temp);
                temp = temp->left;
            }
        }
    }
}

void create(struct node **root,int num)		//insertion number in tree
{
	struct node *temp,*ptr;
	if(*root==NULL)
	{
		*root = (struct node*)malloc(sizeof(struct node));
		(*root)->data = num;
		(*root)->left=NULL;
		(*root)->right=NULL;
	}
	else
	{
		temp = (struct node*)malloc(sizeof(struct node));
		temp->data= num;
		temp->left = NULL;
		temp->right= NULL;
		ptr = *root;
		while(ptr!=NULL)
		{
			if(num > ptr->data)
			{
				if(ptr->right!=NULL)
				{
					ptr = ptr->right;
				}
				else
				{
					ptr->right = temp;
					break;
				}
			}
			else
			{
				if(ptr->left!=NULL)
				{
					ptr = ptr->left;
				}
				else
				{
					ptr->left = temp;
					break;
				}
			}
		}
		
	}
}

// mirror of the tree
void mirrorTree(struct node **root) {
    struct stack *top = NULL;
    push(&top, *root);
    while (!isEmpty(top))
	 {
        struct node *temp = pop(&top);
        struct node *curr = temp->right;
        temp->right = temp->left;
        temp->left = curr;
        if (temp->right != NULL)
        {
        	push(&top, temp->right);
		}
           
        if (temp->left != NULL)
        {
        	push(&top, temp->left);
		}
          
    }
    printf("Mirror of Tree Generated Successfully..\n");
}


//Height of a BST 
int findHeight(struct node* root) 
{ 
 
    struct node* temp = root; 
    if(temp == NULL) 
    { 
        return 0; 
    }
   else 
    { 
        int left_height = findHeight(temp->left); 
        int right_height = findHeight(temp->right); 
 
        if(left_height > right_height) 
            return (left_height + 1); 
 
        else 
            return (right_height + 1); 
    } 
}

// delete element from BST 
struct node * deletion(struct node * root , int key) 
{ 
    struct node *temp = root, *prev = NULL; 
 
    if (temp == NULL) 
	{
    	printf("Element does not exist"); 
        return root; 
    }
    while (temp != NULL) 
	{ 
    	if (key < temp->data) 
        { 
            prev = temp; 
            temp = temp->left; 
        } 
        else if (key > temp->data) 
        { 
            prev = temp; 
            temp = temp->right; 
        } 
        else 
        { 
            // Case 1: No child or one child 
            if (temp->left == NULL) 
            { 
                if (prev == NULL) 
                    root = temp->right; 
                else if (prev->left == temp) 
                    prev->left = temp->right; 
                else 
                    prev->right = temp->right; 
                free(temp);
            } 
            else if (temp->right == NULL) 
            { 
                if (prev == NULL) 
                    root = temp->left; 
                else if (prev->left == temp) 
                    prev->left = temp->left; 
                else 
                    prev->right = temp->left; 
                free(temp); 
            } 
            // Case 2: Two children 
            else 
            { 
                struct node *temp2 = temp->left; 
                struct node *prev2 = temp; 
                while (temp2->right != NULL) 
                { 
                    prev2 = temp2; 
                    temp2 = temp2->right; 
                } 
                temp->data = temp2->data; 
                if (prev2 == temp) 
                    prev2->left = temp2->left; 
                else 
                    prev2->right = temp2->left; 
                free(temp2);
			} 
            return root; 
        } 
    }
    return root; 
} 


 
void Level_order(struct node *root) 	//Level wise display 
{ 
    if(root == NULL) 
        return; 
 
    struct node * temp = root; 
    struct QueueTree *q = createQueue(); 
    enqueue(q,root); 
 
    while(!isEmptyQueue(q))
     { 
        temp = dequeue(q); 
        printf("%d ",temp->data); 
 
        if(temp->right != NULL) 
        { 
            enqueue(q,temp->right); 
        } 
        if(temp->left != NULL) 
        { 
            enqueue(q,temp->left); 
        } 
    } 
    free(q); 
}

void displayLeaf(struct node * root) 	// Display leaf nodes of BST
{ 
    struct node * temp = root; 
    struct stack * top = NULL; 
    push(&top,temp); 
 
    while(!isEmpty(top)) 
    { 
        temp = pop(&top); 
 
    if(temp->left == NULL && temp->right == NULL) 
    {
    	 printf("%d ",temp->data); 
 
    } 
    if(temp->right != NULL) 
        push(&top,temp->right); 
 
    if(temp->left != NULL) 
        push(&top,temp->left); 
    }
    free(top); 
    
} 

struct node * insert(struct node * root , int key) // Insert in a BST 
{ 
    struct node * parent = NULL; 
    struct node * temp = root;  
    struct node * newNode = (struct node *)malloc(sizeof(struct node)); 
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return root;
    }
    newNode->left = newNode->right = NULL; 
    newNode->data = key; 
    
    if(temp == NULL) 
    { 
        return newNode; 
    } 
    while(temp != NULL) 
    { 
        parent = temp; 
        if(key < temp->data) 
        { 
            temp = temp->left;
            if (temp == NULL) {
                parent->left = newNode;
                return root;
            }
        } 
        else if(key > temp->data) 
        { 
            temp = temp->right; 
            if (temp == NULL) {
                parent->right = newNode;
                return root;
            }
        } 
        else // Key already exists in the tree 
        { 
            printf("Key already exists in the tree.\n"); 
            free(newNode); 
            return root; 
        } 
    } 
    return root; // This line should never be reached, but added for safety
}




void inorder(struct node *root)		//recursive function of inorder traversal
{
	if(root!=NULL)
	{
		inorder(root->left);
		printf("%d  ",root->data);
		inorder(root->right);
	}
}
void preorder(struct node *root)	//recursive function of preorder traversal
{
	if(root!=NULL)
	{
		printf("%d  ",root->data);
		preorder(root->left);
		preorder(root->right);
	}
}
void postorder(struct node *root)	//recursive function of postorder traversal
{
	if(root!=NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d  ",root->data);
	}
}


