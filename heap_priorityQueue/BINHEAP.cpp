#include<iostream>
#include<cstdlib>

class Heap{
private:
	int *arr;
	int count;
public:
	void percolateUp(int i);
	void percolateDown(int i);
	void insert(int a);
	int pop();
	int *sort();
};

void Heap :: percolateUp(int i){
	int parent = (i-1)/2;
	if(parent<0 || i<0){
		return;
	}
	if(arr[parent] < arr[i]){
		int t = arr[parent];
		arr[parent] = arr[i];
		arr[i] = t;
		return percolateUp(parent);
	}
	else{
		return;
	}
	return;
} 

void Heap :: percolateDown(int i = 0){
	int L = 2*i+1;
	int R = 2*i+2;
	int max = i;
	if(L<count && arr[L]>arr[max]){
		max = L;
	}
	if(R<count && arr[R]>arr[max]){
		max = R;
	}
	if(max==i){
		return;
	}
	else{
		//swap them
		int t = arr[max];
		arr[max] = arr[i];
		arr[i] = arr[max];
		return(percolateDown(max));
	}
	return;
}

void Heap :: insert(int n){
	arr[count] = n;
	count++;
	percolateUp(count-1);
	return;
}

int Heap :: pop(){
	int t = arr[0];
	arr[0] = arr[count-1];
	percolateDown(0);
	return t;
}

int* Heap :: sort(){
	int *srt = (int*)calloc(sizeof(int),count);
	for(int i = 0; i<count; i++){
		srt[count-1] = pop();
	}
	return srt;
}