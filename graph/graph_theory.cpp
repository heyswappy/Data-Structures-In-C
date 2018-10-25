#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<conio.h>
#define AND &&
#define OR ||
#define NOT !
////////////////////////////////////STACK/////////////////////////////////////////////////////
class Stack
{
	private:
		int top;
		int *arr;
	public:
		int len(){ return(top+1); }
		int get(int a){ return(arr[a]); }
		void push(int a){top++; arr[top]=a;}
		void show(){for(int i=0; i<(top+1);i++){printf("->%d",arr[i]);}}
		int pop(){arr[top]=0; top--; return(arr[top+1]);}
		int srch(int a){for(int i=0; i<(top+1);i++){if(arr[i] == a){return 1;}}return 0;}
		void reset(){top = (-1);}
		Stack( int a = 128 ){arr = (int*)calloc(sizeof(int),a) ; top = (-1) ;}
		Stack(Stack &ptr){ this->reset(); for(int i = 0; i<ptr.len(); i++){ this->push(ptr.get(i)); } return;}
}current,shortest;
/////////////////////////////////QUEUE///////////////////////////////////////////////////////
class Queue
{
	private:
		int head;
		int back;
		int *arr;
		int size;
	public:
		int len(){ return (abs(head-back)); }
		void push(int a){ back = ((back+1)%size); arr[back] = a;}
		int get(int a){return arr[a];}
		int pop(){ int r = arr[head]; head = ((head+1)%size); return r;}
		int srch(int a){for(int i=head, j=0; j<(len());i=((i+1)%size)){if(arr[i] == a){return 1;}}return 0;}
		int show(){for(int i=head, j=0; j<(len());i=((i+1)%size)){printf("->%d",arr[i]);}return 0;}
		void reset(){head = 0;back = 0;}
		Queue(int n = 128 ){arr = (int*)calloc(sizeof(int),n); size = n; head = 0; back = 0;}
}to_visit,visited;
//////////////////////////////PRIORITY QUEUE/////////////////////////////////////////////////
class Pri_Q
{
	private:
		int front; // points to first element
		int back; // points to that cell which would be filled next
		int *pri; // main arr pointer denoting priority
		int *dat; // arr containing info
		int *sub; // arr containing sub data
		int size; // full capacity
		int len; // current lenght
	public:
		Pri_Q( int a = 128 );
		~Pri_Q();
		void show();
		int q_len();
		bool is_full();
		void right_shift(int a);
		void sorted_insert(int a, int b, int c);
		void enqueue(int a, int b=0, int c=0);
		int *get_min();
		int *ret_min();
		int *get_max();
		void update_pri(int p, int d=0, int s=0);
		bool does_exist(int d, int s);
};
Pri_Q :: Pri_Q ( int a )
{
	this->front = 0;
	this->back = 0;
	this->size = a+1;
	this->len = 0;
	this->pri = (int *)calloc(sizeof(int),(a+1));
	this->dat = (int *)calloc(sizeof(int),(a+1));
	this->sub = (int *)calloc(sizeof(int),(a+1));
	if((!pri)||(!dat)||(!sub))
	{
		printf("MEMORY ERROR\n");
		getch();
	}
	return;
}
Pri_Q :: ~Pri_Q()
{
	free(pri);
	free(dat);
	free(sub);
	return;
}
void Pri_Q :: show()
{
	printf("PRIORITY<-");
	for(int i =(this->front),count = 0;(count)<(this->len);count++,i=(i+1)%(this->size))
	{
		printf("%d<-",this->pri[i]);
	}
	printf("\nMAINDATA<-");
	for(int i =(this->front),count = 0;(count)<(this->len);count++,i=(i+1)%(this->size))
	{
		printf("%d<-",this->dat[i]);
	}
	printf("\nSUB-DATA<-");
	for(int i =(this->front),count = 0;(count)<(this->len);count++,i=(i+1)%(this->size))
	{
		printf("%d<-",this->sub[i]);
	}
	printf("\n");
	return;
}
int Pri_Q :: q_len()
{
	// returns lenght
	return(this->len);
}
bool Pri_Q :: is_full()
{
	if((this->len)==((this->size)-1))
	{
		return true;
	}
	return false;
}
void Pri_Q :: right_shift(int index)
{
	//make space at index
	int last = ((this->back)+1)%(this->size);

	int c = 0; //current
	int d = 0; // analogue of c for dat array
	int e = 0; // analogue of c for subdata array
	int n = (this->pri)[index]; //next
	int m = (this->dat)[index]; //analogue of n for dat array
	int o = (this->sub)[index]; //analogue of n for sub array
	for(int i=index ; i!=last;)
	{
		c = n;
		d = m;
		e = o;
		i = ((i+1)%(this->size));
		n = (this->pri)[i];
		m = (this->dat)[i];
		o = (this->sub)[i];
		(this->pri)[i] = c;
		(this->dat)[i] = d;
		(this->sub)[i] = e;
	}
	return;
}
void Pri_Q :: sorted_insert(int p, int d, int s)
{
	// front of the queue has the largest element and back has the smallest element
	// assume that the queue is sorted

	// empty queue
	//printf(" IN SORTED INSERT\n");
	if((this->len)==0)
	{
		(this->pri)[this->back] = p;
		(this->dat)[this->back] = d;
		(this->sub)[this->back] = s;
		this->back = (((this->back)+1))%(this->size) ;
		(this->len)++;
		return;
	}

	// insert in middle
	for(int i = this->front; i<(this->q_len()); )
	{
		if(pri[i]==-1)
		{
			// skip deleted element
			i=((i+1)%(this->size));
			continue;
		}
		if(pri[i]<=p)
		{
			right_shift(i);
			(this->pri)[i]=p;
			(this->dat)[i]=d;
			(this->sub)[i]=s;
			(this->len)++;
			this->back = (((this->back)+1))%(this->size) ;
			return;
		}
		i=((i+1)%(this->size));
	}

	// insert at end
	this->pri[this->back] = p;
	this->dat[this->back] = d;
	this->sub[this->back] = s;
	this->back = (((this->back)+1))%(this->size) ;
	(this->len)++;
	return;
}
void Pri_Q :: enqueue(int p, int d, int s)
{
	// call sorted insert
	if(this->is_full())
	{
		return;
	}
	sorted_insert(p,d,s);
}
int *Pri_Q :: get_min()
{
	int *r = (int*)calloc(sizeof(int),2);
	int last = this->back;
	get_again:
	if(q_len()==0)
	{
		return NULL;
	}
	if(last==0)
	{
		last = (this->size)-1;
	}
	else
	{
		last = last-1;
	}
	(this->back)--;
	if((this->back)<0)
	{
		this->back = (this->size)-1 ;
	}
	(this->len)--;
	if((this->dat)[last]==-1)
	{
		// deleted element
		goto get_again;
	}
	r[0] = (this->dat)[last];
	r[1] = (this->sub)[last];
	return r;
}
int *Pri_Q :: ret_min()
{
	int last = (this->back);
	get_again:
	// return minimum but dont delete it
	//printf("IN TAG OF WAR\n");
	if(q_len()==0)
	{
		return NULL;
	}
	if(last==0)
	{
		last = (this->size)-1;
	}
	else
	{
		last = last-1;
	}
	if((this->pri)[last]==-1)
	{
		// deleted element
		goto get_again;
	}
	int *r = (int*)calloc(sizeof(int),2);
	r[0] = (this->dat)[last];
	r[1] = (this->sub)[last];
	return r;
}
int *Pri_Q :: get_max()
{
	get_again:
	if(q_len()==0)
	{
		return NULL;
	}
	int first = this->front;
	int *r = (int*)calloc(sizeof(int),2);
	r[0] = (this->dat)[first];
	r[1] = (this->sub)[first];
	(this->front)=((this->front)+1)%(this->size);
	(this->len)--;
	if((this->pri)[first]==-1)
	{
		// deleted element
		goto get_again;
	}
	return r;
}
void Pri_Q :: update_pri(int p, int d, int s)
{
	// updates the priority of data d to p
	for(int i = front;i!=back; i=(i+1)%(size))
	{
		if(dat[i]==d)
		{
			pri[i] = -1;
			enqueue(p,d, s);
			return;
		}
	}
}
bool Pri_Q :: does_exist(int d, int s)
{
	for(int i = front; i!=back; i = (i+1)%(size))
	{
		//printf("%d %d\n",dat[i],sub[i]);
		if((dat[i]==d)&&(sub[i]==s))
		{
			return true;
		}
	}
	return false;
}
/////////////////////////////////////GRAPH////////////////////////////////////////////////////////
struct vertex;
struct nbr_node
{
	int id; // extra information so that readily accesible
	int wt; // weight of  the edge
	struct vertex *node; // structure pointer to actual node
	struct nbr_node *next; // pointer to next nbr of main node of which this is a neighbour too
};
struct vertex
{
	int id; // id of a node
	int nbr; // number of neighbours
	int visit; // visited
	struct vertex *parent; // shortest distance to this node is through parent node
	int dist; // distance from source
	int shortest_edge;
	struct nbr_node *nbr_id; // link list of neighbours
	struct vertex *next; // link list of main nodes
};
class Graph
{
	private:
		vertex *head;
		vertex *last;
		int length;
		// functions
		vertex *srch_vertex(int a);
		vertex *insert_vertex(int a);
		int add_nbr(struct vertex *a, struct vertex *b, int wt);
		void update_nodes(struct vertex *ptr, Pri_Q *a);
		void prim_update(struct vertex *ptr, Pri_Q *PQ);
	public:
		Graph();
		int insert_edge(int a, int b, int wt);
		void show();
		int len(){ return length; }
		int dfs(int a, int b);
		int bfs(int a, int b){to_visit.push(a);int i = bfs_level(a,b);dk_path(a,b); return i;}
		int bfs_level(int a, int b);
		void update_nodes(struct vertex &a, Pri_Q b);
		void djikstra(int a, int b);
		void dk_path(int a, int b);
		Graph prim();
		Graph kruskal();
};
Graph :: Graph()
{
	head = (struct vertex*)calloc(sizeof(struct vertex),1); // dummy  vertex
	last = head;
	length = 0;
}
vertex *Graph :: srch_vertex(int a)
{
	vertex *ptr = head->next;
	while(ptr != NULL)
	{
		if(ptr->id == a)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}
vertex *Graph :: insert_vertex(int a)
{
	// returns the node address either if it is created or it exists
	vertex *s = srch_vertex(a);
	if (s == NULL)
	{
		last->next = (struct vertex*)malloc(sizeof(struct vertex));
		vertex *ptr = last->next;
		last = ptr;
		ptr->id = a;
		ptr->nbr = 0;
		ptr->parent = NULL;
		ptr->next = NULL;
		ptr->dist = -1;
		ptr->visit = 0;
		ptr->shortest_edge = -1;
		length++;
		// initialise neighbour list dummy node
		ptr->nbr_id = (struct nbr_node*)malloc(sizeof(struct nbr_node));
		ptr->nbr_id->id = -1;
		ptr->nbr_id->wt = -1;
		ptr->nbr_id->node = NULL;
		ptr->nbr_id->next = NULL;
		return ptr;
	}
	else
	{
		return s; // node already exists
	}
}
int Graph :: add_nbr(struct vertex *a, struct vertex *b, int wt)
{
	struct nbr_node *ver_a = a->nbr_id;
	struct nbr_node *ver_b = b->nbr_id;
	struct nbr_node *ptr;
	int flag_a = 0; // flag if neighbour already exists
	int flag_b = 0; // flag if neighbour already exists

	while(((ver_a)!=NULL)&&((ver_a->next)!=NULL))
	{
		// the loop progresses if current and next node are both not null
		if(ver_a->id==b->id)
		{
			flag_a = 1;
			break;
		}
		ver_a = ver_a->next;

	}
	if(ver_a->id==b->id)
	{
		// check last node
		flag_a = 1;
	}
	if(flag_a == 0)
	{
		// add neighbour to a
		ver_a->next = (struct nbr_node*)malloc(sizeof(struct nbr_node));
		ver_a = ver_a->next;
		ver_a->id = b->id;
		ver_a->wt = wt;
		ver_a->node = b;
		ver_a->next = NULL;
	}
	while(((ver_b)!=NULL)&&((ver_b->next)!=NULL))
	{
		// the loop progresses if current and next node are both not null
		if(ver_b->id==a->id)
		{
			flag_b = 1;
			break;
		}
		ver_b = ver_b->next;

	}
	if(ver_b->id==a->id)
	{
		// check last node
		flag_b = 1;
	}
	if(flag_b == 0)
	{
		// add neighbour to b
		ver_b->next = (struct nbr_node*)malloc(sizeof(struct nbr_node));
		ver_b = ver_b->next;
		ver_b->id = a->id;
		ver_b->wt = wt;
		ver_b->node = a;
		ver_b->next = NULL;
	}
	if((flag_a == 1)&&(flag_b == 1))
	{
		// already neighbours
		return 0;
	}
	return 1;
}
int Graph :: insert_edge(int a, int b, int wt = 1)
{
	vertex *vertex_s = insert_vertex(a);
    vertex *vertex_e = insert_vertex(b);
	// increase neighbours
	vertex_s->nbr++;
	vertex_e->nbr++;
	//assign neighbours
	// returns 1 if nbr added 0 if already nbrs
	return(add_nbr(vertex_s,vertex_e,wt));
}
void Graph :: show()
{
	vertex *ptr = head->next;
	nbr_node *x = NULL;
	while(ptr != NULL)
	{
		printf("\n-> ID : %d\nNEIGHBOURS :-\n",ptr->id);
		for(x = ptr->nbr_id ; x!=NULL ; x = x->next)
		{
			printf("ID : %d, WT : %d\n",x->id,x->wt);
		}
		//printf("\n");
		printf("\n\n");
		ptr = ptr->next;
	}
	printf("\n");
	return;
}
void Graph :: dk_path(int a, int b)
{
	struct vertex *g = srch_vertex(b);
	if(a==b)
	{
		return;
	}
	dk_path(a,srch_vertex(b)->parent->id);
	printf("->%d",g->id);
	return;
}
void Graph :: update_nodes(struct vertex *ptr, Pri_Q *PQ)
{
	struct nbr_node *nbr = ptr->nbr_id->next;
	//printf("UPDATING FOR :%d %d\n",ptr->id,nbr->id);
	while(nbr)
	{
		if(nbr->node->dist==-1)
		{
			// first occurence of the node i.e. node unvisited
			nbr->node->dist = (ptr->dist)+(nbr->wt);
			nbr->node->parent = ptr;
			PQ->enqueue(((ptr->dist)+(nbr->wt)),nbr->id);
		}
		else if((nbr->node->dist) > (ptr->dist)+(nbr->wt))
		{
			// new distance is shorter than older one
			// update parent and distance
			nbr->node->dist = (ptr->dist)+(nbr->wt);
			nbr->node->parent = ptr;
			PQ->enqueue(((ptr->dist)+(nbr->wt)),nbr->id);

		}
		else
		{
			// nothing
			// don't enqueue
		}
		nbr = nbr->next;
	}
	return;
}
void Graph :: djikstra(int a, int b)
{
	Pri_Q PQ = Pri_Q(128);
	PQ.enqueue(0,a);
	struct vertex *src  = srch_vertex(a);
	src->dist = 0;
	struct vertex *current = NULL;
	struct nbr_node *nbr = NULL;

	while(!PQ.is_full())
	{
		int *q = PQ.get_min();
		int n = q[0];
		free(q);
		current = srch_vertex(n);
		if(n==-1)
		{
			return;
		}
		update_nodes(current,&PQ);
		if(n == b)
		{
			return;
		}
	}
}
int Graph :: dfs(int a, int b)
{
	vertex *temp = srch_vertex(a);
	int ans = 0;
	if( (shortest.len()<current.len()) AND (shortest.len() != -1) AND (current.srch(a)) )
	{
		// first condition means that we already have shortest path so current distance is greater than earlier hence no use
		// second condition means that shortest has a valid path
		// third condition tells if the node is visited
		current.pop();
		return 0;
	}

	if(a==b)
	{
		//SHORTEST PATH FOUND
		current.push(a);
		if(((shortest.len()) > (current.len())) OR (shortest.len() == 0))
		{
			// first condition checks that new path is shorter then older one
			// swcond condition checks that shortest stack is not empty
			shortest = current;
		}
		current.pop();
		return 1;

	}
	else
	{
		current.push(a);
		struct nbr_node *nbr = temp->nbr_id->next;
		while(nbr)
		{
			if(!current.srch(nbr->id))
			{
				// conditios means if node is not visited
				ans = dfs(nbr->id,b);
				// after visiting node
				continue;
			}
			else
			{
				//if node is visted
				continue;
			}
			current.pop();
			nbr= nbr->next;
		}
		// when all neighbours traversed
		current.pop();
	}
	return ans;
}
int Graph :: bfs_level(int a, int b)
{
	if(a==b)
	{
		vertex *address = srch_vertex(b);
		address->parent = srch_vertex(a);
		return 1;
	}

	int s = 0;
	int f = 0;
	visited.push(a);
	while(true)
	{
		f++;
		int y = to_visit.pop();
		vertex *temp = srch_vertex(y);
		struct nbr_node *nbr = temp->nbr_id->next;
		while(nbr)
		{
			s =  nbr->id ;
			if(s==b)
			{
				vertex *address = srch_vertex(s);
				address->parent = temp;
				return 1;
			}
			if ((!visited.srch(s)) AND (!to_visit.srch(s)))
			{
				struct vertex *address = srch_vertex(s);
				address->parent = temp;
				to_visit.push(s);
				visited.push(s);
			}
			else
			{
				continue;
			}
		}
		if(f>length)
		{
			return 0;
		}
	}
}
void Graph :: prim_update(struct vertex *ptr, Pri_Q *PQ)
{
	struct nbr_node *nbr = ptr->nbr_id->next;
	//printf("VERTEX : %d PTR : %d\n",ptr->id,nbr);
	while(nbr)
	{
		//printf("NEIGHBOUR IS : %d WITH WT : %d\n",nbr->id,nbr->wt);
		if (nbr->node->shortest_edge == -1)
		{
			// condition no shortest edge initialised
			nbr->node->shortest_edge = nbr->wt;
			nbr->node->parent = ptr;
			//printf("INSERTING WITH PRIORITY OF NODE : %d WITH PRIORITY : %d\n",nbr->id,nbr->wt);
			PQ->enqueue(nbr->wt,nbr->id);
		}
		else if ((nbr->node->shortest_edge)>(nbr->wt))
		{
			// update priority of a node if it is unvisited
			nbr->node->shortest_edge = nbr->wt;
			nbr->node->parent = ptr;
			//printf("UPDATING PRIORITY OF NODE : %d WITH PRIORITY : %d\n",nbr->id,nbr->wt);
			PQ->update_pri(nbr->wt,nbr->id);
		}
		else
		{
			//printf("YOU ARE VISITED %d %d %d\n",nbr,nbr->id,PQ->q_len());
			// nothing
			// don't enqueue
		}
		nbr = nbr->next;
	}
	return;
}
Graph Graph :: prim()
{
	// new graph to store minimum spanning tree
	Graph tree;
	if(this->head->next==NULL)
	{
		// if current graph is empty
		return tree;
	}
	struct vertex *current = this->head->next;
	struct nbr_node *nbr = NULL;
	current->dist = 0;
	// priority queue
	Pri_Q PQ = Pri_Q(128);
	PQ.enqueue(0,current->id);
	int n_edges = (this->length)-1;
	int counter = 0;


	while(!PQ.is_full())
	{
		// visit a vertex
		int *q = PQ.get_min();
		int n = q[0];
		free(q);
		current = srch_vertex(n);

		// mark it as visited
		current->visit = 1;

		// set the parent of nbrs as current node if parent less else update parent with minimum weight
		//printf("VERTEX SELECTED : %d\n",n);
		prim_update(current,&PQ);
		//printf("EXITED UPDATE FUNCTION\n");

		if(n==-1)
		{
			//printf("\n RETURN -1\n");
			return tree;
		}
		if(counter==n_edges)
		{
			return tree;
		}
		//printf("INSERTING BETWEEN %d %d\n",PQ.ret_min(),srch_vertex(PQ.ret_min())->parent->id);
		int *qs = PQ.ret_min();
		int k = q[0];
		free(qs);
		if(tree.insert_edge(k,srch_vertex(k)->parent->id))
		{
			//printf("ADDED\n");
			counter++;
		}

	}
	return tree;
}
Graph Graph :: kruskal()
{
	Graph tree;
	Pri_Q edges;
	int n_edges = length-1;
	struct vertex *v = head->next;
	int a = 0;
	int b = 0;
	if(!v)
	{
		return tree;
	}
	while(v)
	{
		struct nbr_node *nbr = v->nbr_id->next;
		while(nbr)
		{
			a = v->id;
			b = nbr->id;
			if(a>b)
			{
				a = a^b; b = b^a; a = a^b;
			}
			// assumed that b >= a for sure
			if(!edges.does_exist(a,b))
			{
				edges.enqueue(nbr->wt,a,b);
				edges.show();
			}
			else
			{
				//printf("I DO HAVE DUPLICATES\n");
			}
			nbr = nbr->next;
		}
		v = v->next;
	}
	edges.show();
	getch();
	int *n;
	while(n_edges)
	{
		n = edges.get_min();
		if(!n)
		{
			printf("NULL len = %d\n",edges.q_len());
			getch();
			return tree;
		}
		struct vertex *a =srch_vertex(n[0]);
		struct vertex *b =srch_vertex(n[1]);
		if((!a)||(!b))
		{
			printf("WAIT WHAT\n");
			getch();
		}
		int o = tree.dfs(a->id,b->id);
		if(o)
		{
			printf("%d\n",n);
			printf("%d %d\n",n[0],n[1]);
			edges.show();
			tree.insert_edge(n[0],n[1]);
			a->visit=1;
			b->visit=1;
			n_edges--;
		}
	}
	return tree;
}
//////////////////////////////////MAIN/////////////////////////////////////////////////////////
int main()
{
	Graph map;
	////////////////////////////////// MAP NUMBER 1 //////////////////////////////////////
	/*map.insert_edge(1,2,14);
	map.insert_edge(1,4,20);
	map.insert_edge(1,5,25);
	map.insert_edge(1,6,5);
	map.insert_edge(2,3,2);
	map.insert_edge(2,4,8);
	map.insert_edge(2,5,1);
	map.insert_edge(3,7,4);
	map.insert_edge(5,6,15);
	map.insert_edge(5,7,10);
	map.insert_edge(6,7,3);*/
	////////////////////////////////// MAP NUMBER 2 //////////////////////////////////////
	map.insert_edge(0,1,4);
	map.insert_edge(0,7,8);
	map.insert_edge(1,7,11);
	map.insert_edge(1,2,8);
	map.insert_edge(2,3,7);
	map.insert_edge(2,5,4);
	map.insert_edge(2,8,2);
	map.insert_edge(3,4,9);
	map.insert_edge(3,5,14);
	map.insert_edge(4,5,10);
	map.insert_edge(5,6,2);
	map.insert_edge(6,7,1);
	map.insert_edge(6,8,6);
	map.insert_edge(7,8,7);

	/*printf("CALLED DJIKSTRA\n");
	map.djikstra(1,5);
	map.show();
	printf("DJIKSTRA IS CALLED\n");
	map.dk_path(1,5);
	printf("DONE\n");*/
	/*map.show();
	getch();*/
	Graph tree = map.kruskal();
	tree.show();
}
