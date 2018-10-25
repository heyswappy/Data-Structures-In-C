#include<stdio.h>
#include<stdlib.h>

struct queue_type
{
	int front;
	int back;
	int *arr;
	int size;
};

struct queue_type *create_queue(int a)
{
	struct queue_type *ptr = (struct queue_type*)malloc(sizeof(struct queue_type));
	ptr->front = 0;
	ptr->back = 0;
	ptr->size = a;
	ptr->arr = (int *)calloc(sizeof(int),a);
	return;
}

void enqueue(struct queue_type *ptr, int d)
{
	ptr->arr[ptr->back] = d;
	ptr->back = (((ptr->back)+)%(ptr->size));
}

int dequeue(struct queue_type *ptr)
{
	int result = ptr->arr[ptr->front];
	ptr->front = (((ptr->front)+)%(ptr->size));
	return result;
}

int q_len(struct queue_type *ptr)
{
	int size;
	if (ptr->front <= ptr->back)
	{
		size = (ptr->back) - (ptr->front)
	}
	else
	{
		result = (ptr->size) - ((ptr->front)-(ptr->back));
	}
	return result;
}

void show(struct queue_type *ptr)
{
	for(int i = front,count = 0;count<ptr->q_len(ptr);count++,i=(i++)%(ptr->size))
	{
		printf("%d<-",ptr->arr[i]);
	}
	printf("\n");
}

void del_queue(struct queue *ptr)
{
	free(ptr->arr);
	free(ptr);
	return;
}

void main()
{
	//do something
}