#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<bits/stdc++.h>
#define RED true
#define BLACK false
#define isDEBUG false

using namespace std;

class RBTree;

class RBNode{
private:
	int data;
	bool C; // true is red color and false is black color
	RBNode *P;
	RBNode *L;
	RBNode *R;
	RBNode(int n);
friend class RBTree;
};
RBNode :: RBNode(int d){
	data = d;
	P=L=R=NULL;
	C = RED;
}

class RBTree{
private:
	RBNode *root;
	void levelOrderMain(RBNode *root);
	RBNode* rotateSingleLeft(RBNode *root);
	RBNode* rotateSingleRight(RBNode *root);
	RBNode* insertNodeBST(RBNode *root, int n);
    void inOrderMain(RBNode *root);
    int grandParent(RBNode *root);
    int bHeight(RBNode *root);
    int doubleRed(RBNode *root);
    RBNode* blackLL(RBNode *root);
    RBNode* blackLR(RBNode *root);
    RBNode* blackRR(RBNode *root);
    RBNode* blackRL(RBNode *root);
    RBNode* balance(RBNode *root);
    RBNode* uncle(RBNode *root);
    RBNode* sibling(RBNode *root);
public:
	RBTree();
	void inOrder();
	int height(RBNode *root);
	void insertNode(int n);
	void levelOrder();
};

