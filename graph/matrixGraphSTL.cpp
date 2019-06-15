#include<iostream>
#include<cstdlib>
#include<stack>
#include<vector>
#include<queue>
#include<algorithm>
#include<tuple>
#include<utility>
#include<conio.h>

using namespace std;

class PairCompare{
public:
	bool operator () (pair <int,int> a, pair <int,int> b){
		if( get<1>(a) > get<1>(b)){
			return true;
		}
		return false;
	}
};

class TupleCompare{
public:
	bool operator () (tuple <int,int,int> a, tuple <int,int,int> b){
		if( get<2>(a) > get<2>(b)){
			return true;
		}
		return false;
	}
};

class MatrixGraph{
private:
	queue <int> qu;
    stack <int> st;
    vector <int> vt;
    vector <int> path;
public:
	int node;
	int **matrix;
	MatrixGraph(int n);
	bool dfsSearch(int src, int dest);
	bool bfsSearch(int src, int dest);
	int djikstra(int src, int dest);
	MatrixGraph kruskal();
	MatrixGraph prim();
	bool isTree(int src, int dest);
	bool insertEdge(int src, int dest, int wt);
	void show();
};

MatrixGraph :: MatrixGraph(int n){
	node = n;
	matrix = (int**)calloc(sizeof(int*),n);
	for(int i=0; i<n; i++){
		matrix[i] = (int*)calloc(sizeof(int),n);
	}
}

bool MatrixGraph :: dfsSearch(int src, int dest){
	if(src>node || dest>node){return false;}
	if(src==dest){return true;}
	if(find(vt.begin(),vt.end(),src)!=vt.end()){return false;} // search element
	// push only if not visited
	st.push(src);
	vt.push_back(src);
	bool token = false;
	for(int i=0; i<node; i++){
		if(matrix[src][i] != 0){
			token = dfsSearch(i, dest);
		}
		if(token){break;}
	}
	vt.pop_back();
	st.pop();
	return token;
}

bool MatrixGraph :: bfsSearch(int src, int dest){
	if(src>node || dest>node){return false;}
	if(src==dest){return true;}
	qu.push(src);
	vt.push_back(src);
	int t = -1;
	bool token = false;
	while(!qu.empty()){
		t = qu.front();
		qu.pop();
		for(int i = 0; i<node; i++){
			if(matrix[t][i] != 0){
				if(i==dest){return true;}
				if(find(vt.begin(),vt.end(),i)!=vt.end()){continue;} // search element
				// push only if not visited
				qu.push(i);
				vt.push_back(i);
			}
		}
	}
	return token;
}

int MatrixGraph :: djikstra(int src, int dest){
	int *dist = (int*)calloc(sizeof(int),node);
	for(int i=0; i<node; i++){
		// initialise distance array suitably -1 for no edge else edge weight
		dist[i] = ( (matrix[src][i]==0) ?-1:matrix[src][i]);
	}
	dist[src] = 0; // edge from src to src is 0 as -1 creates problems
	pair<int, int> pr; // temporary pair (node,weight)
	priority_queue< pair<int, int> ,vector< pair<int, int> >,PairCompare> pq; // priority queue with comparator
	if(src>node || dest>node){return -1;}  // checks bounds
	if(src==dest){return 0;} // check if src and dest same
	pr = pair<int,int>(src,0); // create first node
	pq.push(pr); // insert first node
	while(!pq.empty()){
        pr = pq.top(); // pop the pair of node,weight
		int t = get<0>(pr); // save the node as it is used frequently
		pq.pop(); // finally pop the last element
		for(int i = 0; i<node; i++){
			// traverse over all the nodes
			if(matrix[t][i] != 0){
				// if node is nbr you are here
				// compute new distance that is parent node's distance added to distance b/w this and parent edge
				int d = dist[t] + matrix[t][i];
				if(i==dest){
					// dest found
					free(dist);
					return d;
				}
				if((dist[i]==-1) || (dist[i]>=d)){
					// if node is not connect to src : 1st condition
					// or new distance smaller then earlier distance : 2nd condition
					// then update distance
					dist[i] = d;
				}
				else{
					// it means we need not insert since we already have a shorter distance to it
					continue;
				}
				pr = pair<int,int>(i,dist[i]);
				pq.push(pr);
			}
		}
	}
	int dist_dest = dist[dest];
	free(dist);
	return dist_dest;
}

