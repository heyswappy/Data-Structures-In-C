#include<stdio.h>
#include<stdlib.h>

struct heap_type{
	int *arr; // main arr pointer
	int *dat; // integer data
	int count; // number of elements in the heap
	int size; // full capacity
	int type; // 0 is min_heap, 1 is max_heap
};

struct heap_type *create_heap(int capacity, int type){
	struct heap_type *ptr = (struct heap_type*)malloc(sizeof(struct heap_type));
	if(!ptr){
		printf("MEMORY ERROR\n");
		return NULL;
	}
	ptr->arr = (int*)calloc(sizeof(int),capacity);
	ptr->dat = (int*)calloc(sizeof(int),capacity);
	if(!(ptr->arr)){
		printf("MEMORY ERROR\n");
		return NULL;
	}
	ptr->count = 0;
	ptr->size = capacity;
	ptr->type = type;
	return ptr;
}

void percolate_down(struct heap_type *ptr, int i){
	int l ,r; // left and right indices
	l = 2*i+1;
	r = l+1;
	if(l>(ptr->count-1))
	{
		// prevent out of index and accessing garbage
		l = -1;
	}
	if(r>(ptr->count-1))
	{
		// prevent out of index and accessing garbage
		r = -1;
	}
	int max = i ;
	if((l != (-1)) && ((ptr->arr[l])>(ptr->arr[max]))){
		// if left index exists and value their is greater then parent then this executes
		max = l;
	}
	if((r != (-1)) && ((ptr->arr[r])>(ptr->arr[max]))){
		// if right index exists and value their if greater then parent then this executes
		max = r;
	}
	int temp = 0;
	if(max != i){
		// max!=i means a child is greater then parent
		// swap them, the priorities
		temp = ptr->arr[i];
		ptr->arr[i] = ptr->arr[max];
		ptr->arr[max] = temp;
		// swap the data corresponding to priority
		temp = ptr->dat[i];
		ptr->dat[i] = ptr->dat[max];
		ptr->arr[max] = temp;
	}
	else
	{
		return;
	}
	percolate_down(ptr,max);
}

int del_max(struct heap_type *ptr){
	int data = ptr->dat[0];
	ptr->arr[0] = ptr->arr[--(ptr->count)];
	ptr->dat[0] = ptr->dat[ptr->count];
	percolate_down(ptr,0);
	return data;
}

void insert(struct heap_type *ptr, int i){
	ptr->arr[ptr->count] = i;
	ptr->count++;
	
	for(int j = (ptr->count)-1; j!=0; j--){
		if((ptr->arr[j])>(ptr->arr[(j-1)/2])){
			// swap them
			int temp = ptr->arr[(j-1)/2];
			ptr->arr[(j-1)/2] = ptr->arr[j];
			ptr->arr[j] = temp; 
		}
		else{
			//else heap property satisfied
			return;
		}
	}
}

void del_heap(struct heap_type *ptr)
{
	free(ptr->arr);
	free(ptr->dat);
	free(ptr);
	return;
}

struct heap_type *build_heap(int n)
{
	struct heap_type *H = create_heap(n,1);
	int t,u;
	int i;
	for( i = 0; i<n; i++)
	{
		scanf("%d %d",&t,&u);
		H->arr[i] = t;
		H->dat[i] = u;
	}
	H->count = n;	
	for( i = ((n-1)/2); i>-1; i--)
	{
		percolate_down(H,i);
	}
	return H;
}

void show_heap(struct heap_type *ptr){
	printf("**HEAP_PRI**\n");
	int i = 0;
	int j = 0;
	for(i = 0, j=1; ;j = j*2+1){
		for(int k = i; k < j; k++){
			printf("%d-",ptr->arr[i]);
			i++;
			if(i>=(ptr->count)){
				printf("\nRETURNED\n");
				return;
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("**HEAP_DAT**\n");
	int i = 0;
	int j = 0;
	for(i = 0, j=1; ;j = j*2+1){
		for(int k = i; k < j; k++){
			printf("%d-",ptr->dat[i]);
			i++;
			if(i>=(ptr->count)){
				printf("\nRETURNED\n");
				return;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void show(struct heap_type *ptr){
	printf("HEAP_PRI<-");
	for(int i = 0 ;i<(ptr->count);i++){
		printf("%d<-",ptr->arr[i]);
	}
	printf("\n");
	printf("HEAP_DAT<-");
	for(int i = 0 ;i<(ptr->count);i++){
		printf("%d<-",ptr->dat[i]);
	}
	printf("\n");
}

void build_from_arr(struct heap_type *H, int *pri, int *dat, int n){
	int i;
	for( i = 0; i<n; i++){
		H->arr[i] = pri[i];
		H->dat[i] = dat[i];
	}
	H->count = n;	
	for( i = ((n-1)/2); i>-1; i--){
		percolate_down(H,i);
	}
}

int *heapsort(int *pri, int *dat, int n){
	struct heap_type *H = create_heap(n,1);
	build_from_arr(H,pri,dat,n);
	// binary heap created
	int orig_size = H->count;
	int t;
	for(int i = (n-1); i > 0; i--)
	{
		t = H->arr[0];
		H->arr[0] = H->arr[(H->count)-1];
		H->arr[(H->count)-1] = t;
		H->count--;
		percolate_down(H,0);
	}
	free(H->arr);
	int *result = H->dat;
	free(H); // free H but not H->arr as both are allocated
	return result;
}

void main(){
	int s;
	scanf("%d",&s);
	int arr[s];
	for(int i =0;i<s;i++)
	{
		scanf("%d",arr+i);
	}
	int *r = heapsort(arr,s);
	printf("0");
	for(int i =0;i<s;i++)
	{
		printf("<%d",*(r+i));
	}
}