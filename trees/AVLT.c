#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct node{
	int data;
	struct node *L;
	struct node *R;
};

// ============================== STACK ======================================

struct stack_type{
	int size ;
	int top ;
	struct node **stack ;
};
struct stack_type *create_stack(int a){
	struct stack_type *ptr = (struct stack_type*)malloc(sizeof(struct stack_type));
	if(!ptr)
	{
		printf("MEMORY ERROR OF STACK\n");
		return NULL;
	}
	ptr->size = a;
	ptr->top = -1;
	ptr->stack = (struct node**)calloc(sizeof(struct node*),a);
	return ptr;
}
int isfull(struct stack_type *stack){
	if(stack->size==(stack->top+1))
	{
		//printf("STACK IS FULL\n") ;
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}
int isempty(struct stack_type *stack){
	if(stack->top == -1)
	{
		//printf("STACK IS EMPTY\n") ;
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}
void push(struct stack_type *stack, struct node* ptr){
	if( !isfull(stack) )
	{
		stack->top++ ;
		stack->stack[stack->top] = ptr ;
	}
	else
	{
		printf("Push Unsuccessful !\n") ;
	}
}
struct node *pop(struct stack_type *stack){
	if ( !isempty(stack) )
	{
		struct node *result = stack->stack[stack->top] ;
		stack->top-- ;
		return(result);
	}
	else
	{
		printf("Pop Unsuccessful !\n") ;
		return NULL;
	}
}
struct node *top(struct stack_type *stack){
	if(stack->top != -1)
	{
		return(stack->stack[stack->top]);
	}
	else
	{
		return NULL;
	}
}
void show_stack(struct stack_type *stack){
	for(int i=0; i<((stack->top)+1);i++)
	{
		printf("->%d",stack->stack[i]->data);
	}
	printf("\n");
}
void del_stack(struct stack_type *stack){
	free(stack->stack);
	free(stack);
	return;
}

// ======================================= QUEUE =============================================

struct queue_type{
	int front;
	int back;
	struct node **arr;
	int size;
};
struct queue_type *create_queue(int a){
	struct queue_type *ptr = (struct queue_type*)malloc(sizeof(struct queue_type));
	ptr->front = 0;
	ptr->back = 0;
	ptr->size = a;
	ptr->arr = (struct node**)calloc(sizeof(struct node*),a);
	return ptr;
}
void enqueue(struct queue_type *ptr, struct node *d){
	ptr->arr[ptr->back] = d;
	ptr->back = ((++(ptr->back))%(ptr->size));
}
struct node *dequeue(struct queue_type *ptr){
	struct node *result = ptr->arr[ptr->front];
	ptr->front = ((++(ptr->front))%(ptr->size));
	return result;
}
int q_len(struct queue_type *ptr){
	int result;
	if (ptr->front <= ptr->back)
	{
		result = (ptr->back) - (ptr->front);
	}
	else
	{
		result = (ptr->size) - ((ptr->front)-(ptr->back));
	}
	return result;
}
void show_q(struct queue_type *ptr){
	for(int i = ptr->front,count = 0;count<q_len(ptr);count++,i=(i++)%(ptr->size))
	{
		printf("%d<-",ptr->arr[i]->data);
	}
	printf("\n");
}
void del_queue(struct queue_type *ptr){
	free(ptr->arr);
	free(ptr);
	return;
}

void inOrder(struct node *root);

int height(struct node *root);

struct node *rotateSingleLeft(struct node *root);

struct node *rotateSingleRight(struct node *root);

struct node *rotateDoubleLeft(struct node *root);

struct node *rotateDoubleRight(struct node *root);

struct node *insertNode(struct node*root, int n);

void levelOrder(struct node *root);

void main(){
	// do something
	struct node *root= NULL;
	root = insertNode(root,50);
	root = insertNode(root,12);
	root = insertNode(root,45);
	root = insertNode(root,99);
	root = insertNode(root,44);
	root = insertNode(root,48);
	root = insertNode(root,9);
	root = insertNode(root,10);
	root = insertNode(root,86);
	root = insertNode(root,102);
	root = insertNode(root,16);
	root = insertNode(root,28);
	root = insertNode(root,55);
	root = insertNode(root,103);
	root = insertNode(root,88);
	root = insertNode(root,1);

	inOrder(root);
	printf("\n\n");
	levelOrder(root);
}

void inOrder(struct node *root){
	if(root){
		inOrder(root->L);
		printf("%d->",root->data);
		inOrder(root->R);
	}
	return;
}
int height(struct node *root){
	if(!root){
		return -1;
	}
	int l = height(root->L);
	int r = height(root->R);
	if(l>r){
		return l+1;
	}
	else{
		return r+1;
	}
}
struct node *rotateSingleLeft(struct node *root){
	struct node *temp = root->L;
	root->L = temp->R;
	temp->R = root;
	return temp;
}
struct node *rotateSingleRight(struct node *root){
	struct node *temp = root->R;
	root->R = temp->L;
	temp->L = root;
	return temp;
}
struct node *rotateDoubleLeft(struct node *root){
	root->L = rotateSingleRight(root->L);
	return rotateSingleLeft(root);
}
struct node *rotateDoubleRight(struct node *root){
	root->R = rotateSingleLeft(root->R);
	return rotateSingleRight(root);
}
struct node *insertNode(struct node*root, int n){
	struct node *temp = NULL;
	if(!root){
		temp = (struct node*)malloc(sizeof(struct node));
		temp->data = n;
		temp->L = NULL;
		temp->R = NULL;
		return temp;
	}
	else if(root->data > n){
		root->L = insertNode(root->L, n);
		if(height(root->L)-height(root->R)==2){
			// insertion in left subtree hece its height larger
			if(root->L->data > n){
				// insertion in left node left subtree
				root = rotateSingleLeft(root);
			}
			else{
				// insertion in left node left subtree
				root = rotateDoubleLeft(root);
			}
		}
	}
	else if(root->data < n){
		root->R = insertNode(root->R, n);
		if(height(root->R)-height(root->L)==2){
			// insertion in right subtree hece its height larger
			if(root->R->data < n){
				//insertion in right node right subtree
				root = rotateSingleRight(root);
			}
			else{
				// insertion in right node right subtree
				root = rotateDoubleRight(root);
			}
		}
	}
	else{
		// element already exists
	}
	return root;
}
void levelOrder(struct node *root){
	struct queue_type *Q = create_queue(100);
	struct queue_type *S = create_queue(100);
	enqueue(Q,root);
	struct node *temp = NULL;

	// print current level
	while(q_len(Q)!=0){
		getch();
		while(q_len(Q)!=0){
			temp = dequeue(Q);
			printf("%d-",temp->data);
			enqueue(S,temp);
		}
		// insert next level
		while(q_len(S)!=0){
			temp = dequeue(S);
			if(temp->L){
				enqueue(Q, temp->L);
			}
			if(temp->R){
				enqueue(Q, temp->R);
			}
		}
		printf("\n");
	}
	return;
}
