#include<stdio.h>
#include<stdlib.h>

struct queue_type{
	int front; // points to first element
	int back; // points to that cell which would be filled next
	int *arr; // main arr pointer
	int size; // full capacity
	int len; // current lenght
};

struct queue_type *create_queue(int a){
	struct queue_type *ptr = (struct queue_type*)malloc(sizeof(struct queue_type));
	ptr->front = 0;
	ptr->back = 0;
	ptr->size = a+1;
	ptr->len = 0;
	ptr->arr = (int *)calloc(sizeof(int),(a+1));
	return ptr;
}

void del_queue(struct queue_type *ptr){
	free(ptr->arr);
	free(ptr);
	return;
}

void show(struct queue_type *ptr){
	printf("QUEUE<-");
	for(int i =(ptr->front),count = 0;(count)<q_len(ptr);count++,i=(i+1)%(ptr->size))
	{
		printf("%d<-",ptr->arr[i]);
	}
	printf("\n");
}

int q_len(struct queue_type *ptr){
	// returns lenght
	return(ptr->len);
}

int is_full(struct queue_type *ptr){
	if((ptr->len)==((ptr->size)-1)){
		return 1;
	}
	return 0;
}

void right_shift(struct queue_type *ptr, int index){
	//make space at index
	int last = ((ptr->back)+1)%(ptr->size);
	int c = 0; //current
	int n = (ptr->arr)[index]; //next
	for(int i=index ; i!=last;){
		c = n;
		i = ((i+1)%(ptr->size));
		n = (ptr->arr)[i];
		(ptr->arr)[i] = c;
	}
	return;
}

void sorted_insert(struct queue_type *ptr, int d){
	// front of the queue has the largest element and back has the smallest element
	// assume that the queue is sorted
	// empty queue
	if((ptr->len)==0)
	{
		(ptr->arr)[ptr->back] = d;
		ptr->back = (((ptr->back)+1))%(ptr->size) ;
		(ptr->len)++;
		return;
	}
	// insert in middle
	for(int i = ptr->front; i<q_len(ptr); )
	{
		if((ptr->arr)[i]<=d)
		{
			right_shift(ptr,i);
			(ptr->arr)[i]=d;
			(ptr->len)++;
			ptr->back = (((ptr->back)+1))%(ptr->size) ;
			return;
		}
		i=((i+1)%(ptr->size));
	}
	// insert at end
	ptr->arr[ptr->back] = d;
	ptr->back = (((ptr->back)+1))%(ptr->size) ;
	(ptr->len)++;
	return;
}

void enqueue(struct queue_type *ptr, int d){
	// call sorted insert
	if(is_full(ptr))
	{
		return;
	}
	sorted_insert(ptr,d);
}

int get_min(struct queue_type *ptr){
	int last = ptr->back;
	if(last==0){
		last = (ptr->size)-1;
	}
	else{
		last = (ptr->back)-1;
	}
	int result = (ptr->arr)[last];
	(ptr->back)--;
	if((ptr->back)<0){
		ptr->back = (ptr->size)-1 ;
	}
	(ptr->len)--;
	return result;
}

int get_max(struct queue_type *ptr){
	int first = ptr->front;
	int result = (ptr->arr)[first];
	(ptr->front)=((ptr->front)+1)%(ptr->size);
	if((ptr->front)==(ptr->size))
	{
		ptr->front = 0 ;
	}
	(ptr->len)--;
	return result;
}

void main(){
	//do something
}