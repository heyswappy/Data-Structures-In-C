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

struct gen_node
{
	int data;
	struct gen_node *first; // first child
	struct gen_node *next;  // next sibling
};

// ============================== STACK ======================================
struct stack_type
{
	int size ;
	int top ;
	struct node **stack ;
};

struct stack_type *create_stack(int a)
{
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

int isfull(struct stack_type *stack)
{
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

int isempty(struct stack_type *stack)
{
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

void push(struct stack_type *stack, struct node* ptr)
{
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

struct node *pop(struct stack_type *stack)
{
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

struct node *top(struct stack_type *stack)
{
	if(stack->top != -1)
	{
		return(stack->stack[stack->top]);
	}
	else
	{
		return NULL;
	}
}

void show_stack(struct stack_type *stack)
{
	for(int i=0; i<((stack->top)+1);i++)
	{
		printf("->%d",stack->stack[i]->data);
	}
	printf("\n");
}

void del_stack(struct stack_type *stack)
{
	free(stack->stack);
	free(stack);
	return;
}

// ======================================= QUEUE =============================================

struct queue_type
{
	int front;
	int back;
	struct node **arr;
	int size;
};

struct queue_type *create_queue(int a)
{
	struct queue_type *ptr = (struct queue_type*)malloc(sizeof(struct queue_type));
	ptr->front = 0;
	ptr->back = 0;
	ptr->size = a;
	ptr->arr = (struct node**)calloc(sizeof(struct node*),a);
	return ptr;
}

void enqueue(struct queue_type *ptr, struct node *d)
{
	ptr->arr[ptr->back] = d;
	ptr->back = ((++(ptr->back))%(ptr->size));
}

struct node *dequeue(struct queue_type *ptr)
{
	struct node *result = ptr->arr[ptr->front];
	ptr->front = ((++(ptr->front))%(ptr->size));
	return result;
}

int q_len(struct queue_type *ptr)
{
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

void show_q(struct queue_type *ptr)
{
	for(int i = ptr->front,count = 0;count<q_len(ptr);count++,i=(i++)%(ptr->size))
	{
		printf("%d<-",ptr->arr[i]->data);
	}
	printf("\n");
}

void del_queue(struct queue_type *ptr)
{
	free(ptr->arr);
	free(ptr);
	return;
}

// ======================================== TREE ==============================================

struct node *create_node(int a);

struct node *create_tree(int n);

void show_tree(struct node *r);

struct node *insert_node_int(struct node *root, int a);

void insert_node_ptr(struct node *root, struct node *ptr);

void preOrder(struct node *root);

int size_of_tree(struct node *root);

void del_tree(struct node **root);

int height_recursive(struct node *root);

int height_loop(struct node *root);

struct node *deepest_node(struct node *root);

struct node *del_tree_element(struct node *tree, int a);

struct node **find_leaf(struct node *ptr, int *a);

int are_similiar(struct node *root1, struct node *root2);

int width(struct node *root);

void all_leaf_paths(struct node *root, struct stack_type *S);

void sum_exist(struct node *root, struct stack_type *S, int *sum, int ans);

void mirror(struct node *root);

int are_mirrors(struct node *root1, struct node *root2);

struct node *LCA(struct node *root, struct node *a, struct node *b);

// ======================================== MAIN ==============================================

void main()
{
	struct node *root = create_BST(15);
}
// ======================================== TREE DEFINITIONS ==============================================

void preOrder(struct node *root)
{
	if(root)
	{
		printf("-%d",root->data);
		preOrder(root->L);
		preOrder(root->R);
	}
}

struct node *create_node(int a)
{
	struct node *ptr = (struct node*)malloc(sizeof(struct node));
	ptr->data = a;
	ptr->L = NULL;
	ptr->R = NULL;
	return ptr;
}

struct node *create_tree(int n)
{
	int count = 0;
	struct queue_type *Q = create_queue(n);

	struct node *root = create_node(count++);
	struct node *temp = root;

	enqueue(Q,root);

	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);

		if(n>count)
		{
			temp->L = create_node(count++);
			enqueue(Q,temp->L);
		}
		else
		{
			return root;
		}

		if(n>count)
		{
			temp->R = create_node(count++);
			enqueue(Q,temp->R);
		}
		else
		{
			return root;
		}
	}

	del_queue(Q);
}

void show_tree(struct node *root)
{
	struct queue_type *Q = create_queue(128);
	struct stack_type *rev = create_stack(128); // to be reversed
	struct stack_type *S = create_stack(128);

	struct node *temp = root;

	enqueue(Q,temp);

	while(q_len(Q)!=0)
	{
		printf("\n");

		// empty all elements to temp stack
		while(q_len(Q)!=0)
		{
			push(rev,dequeue(Q));
		}

		// pushh elements such that stack S has nodes of a level in correct order
		while(!isempty(rev))
		{
			push(S,pop(rev));
		}

		// the loop prints the elemetns of a level
		while(!isempty(S))
		{
			temp = pop(S);

			if(temp)
			{
				printf("%d-",temp->data);
				if(temp->L)
				{
					enqueue(Q,temp->L);
				}
				if(temp->R)
				{
					enqueue(Q,temp->R);
				}
			}

		}

	}
	del_queue(Q);
	del_stack(rev);
	del_stack(S);
}

struct node *insert_node_int(struct node *root, int a)
{
	struct queue_type *Q = create_queue(128);
	enqueue(Q,root);
	struct node *temp = NULL;
	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);
		if(!(temp->L))
		{
			temp->L = create_node(a);
			return temp->L;
		}
		else if(!(temp->R))
		{
			temp->R = create_node(a);
			return temp->R;
		}
		else
		{
			enqueue(Q,temp->L);
			enqueue(Q,temp->R);
		}
	}
	del_queue(Q);
}

void insert_node_ptr(struct node *root, struct node *ptr)
{
	struct queue_type *Q = create_queue(128);
	enqueue(Q,root);
	struct node *temp = NULL;
	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);
		if(!(temp->L))
		{
			temp->L = ptr;
			return;
		}
		else if(!(temp->R))
		{
			temp->R = ptr;
			return;
		}
		else
		{
			enqueue(Q,temp->L);
			enqueue(Q,temp->R);
		}
	}
	del_queue(Q);
}