RBTree :: RBTree(){
	// deafault constructor
	root=NULL;
}
void RBTree :: inOrder(){
    inOrderMain(root);
    return;
}
void RBTree :: inOrderMain(RBNode *root){
	if(root){
		inOrderMain(root->L);
		printf("%d:%c -",root->data,(root->C?'R':'B'));
		inOrderMain(root->R);
	}
	return;
}
void RBTree :: levelOrder(){
	// levelOrder Traversal
	levelOrderMain(root);
}
void RBTree :: levelOrderMain(RBNode *root){
	if(!root){return;}
	queue<RBNode*> Q;
	Q.push(root);
	RBNode* temp=NULL;
	// print current level
	while(!Q.empty()){
		int i =0;
		int s = Q.size();
		for(i=0;i<s;i++){
			temp = Q.front();
			printf("%d:%c -",temp->data,(temp->C?'R':'B'));
			if(temp->L){Q.push(temp->L);}
			if(temp->R){Q.push(temp->R);}
			Q.pop();
		}
		printf("\n");
	}
	return;
}
int RBTree :: height(RBNode *root){
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
int RBTree :: bHeight(RBNode *root){
	if(!root){
		return -1;
	}
	else if(root->C){
		return 0;
	}
	else{
		// go on
	}
	int l = height(root->L);
	int r = height(root->R);
	if(!root->C){
		return (max(l,r)+1);
	}
	else{
		return max(l,r);
	}
}
int RBTree :: doubleRed(RBNode *root){
	if(isDEBUG){printf("CHECKING FOR NULL PARRENT AND GRANDPARENT\n");}
	if(root){if(root->P){if(root->P->P){//pass
	}else{return 0;}}else{return 0;}}else{return 0;}
	if(isDEBUG){printf("ALL THE NODE PARENT AND GRANDPARENT PRESENT\n");}
	RBNode *ParentL = root->P->L;
	RBNode *ParentR = root->P->R;
	RBNode *GParentL = root->P->P->L;
	RBNode *GParentR = root->P->P->R;
	if(isDEBUG){printf("ASSIGNED CHILDREN\n");}
	if(root->P == GParentL){
		if(isDEBUG){printf("FIRST CHILD LEFT\n");}
		// parent is left child
		if(root == ParentL){
			if(isDEBUG){printf("SECOND CHILD LEFT\n");}
			if((root->C)&&(root->P->C)){
				// LL situation
				if(isDEBUG){printf("LL SITUATION\n");}
				return 1;
			}
		}
		else if(root == ParentR){
			if(isDEBUG){printf("SECOND CHILD RIGHT\n");}
			if((root->C)&&(root->P->C)){
				// LR situation
				if(isDEBUG){printf("LR SITUATION\n");}
				return 2;
			}
		}
	}
	else if(root->P == GParentR){
		if(isDEBUG){printf("FIRST CHILD RIGHT\n");}
		// parent is left child
		if(root == ParentR){
			if(isDEBUG){printf("SECOND CHILD RIGHT\n");}
			if((root->C)&&(root->P->C)){
				// RR situation
				if(isDEBUG){printf("RR SITUATION\n");}
				return 3;
			}
		}
		else if(root == ParentL){
			if(isDEBUG){printf("SECOND CHILD LEFT\n");}
			if((root->C)&&(root->P->C)){
				// RL situation
				if(isDEBUG){printf("RL SITUATION\n");}
				return 4;
			}
		}
	}
	// if no condition passes return 0 i.e no double red condition
	if(isDEBUG){printf("NO DOUBLERED\n");}
	return 0;
}
RBNode* RBTree :: uncle(RBNode *root){
	if(isDEBUG){printf("IN UNCLE\n");}
	if(root){if(root->P){if(isDEBUG){printf("CALLING SIBLING IN UNCLE\n");} return sibling(root->P);}}
	// for exterior node
	if(isDEBUG){printf("EXTERIOR UNCLE\n");}
	return NULL;
}
RBNode* RBTree :: sibling(RBNode *root){
	if(isDEBUG){printf("IN SIBLING\n");}
	if(root){
		RBNode *parent = root->P;
		if(!parent) return NULL;
		if((parent->L)==root){
			if(parent->R){
				if(isDEBUG){printf("RETURNING SIBLING RIGHT\n");}
				return parent->R;
			}
			if(isDEBUG){printf("RETURNING SIBLING NULL\n");}
			return NULL;
		}
		else{
			if(parent->L){
				if(isDEBUG){printf("RETURNING SIBLING LEFT\n");}
				return parent->L;
			}
			if(isDEBUG){printf("RETURNING SIBLING NULL\n");}
			return NULL;
		}
	}
}
RBNode* RBTree :: rotateSingleLeft(RBNode *root){
	if((!root)||(!(root->L))){
		return NULL;
	}
	if(isDEBUG){printf("ROTATE LEFT\n");}
	RBNode *temp = root->L;
	RBNode *parent = root->P;
	if(isDEBUG){printf("SAVE LEFT\n");}
	// update 1
	root->L = temp->R;
	if(temp->R) temp->R->P=root;
	if(isDEBUG){printf("UPDATE 1 DONE\n");}
	// update 2
	temp->R=root;
	temp->P=parent;
	root->P = temp;
	// update 3
	if(parent) parent->R = temp;
	if(isDEBUG){printf("UPDATE 2 DONE RETURNING\n");}
	return temp;
}
RBNode* RBTree :: rotateSingleRight(RBNode *root){
	if((!root)||(!(root->R))){
		return NULL;
	}
	if(isDEBUG){printf("ROTATE RIGHT\n");}
	RBNode *temp = root->R;
	RBNode *parent = root->P;
	if(isDEBUG){printf("SAVE RIGHT\n");}
	// update 1
	root->R = temp->L;
	if(temp->L) temp->L->P=root;
	if(isDEBUG){printf("UPDATE 1 DONE\n");}
	// update 2
	temp->L = root;
	root->P = temp;
	temp->P = parent;
	// update 3
	if(parent) parent->L = temp;
	if(isDEBUG){printf("UPDATE 2 DONE RETURNING\n");}
	return temp;
}
RBNode* RBTree :: blackLL(RBNode *root){
	if(isDEBUG){this->levelOrder(); printf("\n\n\n");}
	// swap parent and grandparent color
	if(isDEBUG){printf("ABOUT TO SWAP COLORS IN LL current is %d \n",root->data);}
	bool temp = root->P->P->C;
	if(isDEBUG){printf("ABOUT TO SWAP COLORS 1/3\n");}
	root->P->P->C = root->P->C;
	if(isDEBUG){printf("ABOUT TO SWAP COLORS 2/3\n");}
	root->P->C = temp;
	if(isDEBUG){this->levelOrder();printf("\n\n\n");}
	// rotate towards right
	if(isDEBUG){printf("COLORS SWAPPED AND ABOUT TO ROTATE\n");}
	RBNode *newRoot = rotateSingleLeft(root->P->P);
	if(isDEBUG){this->levelOrder(); printf("\n\n\n");}
	if(isDEBUG){printf("ROTATION COMPLETE RETURNING FROM LL\n");}
	return newRoot;
}
RBNode* RBTree :: blackLR(RBNode *root){
	// convert to LL case
	if(isDEBUG){printf("CONVERT TO LL FROM LR BY ROTATION current is %d\n",root->data);}
	RBNode *newRoot = rotateSingleRight(root->P);
	if(isDEBUG){printf("ROTATED AND ABOUT TO CALL LL\n");}
	newRoot = blackLL(root->L);
	if(isDEBUG){printf("RETURNING FROM LR\n");}
	return newRoot;
}
RBNode* RBTree :: blackRR(RBNode *root){
	if(isDEBUG){this->levelOrder(); printf("\n\n\n");}
	// swap parent and grandparent color
	if(isDEBUG){printf("ABOUT TO SWAP COLORS IN RR current is %d\n",root->data);}
	bool temp = root->P->P->C;
	root->P->P->C = root->P->C;
	root->P->C = temp;
	if(isDEBUG){this->levelOrder(); printf("\n\n\n");}
	// rotate towards left
	if(isDEBUG){printf("COLORS SWAPPED AND ABOUT TO ROTATE\n");}
	RBNode *newRoot = rotateSingleRight(root->P->P);
	if(isDEBUG){this->levelOrder(); printf("\n\n\n");}
	if(isDEBUG){printf("ROTATION COMPLETE RETURNING FROM RR\n");}
	return newRoot;
}
RBNode* RBTree :: blackRL(RBNode *root){
	// convert to RR case
	if(isDEBUG){printf("CONVERT TO RR FROM RL BY ROTATION current is %d\n",root->data);}
	RBNode *newRoot = rotateSingleLeft(root->P);
	if(isDEBUG){printf("ROTATED AND ABOUT TO CALL RR\n");}
	newRoot = blackRR(root->R);
	if(isDEBUG){printf("RETURNING FROM RL\n");}
	return newRoot;
}
void RBTree :: insertNode(int n){
	if(isDEBUG){printf("INSERTING DATA: %d \n",n);}
	if(!root){
		// empty tree
		root = insertNodeBST(root, n);
		root->C = false;
		return;
	}
	RBNode *ptr = insertNodeBST(root, n);
	if(!ptr){
		return;
	}
	if(isDEBUG){printf("CALLING BALANCE %u\n",ptr);}
	if(isDEBUG){this->levelOrder();}
	ptr = balance(ptr);
	if(isDEBUG){printf("RETURN FROM BALANCE\n");}
	// ptr now has the last node modified
	if(ptr){
		if(!(ptr->P)){
			root = ptr;
			root->C = BLACK;
		}
	}
	return;
}
RBNode* RBTree :: insertNodeBST(RBNode *root, int n){
	RBNode *temp = NULL;
	if(!root){
		// empty tree
		RBNode *ptr = new RBNode(n);
		return ptr;
	}
	if(root->data == n){
		return NULL;
	}
	if(root->data > n){
		if(!(root->L)){
			root->L = new RBNode(n);
			root->L->P = root;
			return root->L;
		}
		return insertNodeBST(root->L,n);
	}
	else{
		if(!(root->R)){
			root->R = new RBNode(n);
			root->R->P = root;
			return root->R;
		}
		return insertNodeBST(root->R,n);
	}
}
RBNode* RBTree :: balance(RBNode *root){
	if(!(root->P)){
		if(isDEBUG){printf("EMPTY TREE\n");}
		root->C = BLACK;
		return root;
	}
	if(isDEBUG){printf("CALLING DOUBLERED\n");}
	int type = doubleRed(root);
	if(isDEBUG){printf("RECEIVED DOUBLERED FOR NODE: %d STATUS: %d\n",root->data,type);}
	RBNode *u = uncle(root);
	if(!u || !(u->C)){
			if(isDEBUG){printf("BLACK OR EXTERIOR UNCLE FOUND\n");}
			switch(type){
			case 1: return blackLL(root);
			break;
			case 2: return blackLR(root);
			break;
			case 3: return blackRR(root);
			break;
			case 4: return blackRL(root);
			break;
			default: break;
		}
		if(isDEBUG){printf("RETURN FROM BLACK EXTERIOR NODE\n");}
		return NULL;
	}
	else{
		// red node make parent and uncle black
		if(isDEBUG){printf("RED UNCLE FOUND\n");}
		root->P->C = BLACK;
		u->C = BLACK;
		if(root->P->P == this->root){
			root->P->P->C = BLACK;
			return NULL;
		}
		if(root->P->P){
			root->P->P->C =RED;
			if(isDEBUG){printf("RECURSING TO BALANCE AGAIN\n");}
			return balance(root->P->P);
			if(isDEBUG){printf("END RECURSION\n");}
		}
	}
	return NULL;
}
int main(){
	// do something
	RBTree t;
	t.insertNode(50);
	t.insertNode(45);
	t.insertNode(12);
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
	t.insertNode(88);
	t.insertNode(1);

	t.inOrder();
	printf("\n\n");
	t.levelOrder();
	return 1;
}
