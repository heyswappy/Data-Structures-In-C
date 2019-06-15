#include<iostream>
#include<cstdlib>

class Node{
public:
	int *data;
	Node **child;
	int keys;
	int leaf;

	/* FUNCTIONS */

}

class Btree{
public:
	Node *root;
	int degree;
}

void Node :: Node(int degree){
	data = (int*)calloc(sizeof(int),(degree/2)-1);
	child = (Node**)calloc(sizeof(Node*),(degree/2));
	keys = 0;
	leaf = 1;
}

void Node :: insertKeyNode(int n, Node *L = NULL, Node *R = NULL){
	//insert a key in hte node being called
	if(L){
		child[keys] = L;
	}
	data[keys++] = n;
	child[keys] = R;
	return;
}

void Node ::  splitChild(int k, int n){
		// k is the kth child and n is the degree
		// assume that ith child of parent is full and split it

		// find median element
		int mid = (n-1)/2;
		Node *child = child[k-1];

		// handle elements to the left and right for that first make two new nodes
		Node *newL = Node(n);
		Node *newR = Node(n);

		// copy left side data to newL
		for(int i=0; i<mid; i++){
			newL->child[newL->key] = child->child[i]; // copy pointer data
			newL->data[(newL->key)++] = child->data[i]; // copy integer data
		}
		// copy last pointer
		newL->child[key+1] = child->child[mid];

		// copy right side data to newR
		for(int i=mid+1; i<(n-1); i++){
			newR->child[newR->key] = child->child[i]; // copy pointer data
			newR->data[(newR->key)++] = child->data[i]; // copy integer data
		}
		// copy last pointer
		newR->child[key+1] = child->child[n-1];

		// now copy the mid element to parent with correct pointers
		this->insertKeyNode(child,newL,newR);
		return;
}

Node *Node :: insertKey(Node *root, int degree, int data, int flag){
	// if flag = 1 then its the root
	Node *temp = NULL;
	if(flag && root->keys == degree-1){
		// if root (main) is full
		temp = new Node();
		temp->child[0] = root;
		temp.splitChild(1,degree);
		insertKey(temp, degree, data, 1);
		root = temp;
	}
	temp = root;
	while(temp->leaf!=1){
		int i = 0
		for(i=0; i<keys; i++){
			if(n < data[i]){
				break;
			}
		}
		if(i==keys){
			// loop run full hence pointer index is keys+1
			i = keys;
		}
		// i now has the index of next sub tree where node is to be inserted
		if(temp->child[i]->keys == degree-1){
			temp->splitChild(i,degree);
		}
		temp = temp->child[i];
	}
	// if leaf node has empty position
	temp->insertKeyNode(data);
	return root;
}