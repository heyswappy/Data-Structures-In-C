#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<bits/stdc++.h>

using namespace std;

class AVLTree;
class AVLNode{
private:
	int data;
	AVLNode *L;
	AVLNode *R;
	AVLNode(int n){data=n;L=R=NULL;}
friend class AVLTree;
};

class AVLTree{
private:
	AVLNode *root;
	void levelOrderMain(AVLNode *root);
	AVLNode *rotateSingleLeft(AVLNode *root);
	AVLNode *rotateSingleRight(AVLNode *root);
	AVLNode *rotateDoubleLeft(AVLNode *root);
	AVLNode *rotateDoubleRight(AVLNode *root);
	AVLNode *insertNodeMain(AVLNode *root, int n);
    void inOrderMain(AVLNode *root);
public:
	AVLTree();
	void inOrder();
	int height(AVLNode *root);
	void insertNode(int n);
	void levelOrder();
};

AVLTree :: AVLTree(){root=NULL;}

void AVLTree :: inOrder(){
    inOrderMain(root);
    return;
}

void AVLTree :: inOrderMain(AVLNode *root){
	if(root){
		inOrderMain(root->L);
		printf("%d->",root->data);
		inOrderMain(root->R);
	}
	return;
}
int AVLTree :: height(AVLNode *root){
	if(!root){
		return -1;
	}
	int l = height(root->L);
	int r = height(root->R);
	if(l>r){
		return l+1;
	}
	else{
		return r+1;
	}
}
AVLNode* AVLTree :: rotateSingleLeft(AVLNode *root){
	AVLNode *temp = root->L;
	root->L = temp->R;
	temp->R = root;
	return temp;
}
AVLNode* AVLTree :: rotateSingleRight(AVLNode *root){
	AVLNode *temp = root->R;
	root->R = temp->L;
	temp->L = root;
	return temp;
}
AVLNode* AVLTree :: rotateDoubleLeft(AVLNode *root){
	root->L = rotateSingleRight(root->L);
	return rotateSingleLeft(root);
}
AVLNode* AVLTree :: rotateDoubleRight(AVLNode *root){
	root->R = rotateSingleLeft(root->R);
	return rotateSingleRight(root);
}
void AVLTree :: insertNode(int n){
	root = insertNodeMain(root, n);
	return;
}
AVLNode* AVLTree :: insertNodeMain(AVLNode *root, int n){
	AVLNode *temp = NULL;
	if(!root){
		temp = new AVLNode(n);
		return temp;
	}
	else if(root->data > n){
		root->L = insertNodeMain(root->L, n);
		if(height(root->L)-height(root->R)==2){
			// insertion in left subtree hece its height larger
			if(root->L->data > n){
				// insertion in left node left subtree
				root = rotateSingleLeft(root);
			}
			else{
				// insertion in left node left subtree
				root = rotateDoubleLeft(root);
			}
		}
	}
	else if(root->data < n){
		root->R = insertNodeMain(root->R, n);
		if(height(root->R)-height(root->L)==2){
			// insertion in right subtree hece its height larger
			if(root->R->data < n){
				//insertion in right node right subtree
				root = rotateSingleRight(root);
			}
			else{
				// insertion in right node right subtree
				root = rotateDoubleRight(root);
			}
		}
	}
	else{
		// element already exists
	}
	return root;
}
void AVLTree :: levelOrder(){
	// levelOrder Traversal
	levelOrderMain(root);
}
void AVLTree :: levelOrderMain(AVLNode *root){
	if(!root){return;}
	queue<AVLNode*> Q;
	Q.push(root);
	AVLNode* temp=NULL;
	// print current level
	while(!Q.empty()){
		int i =0;
		int s = Q.size();
		for(i=0;i<s;i++){
			temp = Q.front();
			printf("%d-",temp->data);
			if(temp->L){Q.push(temp->L);}
			if(temp->R){Q.push(temp->R);}
			Q.pop();
		}
		printf("\n");
	}
	return;
}

int main(){
	// do something
	AVLTree t;
	t.insertNode(50);
	t.insertNode(12);
	t.insertNode(45);
	t.insertNode(99);
	t.insertNode(44);
	t.insertNode(48);
	t.insertNode(9);
	t.insertNode(10);
	t.insertNode(86);
	t.insertNode(102);
	t.insertNode(16);
	t.insertNode(28);
	t.insertNode(55);
	//t.insertNode(103);
	t.insertNode(88);
	t.insertNode(1);

	t.inOrder();
	printf("\n\n");
	t.levelOrder();
	return 1;
}
