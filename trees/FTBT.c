#include<stdio.h>
#include<stdlib.h>

/* FULLY THREADED BINARY TREE */

struct node{
	int data;
	int ltag;
	struct node *L;
	int rtag;
	struct node *R;
};

struct node *insertNode(struct node *root, struct node *parent, int n){
	struct node *temp = NULL;
	if(!root){
		temp = (struct node*)malloc(sizeof(struct node));
		temp->data = n;
		if(parent){
			if(parent->data > n){
				//we are currently in left subtree
				temp->L = parent->L ; // predecessor of parent
				temp->R = parent ; // successor is root
			}
			else{
				//we are currently in right subtree
				temp->L = parent ; // predecessor is root
				temp->R = parent->R ; // successor is parent right
			}
		}
		else{
			temp->L = NULL;
			temp->R = NULL;
		}
		temp->ltag = 0;
		temp->rtag = 0;
		return temp;
	}
	else if(root->data > n){
		if(root->ltag){
			root->L = insertNode(root->L,root,n);
		}
		else{
			// no left subtree exists
			root->L = insertNode(NULL,root,n);
			root->ltag = 1;

		}
	}
	else if(root->data < n){
		if(root->rtag){
			root->R = insertNode(root->R,root,n);
		}
		else{
			// no right subtree exists
			root->R = insertNode(NULL,root,n);
			root->rtag = 1;
		}
	}
	else{
		// element already present
	}
	return root;
}

struct node *inOrderSuccessor(struct node *root){
	struct node *temp;
	if(root->rtag == 0){
		// no right subtree
		return root->R;
	}
	else{
		temp = root->R;
		while(temp->ltag){
			// while left subtree exists
			temp = temp->L;
		}
		return temp;
	}
}

void inOrder(struct node *root){
	struct node *temp = root;
	while(temp->L!=NULL){
		// to find leftmost node
		temp = temp->L;
	}
	while(temp){
		printf("%d->",temp->data);
		temp = inOrderSuccessor(temp);

	}
}

void main()
{
	struct node *root = NULL;
	root = insertNode(root,NULL,3);
	root = insertNode(root,NULL,5);
	root = insertNode(root,NULL,7);
	root = insertNode(root,NULL,2);
	inOrder(root);
}
