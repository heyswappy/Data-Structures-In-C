#include<iostream>
#include<cstdlib>

class Node{
private:
	int data;
	Node *L;
	Node *R;
friend class BST;
};

class BST{
private:
	Node *root;
public:
	Node *rotateSingleLeft(Node* root);
	Node *rotateSingleRight(Node* root);
	Node *rotateDoubleLeft(Node* root);
	Node *rotateDoubleRight(Node* root);
};

Node* BST :: rotateSingleLeft(Node *rt){
	Node *ptr = rt->L;
	rt->L = ptr->R;
	ptr->R = rt;
	return ptr; 
}

Node* BST :: rotateSingleRight(Node *rt){
	Node *ptr = rt->R;
	rt->R = ptr->L;
	ptr->L = rt;
	return ptr; 
}

Node* BST :: rotateDoubleLeft(Node *rt){
	rt->R = rotateSingleRight(rt->R)
	return rotateSingleLeft(rt->L); 
}

Node* BST :: rotateDoubleRight(Node *rt){
	rt->L = rotateSingleLeft(rt->L)
	return rotateSingleRight(rt->R); 
}