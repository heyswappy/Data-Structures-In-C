#include<stdio.h>
#include<stdlib.h>

struct stack_type
{
	int size ;
	int top ;
	int *stack ;
};

struct stack_type *create_stack(int a);
int isfull(struct stack_type *stack);
int isempty(struct stack_type *stack);
void push(struct stack_type *stack, int a) ;
int pop(struct stack_type *stack) ;
int top(struct stack_type *stack);
void show_stack( struct stack_type *stack);

int main(void)
{
	// DO SOMETHING
}

struct stack_type *create_stack(int a)
{
	struct stack_type *ptr = (struct stack_type*)malloc(sizeof(struct stack_type));
	ptr->size = a;
	ptr->top = -1;
	ptr->stack = (int *)calloc(sizeof(int),a);
	return ptr;
}
int isfull(struct stack_type *stack)
{
	if(stack->size==(stack->top+1))
	{
		printf("Stack Overflow") ;
		return 0 ;
	}
	else
	{
		return 1 ;
	}
}

int isempty(struct stack_type *stack)
{
	if(stack->top == -1)
	{
		printf("Stack Underflow") ;
		return 0 ;
	}
	else
	{
		return 1 ;
	}
}

void push(struct stack_type *stack, int data)
{
	if( isfull(stack) )
	{
		stack->top++ ;
		stack->stack[stack->top] = data ;
	}
	else
	{
		printf("\nPush Unsuccessful !") ;
	}
}

int pop(struct stack_type *stack)
{
	if ( isempty() )
	{
		int result = stack->stack[stack->top] ;
		stack->top-- ;
		return(result);
	}
	else
	{
		printf("\nPop Unsuccessful !") ;
	}
}

int top(struct stack_type *stack)
{
	if(stack->top != -1)
	{
		return(stack->stack[statck->top]);
	}
	else
	{
		return -1;
	}
}

void show_stack(struct stack_type *stack)
{
	for(int i=0; i<(stack->size);i++)
	{
		printf("->%d",stack->stack[i]);
	}
	printf("\n");
}

void del_stack(struct stack_type *stack)
{
	free(stack->stack);
	free(stack);
	return;
}