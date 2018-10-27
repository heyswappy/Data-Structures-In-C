#include<stdio.h>
#include<stdlib.h>

struct SET{
	int *arr;
	int n;
};

struct SET* MAKESET(int n){
	// create new set with setnames from 0 to n-1 which also serve as the elements
	struct SET* ptr = (struct SET*)malloc(sizeof(struct SET));
	ptr->arr = (int*)calloc(sizeof(int),n);
	for(int i=0; i<n; i++){
		ptr->arr[i] = -1;
	}
	ptr->n = n;
	return ptr;
}
int FIND(struct SET *st, int n){
	// find the name of the set n belongs to
	if(st->arr[n] == -1){
		return n;
	}
	return(st,st->arr[n]);
}
void UNION(struct SET *st, int a, int b){
	// union the sets that have a and b
	if( FIND(st,a) == FIND(st,b) ){
		// already in same set
		return;
	}
	if(FIND(st,a)<FIND(st,b)){
		st->arr[a] = b;
		st->arr[b] += st->arr[a];
	}
	else{
		st->arr[b] = a;
		st->arr[a] += st->arr[b];
	}
	return;
}

void main(){
	// do somethign
}
