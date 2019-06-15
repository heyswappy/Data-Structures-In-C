#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<conio.h>

using namespace std;

class SegTree{
private:
	int *arr;
	int l;
	int full; // number of all nodes
	int minVal;
	int maxVal;
	bool isMinSegTree;
	int updateMin(int i);
	int updateMax(int i);
	int queryMain(int i, int j, int start, int ends, int cur);
public:
	SegTree(int *arr, int n, bool minSegTree);
	~SegTree();
	void build();
	int query(int i, int j);
	void show();
};

SegTree :: SegTree(int *arr, int n, bool minSegTree){
    if(!arr) return;
	int i,j,power  = 1;
	// determine the size of array
	while(n > power){
		power = power*2;
	}
	power = power*2;
	// allocate the objects elements appropriately
	this->arr = (int*)calloc(sizeof(int),power);
	// cout<<"ALLOCATE POWER:"<<power<<"\n";
	l = power/2;
	full = power;
	minVal = arr[0];
	maxVal = arr[0];
	isMinSegTree = minSegTree;
	// initialize the object array
	for(i = 0;i<n;i++){
		//cout<<power/2+1+i<<"-"<<arr[i];
		(this->arr)[power/2+i] = arr[i];
	}
	//cout<<"ALLOCATED AND INITIALIZED";
	// determine min and max for padding
	for(j=1;j<n;j++){
        if(arr[j]<minVal) minVal=arr[j] ;
        if(arr[j]>maxVal) maxVal=arr[j] ;
	}
	//cout<<"DETERMINE MINMAX";
	// apply the padding
	// remember i already has the index of last element
	if(isMinSegTree){
        // if it is a minSegTree
        for(;i<power/2;i++){
        	(this->arr)[(power/2)+i] = maxVal;
        }
	}
	else{
        // if it is a maxSegTree
        for(;i<power/2;i++){
            (this->arr)[(power/2)+i] = minVal;
        }
	}
	//cout<<"PADDED";
}

SegTree :: ~SegTree(){free(arr);}

void SegTree :: build(){
	isMinSegTree?updateMin(1):updateMax(1);
	return;
}

int SegTree :: updateMin(int i){
    //cout<<"ENTERING WITH VALUE:"<<i<<" "<<l<<"\n";
	// end of tree
	if(i>=full){
		if(isMinSegTree) return maxVal;
		return minVal;
	}
	// itermediate node
	if(i<l){
		arr[i] = min(updateMin(2*i),updateMin(2*i+1));
        //cout<<"UPDATED INDEX"<<i<<"WITH VALUE"<<arr[i]<<"\n";
	}
	// leaf node
	return arr[i];
}

int SegTree :: updateMax(int i){
    //cout<<"ENTERING WITH VALUE:"<<i<<" "<<l<<"\n";
	// end of tree
	if(i>=full){
		if(isMinSegTree) return maxVal;
		return minVal;
	}
	// itermediate node
	if(i<l){
		arr[i] = max(updateMax(2*i),updateMax(2*i+1));
        //cout<<"UPDATED INDEX"<<i<<"WITH VALUE"<<arr[i]<<"\n";
	}
	// leaf node
	return arr[i];
}

int SegTree :: query(int i, int j){
	return queryMain(i,j,0,l-1,1);
}

int SegTree :: queryMain(int i, int j, int start, int ends, int cur){
	/* i and j are the query indices, start and end are the array endpoints,
		cur is currentnode index*/
	if(cur>=full) return isMinSegTree?maxVal:minVal;
	//printf("Query(%d,%d), Search(%d,%d) ,CurrentNode: %d\n",i,j,start,ends,cur); getch();
	int mid = (start+ends)/2 ;
	// full overlap
	if(i==start && j==ends){
		return arr[cur];
	}
	//no overlap
	if( (i>=start) && (i<=mid) && (j>=start) && (j<=mid) ){
		return(queryMain(i,j,start,mid,cur*2));
	}
	if( (i>=mid+1) && (i<=ends) && (j>=mid+1) && (j<=ends) ){
		return(queryMain(i,j,mid+1,ends,cur*2+1));
	}
	// partial overlap
	if( (i>=start) && (i<=mid) && (j<=ends) && (j>=mid+1) ){
		int a = queryMain(i,mid,start,mid,cur*2);
		int b = queryMain(mid+1,j,mid+1,ends,cur*2+1);
		int t = isMinSegTree?min(a,b):max(a,b);
		return t;
	}
	return -1;
}

void SegTree :: show(){
	for(int i = 0; i < full; i++){
		cout<<i<<"-"<<arr[i]<<"\n";
	}
}

int main(){
    int arr[15] = {1,17,56,23,2,3,8,9,6,19,5,10,78,55,99};
	SegTree myTree = SegTree(arr,15,false);
	myTree.build();
	myTree.show();
	int a = myTree.query(6,9);
	return 0;
}