int size_of_tree(struct node *root)
{
	int size = 0;

	struct queue_type *Q = create_queue(128);
	if(root)
	{
		enqueue(Q,root);
		size++;
	}
	else
	{
		return 0;
	}

	struct node *temp = NULL;
	
	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);
		if(temp->L)
		{
			enqueue(Q,temp->L);
			++size;
		}
		if(temp->R)
		{
			enqueue(Q,temp->R);
			++size;
		}
	}
	del_queue(Q);
	return size;
}

void del_tree(struct node **root)
{
	if(!(*root))
	{
		return;
	}
	del_tree(&((*root)->L));
	del_tree(&((*root)->R));
	(*root)->L = NULL;
	(*root)->R = NULL;
	free(*root);
	*root = NULL;
}

int height_recursive(struct node *root)
{
	if(!root)
	{
		return 0;
	}
	else
	{
		int l = height_recursive(root->L);
		int r = height_recursive(root->R);
		if(l>=r)
		{
			return ++l;
		}
		else
		{
			return ++r;
		}
	}
}

int height_loop(struct node *root)
{
	struct queue_type *Q = create_queue(128);
	struct stack_type *rev = create_stack(128); // to be reversed
	struct stack_type *S = create_stack(128);

	struct node *temp = root;

	enqueue(Q,temp);

	int size = 0;

	while(q_len(Q)!=0)
	{
		size++;

		// empty all elements to temp stack
		while(q_len(Q)!=0)
		{
			push(rev,dequeue(Q));
		}

		// pushh elements such that stack S has nodes of a level in correct order
		while(!isempty(rev))
		{
			push(S,pop(rev));
		}

		// the loop prints the elemetns of a level
		while(!isempty(S))
		{
			temp = pop(S);

			if(temp)
			{
				if(temp->L)
				{
					enqueue(Q,temp->L);
				}
				if(temp->R)
				{
					enqueue(Q,temp->R);
				}
			}

		}

	}
	del_queue(Q);
	del_stack(rev);
	del_stack(S);
	return size;
}

struct node *deepest_node(struct node *root)
{
	struct queue_type *Q = create_queue(128);
	struct node *temp = NULL;
	enqueue(Q,root);

	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);
		if(temp->L)
		{
			enqueue(Q,temp->L);
		}
		if(temp->R)
		{
			enqueue(Q,temp->R);
		}
	}

	// temp has the last node pushed to queue
	del_queue(Q);
	return temp;
}

