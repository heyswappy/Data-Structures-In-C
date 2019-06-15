#include<iostream>
#include<cstdlib>

class Node{
private:
	int data;
	int lTag;
	Node *L;
	int rTag;
	Node *R;
	Node(int n){data = n; lTag = rTag = 0; L = R = NUL;}
friend class BST;
};

class BST{
private:
	Node *root;
	Node *temp; // used for traversals to reduce variables
public:
	void insert(int n);
	Node *inOrderSuccessor(Node *ptr);
	void inOrder();
}

void BST :: insert(int n, Node *cur = root, Node *parent){
	if(!cur){
		Node *ptr = Node(n);
		if(parent){
			if(parent->data > n){
				// insertion in left subtree
				cur->L = parent->L;
				cur->R = parent;
			}
			else{
				// insertion in right subtree
				cur->L = parent;
				cur->R = parent->R;
			}
		}
		else{
			cur->L = NULL;
			cur->R = NULL;
		}
		cur->lTag = 0;
		cur->rTag = 0;
		return ptr;
	}
	else if(cur->data > n){
		if(lTag){
			root->L = insert(n,root->L,root);
		}
		else{
			root->L = insert(n,root->L,root);
			root->lTag = 1;
		}
	}
	else if(cur->data < n){
		if(rTag){
			root->R = insert(n,root->R,root);
		}
		else{
			root->R = insert(n,root->R,root);
			root->rTag = 1;
		}
	}
	else{
		// eleemnt already present
	}
	return cur;
}

Node* BST :: inOrderSuccessor(Node *ptr){
	if(ptr->rTag == 0){
		return ptr->R;
	}
	else{
		Node *t = ptr->R;
		while(t->lTag == 1){
			t = t->L;
		}
		return t;
	}
}

void BST :: inOrder(){
	Node *temp;
	while(temp->lTag = 1){
		temp = temp->L;
	}
	while(temp){
		cout<<temp->data;
		temp = inOrderSuccessor(temp);
	}
	return;
}