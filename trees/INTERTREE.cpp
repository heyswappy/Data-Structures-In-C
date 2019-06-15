#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<bits/stdc++.h>

using namespace std;

class InterTree;

class InterNode{
private:
	int data; // same as start i.e the key of node that facilitates search
	int end;
	int maxVal;
	InterNode *L;
	InterNode *R;
	InterNode(int a, int b, int c, InterNode *d, InterNode *e);
	~InterNode();
friend class InterTree;
};

InterNode :: InterNode(int s, int e, int m = -1, InterNode *lChild = NULL, InterNode *rChild = NULL){
	data = s;
	end = e;
	maxVal = m;
	L = lChild;
	R = rChild;
}

InterNode :: ~InterNode(){
	return;
}

class InterTree{
private:
	InterNode *root;
	void levelOrderMain(InterNode *root);
	InterNode *rotateSingleLeft(InterNode *root);
	InterNode *rotateSingleRight(InterNode *root);
	InterNode *rotateDoubleLeft(InterNode *root);
	InterNode *rotateDoubleRight(InterNode *root);
	InterNode *insertNodeMain(InterNode *root, int a, int b);
    void inOrderMain(InterNode *root);
    int updateMaxVal(InterNode *root);
    pair<int,int> queryMain(InterNode *root, int a, int b);
public:
	InterTree();
	void inOrder();
	int height(InterNode *root);
	void insertNode(int a, int b);
	void build();
	void levelOrder();
	pair<int,int> query(int a, int b);
};

InterTree :: InterTree(){
	// normal constructor
	root=NULL;
}
void InterTree :: inOrder(){
    inOrderMain(root);
    return;
}
void InterTree :: inOrderMain(InterNode *root){
	if(root){
		inOrderMain(root->L);
		printf("%d:%d:%d->",root->data,root->end,root->maxVal);
		inOrderMain(root->R);
	}
	return;
}
int InterTree :: height(InterNode *root){
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
InterNode* InterTree :: rotateSingleLeft(InterNode *root){
	InterNode *temp = root->L;
	root->L = temp->R;
	temp->R = root;
	return temp;
}
InterNode* InterTree :: rotateSingleRight(InterNode *root){
	InterNode *temp = root->R;
	root->R = temp->L;
	temp->L = root;
	return temp;
}
InterNode* InterTree :: rotateDoubleLeft(InterNode *root){
	root->L = rotateSingleRight(root->L);
	return rotateSingleLeft(root);
}
InterNode* InterTree :: rotateDoubleRight(InterNode *root){
	root->R = rotateSingleLeft(root->R);
	return rotateSingleRight(root);
}
void InterTree :: insertNode(int s, int e){
	root = insertNodeMain(root, s, e);
	return;
}
InterNode* InterTree :: insertNodeMain(InterNode *root, int s, int e){
	InterNode *temp = NULL;
	if(!root){
		temp = new InterNode(s,e);
		return temp;
	}
	else if(root->data > s){
		root->L = insertNodeMain(root->L, s, e);
		if(height(root->L)-height(root->R)==2){
			// insertion in left subtree hece its height larger
			if(root->L->data > s){
				// insertion in left node left subtree
				root = rotateSingleLeft(root);
			}
			else{
				// insertion in left node left subtree
				root = rotateDoubleLeft(root);
			}
		}
	}
	else if(root->data < s){
		root->R = insertNodeMain(root->R, s, e);
		if(height(root->R)-height(root->L)==2){
			// insertion in right subtree hece its height larger
			if(root->R->data < s){
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
void InterTree :: levelOrder(){
	// levelOrder Traversal
	levelOrderMain(root);
}
void InterTree :: levelOrderMain(InterNode *root){
	if(!root){return;}
	queue<InterNode*> Q;
	Q.push(root);
	InterNode* temp=NULL;
	// print current level
	while(!Q.empty()){
		int i =0;
		int s = Q.size();
		for(i=0;i<s;i++){
			temp = Q.front();
			printf("%d:%d:%d--",temp->data,temp->end,temp->maxVal);
			if(temp->L){Q.push(temp->L);}
			if(temp->R){Q.push(temp->R);}
			Q.pop();
		}
		printf("\n");
	}
	return;
}
int InterTree :: updateMaxVal(InterNode *root){
	if(!root){
		return -1;
	}
	root->maxVal = max(max(updateMaxVal(root->L),updateMaxVal(root->R)),root->end);
	return (root->maxVal);
}
void InterTree :: build(){
	updateMaxVal(root);
	return;
}
pair<int,int> InterTree :: queryMain(InterNode *root,int s, int e){
	if(!root){
        pair<int,int> t(-1,-1);
		return t;
	}
	// BASE CONDITIONS WITH OVERLAP
		// end to end overlap of interval
		if((root->data==s)&&(root->end==e)){
			pair<int,int> t(root->data,root->end);
			return t;
		}
		// start time overlap (partial overlap)
		if((root->data <= s)&&(root->end > s)){
			pair<int,int> t(root->data,root->end);
			return t;
		}
		// end time overlap (partial overlap)
		if((root->end <= e)&&(root->data > e)){
			pair<int,int> t(root->data,root->end);
			return t;
		}
	// NO OVERLAP CONDITIONS
	if(root->L){
		if(root->L->maxVal <= s){
			// greatest interval end time is smaller then the query start time
			// hence no overlap in left subtree
			// so recur to right subtree
			return queryMain(root->R, s, e);
		}
		else{
		// overlap present in
		return queryMain(root->L, s, e);
		}
	}
	// IF LEFT NODE NOT EXISTS RECUR BLINDLY TO RIGHT TREE
	pair<int,int> t = queryMain(root->R, s, e);
	return t;
}
pair<int,int> InterTree :: query(int s, int e){
	pair<int,int> t;
	t = queryMain(root, s, e);
	if(get<0>(t)==-1 && get<1>(t)==-1){
		cout<<"\nFOUND NO CLASH\n";
		return t;
	}
	cout<<"\nCLASHED AT: "<<get<0>(t)<<", "<<get<1>(t)<<"\n";
	return t;
}

int main(){
	// do something
	InterTree t;
	t.insertNode(7,8);
	t.insertNode(6,8);
	t.insertNode(3,8);
	t.insertNode(4,9);
	t.insertNode(2,7);
	t.insertNode(5,6);
	t.insertNode(1,6);
	t.build();
	printf("\n\n");
	t.inOrder();
	printf("\n\n");
	t.levelOrder();
	t.query(10,15);
	return 1;
}
