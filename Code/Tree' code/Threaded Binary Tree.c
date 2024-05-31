#include<stdio.h>
#include<stdlib.h>
struct TBTNode
{
	int lbit, rbit;
	int data;
	struct TBTNode *left,*right;
};
struct TBTNode* create(struct TBTNode *head , int key)
{
	struct TBTNode *temp,*p;
	temp = (struct TBTNode*) malloc(sizeof(struct TBTNode));
	temp->data = key;
	temp->lbit = 0;
	temp->rbit = 0;
	if(head->lbit==0)
	{
		head->lbit = 1;
		head->left = temp;
		temp->left = head;
		temp->right = head;
	
		return head;
	}
	p = head->left;
	while(1)
	{
		if( p->data > key  && p->lbit == 1)
		{
			p=p->left;
		}
		else if(p->data < key && p->rbit==1)
		{
			p=p->right;
		}
		else
			break;
	}
	if(p->data > key)
	{
		temp->right = p;
		temp->left = p->left;
		p->left = temp;
		p->lbit=1;
		
	}
	if(p->data < key)
	{
		temp->left = p;
		temp->right = p->right;
		p->right = temp;
		p->rbit = 1;

	}
	return head;
}

//preorder traversal
void preorder(struct TBTNode *head)
{
	struct TBTNode *p= NULL;
	p = head->left;
	while(p!=head)
	{
		printf("%d  ",p->data);
		if(p->lbit==1)
		{
			p=p->left;
		}
		else if(p->rbit==1)
		{
			p=p->right;
		}
		else if(p->rbit == 0)
		{
			while(p->rbit==0)
			{
				p=p->right;
			}
			p=p->right;
		}
	}
}

// Inorder Traversal
void inorder(struct TBTNode *head)
{
    struct TBTNode *temp = head->left;
    while (temp->lbit == 1)
    {
        temp = temp->left;
    }
    while (temp != head)
    {
        printf("%d  ", temp->data);
        if (temp->rbit == 1)
        {
            temp = temp->right;
            while (temp->lbit == 1)
            {
                temp = temp->left;
            }
        }
        else
        {
            temp = temp->right;
        }
    }
}


struct TBTNode* findParent(struct TBTNode* p) {
   struct TBTNode* child = p;

   while (p->rbit == 1) p = p->right;
   p = p->right;

   if (p->left == child)
       return p;

   p = p->left;
   while (p->right != child) {
       p = p->right;
   }
   return p;
}


struct TBTNode* postSuccessor(struct TBTNode* p) {
   struct TBTNode* cur = p;
   struct TBTNode* parent = findParent(cur);

   if (parent->right == cur) return parent;
   else {
       while (p->rbit == 1) p = p->right;
       p = p->right;

       if (p->rbit == 1) {
           p = p->right;
           while (!(p->rbit == 0 && p->lbit == 0)) {
               if (p->lbit == 1) p = p->left;
               else if (p->rbit == 1) p = p->right;
           }
       }
   }
   return p;
}

// postorder traversal
void postorder(struct TBTNode* head) {
   struct TBTNode* p = head->left;
   struct TBTNode* temp = p;
   while (!(p->rbit == 0 && p->lbit == 0)) {
       if (p->lbit == 1) {
           p = p->left;
       }
       else if (p->rbit == 1) p = p->right;
   }
   printf("%d  ", p->data);

   while (p != head->left) {
       p = postSuccessor(p);
       printf("%d  ", p->data);
   }
}

int main()
{
	struct TBTNode *head = NULL;
	int n,i,key;
	head = (struct TBTNode*)malloc(sizeof(struct TBTNode));
	head->data = -1;
	head->left = head;
	head->right = head;
	head->rbit = 1;
	head->lbit = 0;

	printf("Enter the number of nodes : ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Enter the value %d: ",i+1);
		scanf("%d",&key);
		head = create(head,key);
	}
	
	printf("\nPreorder Traversal....\n");
	preorder(head);
	
	printf("\nInorder Traversal....\n");
	inorder(head);
	
	printf("\nPostorder Traversal....\n");
	postorder(head);
	free(head);
	return 0;
}