struct node *del_tree_element(struct node *root, int d)
{
	struct queue_type *Q = create_queue(128);
	struct stack_type *S = create_stack(128);
	struct node *temp = NULL;
	struct node *ans = NULL;
	enqueue(Q,root);
	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);
		if(temp)
		{
			if((temp->data)==d)
			{
				ans = temp;
			}
		}
		if(temp->L)
		{
			enqueue(Q,temp->L);
			push(S,temp->L);
		}
		if(temp->R)
		{
			enqueue(Q,temp->R);
			push(S,temp->R);
		}
	}
	// element not found
	if(!ans)
	{
		return NULL;
	}
	del_queue(Q);
	// ans now has element node and temp has deepest node and stack has all nodes
	struct node *req = NULL;
	while(!isempty(S))
	{
		req = pop(S);
		if ((req->L == temp) || (req->R == temp))
		{
			break;
		}
	}
	if((req->L)==temp)
	{
		ans->data = temp->data;
		free(temp);
		req->L = NULL;
	}
	if((req->R)==temp)
	{
		ans->data = temp->data;
		free(temp);
		req->R = NULL;
	}
	del_stack(S);
	return ans;
}

struct node **find_leaf(struct node *root, int *s)
{
	// int ptr is used to communicate the number of leafs
	// we pass a integer ptr and after function call, it has the no. of leaves
	struct node **arr = (struct node**)calloc(sizeof(struct node*),0);
	int size = 0;
	struct node *temp = NULL;
	struct queue_type *Q = create_queue(128);
	if(!root)
	{
		return NULL;
	}
	enqueue(Q,root);
	
	while(q_len(Q)!=0)
	{
		temp = dequeue(Q);
		if(temp->L)
		{
			enqueue(Q,temp->L);
		}
		if(temp->R)
		{
			enqueue(Q,temp->R);
		}

		if( ((temp->L)==NULL) && ((temp->R)==NULL) )
		{
			// condition for child node
			size++;
			struct node **buf = realloc(arr,size);
			if(!buf)
			{
				printf("MEMORY ERROR\n");
				return NULL;
			}
			else
			{
				arr = buf;
			}
			arr[size-1]=temp;
		}
	}

	for(int i = 0;i<size;i++)
	{
		printf("%d->",(*(arr+i))->data);
	}
	// save the number of leaves to the integers' address passed
	*s = size;
	return arr;
}

int are_similiar(struct node *root1, struct node *root2)
{
	if((!root1)&&(!root2))
	{
		return 1;
	}
	else if( ((root1 == NULL) && (root2 != NULL)) || ((root1 != NULL) && (root2 == NULL)) )
	{
		return 0;
	}
	else
	{
		if((root1->data)==(root2->data))
		{
			if((are_similiar(root1->L,root2->L))&&(are_similiar(root1->R,root2->R)))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
}

int width(struct node *root)
{
	if(!root)
	{
		return 0;
	}
	int left = width(root->L);
	int right = width(root->R);
	if(left>right)
	{
		return(left+1);
	}
	else
	{
		return(right+1);
	}
}

void all_leaf_paths(struct node *root, struct stack_type *S)
{
	if((!(root->L))&&(!(root->R)))
	{
		printf("\n");
		push(S,root);
		show_stack(S);
		printf("\n");
		pop(S);
		return;
	}
	push(S,root);
	if(root->L)
	{
		all_leaf_paths(root->L,S);
	}
	if(root->R)
	{
		all_leaf_paths(root->R,S);
	}
	pop(S);
	return;
}

void sum_exist(struct node *root, struct stack_type *S, int *sum, int ans)
{
	push(S,root);
	*sum += root->data;	
	if(*sum == ans)
	{
		printf("\nPATH : ");
		show_stack(S);
		printf("\n");
		pop(S);
		*sum -= root->data;
		return;
	}	
	if(root->L)
	{
		sum_exist(root->L,S,sum,ans);
	}
	
	if(root->R)
	{
		sum_exist(root->R,S,sum,ans);
	}
	pop(S);
	*sum -= root->data;
	return;
}

void mirror(struct node *root)
{
	if(!root)
	{
		return;
	}
	mirror(root->L);
	mirror(root->R);
	struct node *temp = root->R;
	root->R = root->L;
	root->L = temp;
}

int are_mirrors(struct node *root1, struct node *root2)
{
	if((root1==NULL)&&(root2==NULL))
	{
		return 1;
	}
	if((root1==NULL)||(root2==NULL))
	{
		return 0;
	}
	if(root1->data != root2->data)
	{
		return 0;
	}
	else
	{
		return((are_mirrors(root1->L,root2->R))&&(are_mirrors(root1->R,root2->L)));
	}
}

struct node *LCA(struct node *root, struct node *a, struct node *b)
{
	struct node *left=NULL;
	struct node *right = NULL;
	if(root==NULL)
	{
		return root;
	}
	if(root==a||root==b)
	{
		return root;
	}
	left = LCA(root->L,a,b);
	right = LCA(root->R,a,b);
	if(left&&right)
	{
		return root;
	}
	else
	{
		if(left!=NULL)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
}