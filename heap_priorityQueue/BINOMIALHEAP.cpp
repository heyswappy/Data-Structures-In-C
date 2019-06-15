#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<bits/stdc++.h>
#define isDebug false

class BinoNode{
private:
	BinoNode *P; //parent
	BinoNode *S; // sibling
	BinoNode *L; // leftmost child
	int data;
	int order;
	BinoNode(int d);
friend class BinoHeap;
};
BinoNode :: BinoNode(int d){
	data = d;
	order = 1;
	P=S=L=NULL;
}

class BinoHeap{
private:
	BinoNode *head;
	void mergeMain(BinoNode *parent, BinoNode *child);
    BinoNode* merge(BinoNode *ptr1, BinoNode *ptr2);
    BinoNode* insertSingle(int node);
    BinoNode* fix(BinoNode *root);
    void sortedNodeInsert(BinoNode *root);
    void traverse(BinoNode *root);
public:
    BinoHeap();
    void insert(int d);
    void describe();
    int extractMin();
};
BinoHeap :: BinoHeap(){
	// create heap
    head = NULL;
}
void BinoHeap :: mergeMain(BinoNode *parent, BinoNode *child){
	if(isDebug) printf("IN MERGEMAIN WITH PARENT: %d AND CHILD: %d\n",parent->data,child->data);
	BinoNode *tmp = parent->L;
	parent->L = child;
	child->P = parent;
	child->S = tmp;
	parent->order += 1;
	if(isDebug) printf("MERGEMAIN COMPLETED\n");
    return;
}
BinoNode* BinoHeap :: merge(BinoNode *ptr1, BinoNode *ptr2){
	if(isDebug) printf("IN MERGE FUNCTION; ABOUT TO MERGE %d %d\n",ptr1->data,ptr2->data);
    if((ptr1->data)>(ptr2->data)){
    	if(isDebug) printf("FIRST CANDIDATE IS GREATER WITH KEY: %d\n",ptr1->data);
        mergeMain(ptr2, ptr1);
        if(isDebug) printf("RETURNING FROM MERGE\n");
        return ptr2;
    }
    if(isDebug) printf("SECOND CANDIDATE IS GREATER WITH KEY: %d\n",ptr2->data);
    // this to ensure proper connections at topmost level
    // no need to do this in above if case
    BinoNode *sibling = ptr2->S;
    mergeMain(ptr1, ptr2);
    ptr1->S = sibling;
    if(isDebug) printf("RETURNING FROM MERGE\n");
    return ptr1;
}
BinoNode* BinoHeap :: insertSingle(int d){
	if(isDebug) printf("INSERTING SINGLE: %d\n",d);
    BinoNode *tmp = new BinoNode(d);
    tmp->S = this->head;
    if(isDebug) printf("RETURING FROM INSERT SINGLE\n");
    return tmp;
}
void BinoHeap :: insert(int d){
	if(isDebug) printf("CALLING INSERTSINGLE\n");
    this->head = insertSingle(d);
    if(isDebug) this->describe();
    if(isDebug) printf("CALLING TO FIX VIOALTIONS\n");
    this->head = fix(this->head);
    if(isDebug) printf("FIXED AND RETURNING\n");
    return;
}
BinoNode* BinoHeap :: fix(BinoNode *root){
	if(!root){ return this->head; }
	if(isDebug) printf("IN FIX %d\n",root->data);
    if(!(root->S)){
        // last node so return sibling
        if(isDebug) printf("RETURNING DUE TO NULL FROM FIX\n");
        return root;
    }
    BinoNode *sibling = fix(root->S);
    // update new merged siblings (if any)
    root->S = sibling;
    if(isDebug) printf("GOT SIBLING FROM FIX FUNCTION!\n");
    while((root->order)==(sibling->order)){
        // if same order merge
        if(isDebug) printf("SAME ORDER BETWEEN %d AND %d\n",root->data,sibling->data);
        root = merge(root,root->S);
        if(!(root->S)){
            // if no sibling exit the loop to return
            break;
        }
        sibling = root->S;
    }
    if(isDebug) printf("RETURNING FROM FIX FUNCTION\n");
    return root;
}
void BinoHeap :: sortedNodeInsert(BinoNode *root){
	if(!root) return;
	if(!(this->head)){
		if(isDebug) printf("FOUND NULL HEAD WHILE INSERTING NODE: %d\n",root->data);
		this->head = root;
		root->S = NULL;
		root->P = NULL;
		return;
	}
	if(isDebug) printf("IN SORTED INSERT FOR NODE: %d\n",root->data);
	BinoNode *ptr = this->head;
	if(ptr->order > root->order){
		// the given binomial tree has order smaller then that of first tree
		if(isDebug) printf("THE TREE WITH ROOT: %d HAS ORDER SMALLER THEN ROOT OF TREE\n",root->data);
		root->S = this->head;
		root->P = NULL;
		this->head = root;
		return;
	}
	if(isDebug) printf("ABOUT TO WHILE LOOP\n");
	while(ptr->order <= root->order){
		if(!(ptr->S)){
			break;
		}
		ptr = ptr->S;
	}
	// if ptr then it means insertion in middle but then insertion at last
	// last of the list will also lead to the same code so need to check ptr
	if(isDebug) printf("INSERT ROOT: %d AFTER ROOT: %d\n",root->data,ptr->data);
	root->S = ptr->S;
	root->P = NULL;
	ptr->S = root;
	if(isDebug) printf("RETURNING FROM SORTED INSERT\n");
	return;
}
int BinoHeap :: extractMin(){
	if(isDebug) printf("IN EXTRACT MIN\n");
	if(!(this->head)) return -1;
	int minVal = this->head->data;
	BinoNode *prev = this->head;
	BinoNode *cur = this->head->S;
	BinoNode *minNode = this->head;
	BinoNode *minPrev = this->head;
	while(cur){
		if(cur->data < minVal){
			minPrev = prev;
			minVal = cur->data;
			minNode = cur;
		}
		prev = cur;
		cur = cur->S;
	}
	// delete the root selected and merge all children binomial trees
	if(isDebug)
		printf("ISOLATE THE ROOT OF THE TREE ABOUT TO REMOVE NODE: %d WITH PREV NODE: %d\n",minNode->data,minPrev->data);
	// isolation of root node is different
	if(minPrev == minNode){
		if(isDebug) printf("FIRST ROOT SELECTED EXTRACT MIN HENCE UPDATE OBJECT'S ROOT\n");
		this->head = minNode->S;
	}
	// the following statement helps isolate non root trees and has no effect on root trees
	minPrev->S = minNode->S;
	BinoNode *childItr = minNode->L;
	// set left pointer null
	minNode->L = NULL;
	while(childItr){
		if(isDebug) printf("INSERTING THE CHILD TREE OF ISOLATED TREE WITH ROOT: %d\n",childItr->data);
		BinoNode *nxt = childItr->S;
		sortedNodeInsert(childItr);
		childItr = nxt;
	}
	if(isDebug) printf("DELETING NODE\n");
	delete minNode;
	if(isDebug) printf("CALLING TO FIX ON NODE: %d\n",this->head);
	if((isDebug)&&(this->head)) printf("CALLING TO FIX ON NODE NUMBER: %d\n",this->head->data);
	this->head = fix(this->head);
	if(isDebug) printf("RETURNING FROM EXTARCT MIN\n");
	return minVal;
}
void BinoHeap :: traverse(BinoNode *root){
	// traverse the tree
	if(!root){
		printf("ENCOUNTERED NULL RETURNING\n");
		return;
	}
	printf("TRAVERSING NODE: %d\n",root->data);
	printf("MY CHILDREN ARE: ");
	BinoNode *childItr = root->L;
	while(childItr){
		printf("%d,",childItr->data);
		childItr = childItr->S;
	}
	printf("\n");
	childItr = root->L;
	while(childItr){
		traverse(childItr);
		childItr = childItr->S;
	}
	printf("RETURN\n");
	return;
}
void BinoHeap :: describe(){
	printf("\nDESCRIBE START\n");
	BinoNode *tmp = this->head;
	while(tmp){
		printf("==CURRENT ROOT IS: %d\n",tmp->data);
		traverse(tmp);
		tmp = tmp->S;
	}
	printf("\nDESCRIBE END\n");
	return;
}
int main(){
    BinoHeap hp = BinoHeap();
    for(int i=10000; i>0; i--){
    	hp.insert(i);
    }
    for(int i=0; i<100; i++){
        int n = hp.extractMin();
    	printf("SMALLEST IS: %d\n",n);
    }
	return 0;
}
