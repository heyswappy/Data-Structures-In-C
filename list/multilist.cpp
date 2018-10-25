#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

class Node{
private:
	friend class Category;
	friend class MultiList;
	string data;
	Node *next;
	Node(string a){data = a; next = NULL;};
};

class Category{
private:
	friend class MultiList;
	string data;
	Node *next;
	Category *down;
	Category(string a){data = a; down = NULL; next = NULL;}
	void addItem(string a);
	void delItem(string a);
	void display();
	~Category(){Node *t = next;while(t!=NULL){t=next;next = next->next;delete t;}};
};
void Category :: addItem(string a){
	Node *t = next;
	if(!next){
		next = new Node(a);
		return;
	}
	while(t->next){
		if(t->data == a){
			cout<<"ITEM EXITS";
			return;
		}
		t=t->next;
	}
	t->next = new Node(a);
	return;
}
void Category :: delItem(string a){
	Node *t;
	for(t=next;t!=NULL;t=t->next){
		if(t->next->data==a){
			Node *s = t->next;
			t->next = t->next->next;
			delete s;
			return;
		}
	}
	cout<<"ITEM NOT FOUND";
	return;
}
void Category :: display(){
	Node *t = next;
	cout<<data;
	while(t){
		cout<<"->"<<(t->data);
		t = t->next;
	}
	cout<<"\n|\nv\n";
	return;
}

class MultiList{
public:
	Category *head;
	MultiList(){head=NULL;}
	void addItem(string cat, string item);
	void delItem(string cat, string item);
	void addCat(string a);
	void delCat(string a);
	void display();

};
void MultiList :: addCat(string a){
	//cout<<a;
    Category *ptr = head;
	if(!ptr){
		head = new Category(a);
		//cout<<(head->data);
		return;
	}
	while((ptr->down)!=NULL){
		if (ptr->data == a){
			cout<<"\nALREADY EXISTS";
			return;
		}
	}
	ptr->down = new Category(a);
	//cout<<(ptr->down->data);
	return;
}
void MultiList :: delCat(string a){
	if(!head){
		cout<<"EMPTY";
		return;
	}
	Category *ptr = head;
	if (ptr->data == a){
		Category *t = ptr->down;
		delete head;
		head = t;
		return;
	}
	while((ptr->down)!=NULL){
		if (ptr->down->data == a){
			Category *t = ptr->down;
			ptr->next = ptr->next->next;
			delete t;
			return;
		}
	}
	cout<<"NOT FOUND";
	return;
}
void MultiList :: addItem(string cat, string item){
	Category *t = NULL;
	for(t=head;t!=NULL;t=t->down){
		if((t->data)==cat){
			t->addItem(item);
			return;
		}
	}
	cout<<"CATEGORY NOT FOUND";
	return;
}
void MultiList :: delItem(string cat, string item){
	Category *t = NULL;
	for(t=head;t!=NULL;t=t->down){
		if((t->data)==cat){
			t->delItem(item);
			return;
		}
	}
	cout<<"CATEGORY NOT FOUND";
	return;
}
void MultiList :: display(){
	Category *t = head;
	while(t){
		t->display();
		t=t->down;
	}
	return;
}

int main(){
	MultiList sport;
	sport.addCat(string("cricket"));
	sport.addCat(string("football"));
	sport.addItem(string("cricket"),string("bat"));
	sport.addItem(string("cricket"),string("ball"));
	sport.addItem(string("cricket"),string("wicket"));
	sport.addItem(string("football"),string("ball"));
	sport.addItem(string("football"),string("gloves"));
	sport.addItem(string("football"),string("studs"));
	sport.display();
}