MatrixGraph MatrixGraph :: kruskal(){
	MatrixGraph newMap(this->node);
	tuple <int,int,int> edge;
	priority_queue< tuple<int, int, int> ,vector< tuple<int, int, int> >,TupleCompare> pq; // priority queue with comparator
	for(int i=0; i<node; i++){
		for(int j=i; j<node; j++){
			if (matrix[i][j] != 0){
				edge = make_tuple(i,j,matrix[i][j]);
				pq.push(edge);
			}
		}
	}
	while(!pq.empty()){
		edge = pq.top();
		int src = get<0>(edge);
		int dest = get<1>(edge);
		int wt = get<2>(edge);
		pq.pop();
		if(!newMap.dfsSearch(src,dest)){
			newMap.insertEdge(src,dest,wt);
		}
	}
	return newMap;
}

MatrixGraph MatrixGraph :: prim(){
	int *dist = (int*)calloc(sizeof(int),node);
	int *parent = (int*)calloc(sizeof(int),node);
	for(int i=0; i<node; i++){
		// initialise distance array suitably -1 for no edge else edge weight
		// initialise parent array suitably -1 for no
		dist[i] = ( (matrix[0][i]==0) ?-1:matrix[0][i]);
		parent[i] = -1;
	}
	dist[0] = 0; // edge from src to src is 0 as -1 creates problems
	parent[0] = 0; // edge from src to src is 0
	pair<int, int> pr; // temporary pair (node,weight)
	priority_queue< pair<int, int> ,vector< pair<int, int> >,PairCompare> pq; // priority queue with comparator
	pr = pair<int,int>(0,0); // create first node
	pq.push(pr); // insert first node
	while(!pq.empty()){
        pr = pq.top(); // pop the pair of node,weight
		int t = get<0>(pr); // save the node as it is used frequently
		pq.pop(); // finally pop the last element
		for(int i = 0; i<node; i++){
			// traverse over all the nodes
			if(matrix[t][i] != 0){
				// if node is nbr you are here
				// compute new distance that is parent node's distance added to distance b/w this and parent edge
				int d = dist[t] + matrix[t][i];
				if((dist[i]==-1) || (dist[i]>=d)){
					// if node is not connect to src : 1st condition
					// or new distance smaller then earlier distance : 2nd condition
					// then update distance and assign new parent
					dist[i] = d;
					parent[i] = t;
				}
				else{
					// it means we need not insert since we already have a shorter distance to it
					continue;
				}
				pr = pair<int,int>(i,dist[i]);
				pq.push(pr);
			}
		}
	}
	MatrixGraph newMap(node);
	for(int i=0;i<node;i++){
		newMap.insertEdge(i,parent[i],matrix[i][parent[i]]);
	}
	free(parent);
	free(dist);
	return newMap;
}

void MatrixGraph :: show(){
	printf("   ");
	for(int i=0; i<node; i++){
		printf(" %2d",i);
	}
	printf("\n");
	for(int i=0; i<node; i++){
		printf("%2d ",i);
		for(int j=0; j<node; j++){
			printf(" %2d",matrix[i][j]);
		}
		printf("\n");
	}
}

bool MatrixGraph:: insertEdge(int src, int dest, int wt){
	if(src>=node || dest>=node || src<0 || dest<-1){return false;}
	matrix[src][dest] = wt;
	matrix[dest][src] = wt;
	return true;
}

int main(){
    MatrixGraph myMap(10);
    myMap.show();
    myMap.insertEdge(1,2,3);
    myMap.insertEdge(1,4,3);
    myMap.insertEdge(2,3,2);
    myMap.insertEdge(2,5,4);
    myMap.insertEdge(2,6,4);
    myMap.insertEdge(3,4,1);
    myMap.insertEdge(3,7,3);
    myMap.insertEdge(4,5,4);
    myMap.insertEdge(6,7,2);
    myMap.insertEdge(8,9,5);
    myMap.show();
    bool k = myMap.dfsSearch(1,7);
    cout<<"PATH?:"<<k<<"\nNEXT\n";
    bool m = myMap.bfsSearch(1,7);
    cout<<"PATH?:"<<m<<"\nNEXT\n";
    getch();
    int p = myMap.djikstra(1,7);
    cout<<"\nDISTANCE: "<<p<<"\n";
    MatrixGraph tree = myMap.kruskal();
    cout<<"\n\n";
    tree.show();
    tree = myMap.prim();
    cout<<"\n\n";
    tree.show();
    return 1;
}
