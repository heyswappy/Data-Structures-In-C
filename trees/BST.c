#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

struct node
{
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

// ======================================== TREE ==============================================




struct node *newBST(int n){
	struct *root;
	while(n){
		root = insertNode(n--);
	}
	return root;
}

struct node *newBSTarr(int n){
	int t;
	struct node *root = NULL;
	while(n){
		scanf("%d",t);
		root = insertNode(root,t);
	}
	return root;
}

struct node *buildBST(int *arr, int start, int end);

struct node *findMin(struct node *root);

struct node *findMax(struct node *root);

struct node *insertNode(struct node *root, int n);

struct node *delNode(struct node *root, int n);

struct node *LCA(struct node *root, int a, int b);

int *isBST(struct node *root);

// ======================================== MAIN ==============================================

void main()
{
	struct node *root = create_BST(15);
}
// ======================================== TREE DEFINITIONS ==============================================

struct node *buildBST(int *arr, int start, int end){
	struct node *root;
	if(!arr){
		return NULL;
	}
	if(start > end){
		return NULL;
	}
	else if(start == end){
		root = (struct node*)malloc(sizeof(struct node));
		root->data = arr[start];
		root->L = NULL;
		root->R = NULL;
		return root;
	}
	else{
		int mid = (start+end)/2;
		root->data = arr[mid];
		root->L = buildBST(arr, start, mid-1);
		root->R = buildBST(arr, mid+1, end);
		return root;
	}
	return root;
}
struct node *findMin(struct node *root){
	if(!root){
		return root;
	}
	else{
		while(root->L){
			root = root->L;
		}
		return root;
	}
	return root;
}
struct node *findMax(struct node *root){
	if(!root){
		return root;
	}
	else{
		while(root->R){
			root = root->R;
		}
		return root;
	}
	return root;
}
struct node *insertNode(struct node *root, int n){
	struct node *temp;
	if(!root){
		temp = (strcut node*)malloc(sizeof(struct node));
		temp->data = n;
		temp->L = NULL;
		temp->R = NULL;
		return temp;
	}
	else if(root->data > n){
		root->L = insertNode(root->L,n);
	}
	else if(root->data > n){
		root->R = insertNode(root->R,n);
	}
	else{
		// element already exists
	}
	return root;
}
struct node *delNode(struct node *root, int n){
	struct node *temp;

	if(root==NULL){
		// elemet not found
		return root;
	}
	else if(root->data > n){
		root->L = delNode(root->L,n);
	}
	else if(root->data < n){
		root->R = delNode(root->L,n);
	}
	else{
		// node found
		if(root->L && root->R){
			// both children
			temp = findMax(root->L);
			root->data = temp->data;
			root->L = delNode(root->L,root->data);
		}
		else{
			// single child
			temp = root;
			if(root->L==NULL){
				root = root->R;
			}
			if(root->R==NULL){
				root = root->L;
			}
			free(temp);
		}
	}
	return root;
}
struct node *LCA(struct node *root, struct node *a, struct node *b){
	while(1){
		if(((root->data > a->data)&&(root->data < b))||((root->data < a)&&(root->data > b))){
			return root;
		}
		if(root->data > a->data){
			root = root->L;
		}
		else{
			root = root->R;
		}
	}
	return root;
}
int *isBST(struct node *root){
	if(root->data > findMax(root->L)){
		return 0;
	}
	if(root->data < findMin(root->R)){
		return 0;
	}
	if(!isBST(root->L) || !isBST(root->R)){
		return 0;
	}
	// passing all that its a bst
	return 1;
}