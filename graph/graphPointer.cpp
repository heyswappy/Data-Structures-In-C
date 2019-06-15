#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<conio.h>
#define AND &&
#define OR ||
#define NOT !

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
	public:
		Graph();
		int insert_edge(int a, int b, int wt);
		void show();
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

	tree.show();
}
