//Kameron Gill
//kgill2@Ucsc.edu
//1476833


//lab4: Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"


#define WHITE 0
#define GRAY 1
#define BLACK 2

#define INF -1
#define NIL 0
typedef struct GraphObj{
	List *adjacent;
	int order;
	int size;
	int source;
	int *parent;
	int *distance;
	int *color;
} GraphObj;

//Constructors below

//newGraph() function
Graph newGraph(int n){
	//intialization for Graph
	Graph G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	G->parent = malloc(sizeof(int)*(n+1));
	G->distance = malloc(sizeof(int)*(n+1));
	G->color = malloc(sizeof(int)*(n+1));
	G->adjacent = malloc(sizeof(List)*(n+1));


	//set parent,color,distance and adjacent to begginger setting
	for(int i =0; i<=n; i++){
		G->adjacent[i] = newList();
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->color[i] = WHITE;
	}
	return G;
}

//free Graph
//frees up any memory allocations for a Graph ADT
void freeGraph(Graph *pG){
	for (int i=0; i<=getOrder(*pG); i++){
		freeList(&(*pG)->adjacent[i]);
	}
	free((*pG)->adjacent);
	free((*pG)->parent);
	free((*pG)->distance);
	free((*pG)->color);



	free(*pG);
	*pG = NULL;
}

//getOrder
//returns order
int getOrder(Graph G){
	if (G == NULL){
		printf("getOrder() error: Called on Null Graph!");
		exit(EXIT_FAILURE);
	}
	return G->order;
}
//getSize
//return size
int getSize(Graph G){
	if (G == NULL){
		printf("getSize() Error: Called on Null Graph!");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

//getSource
//return Source.
int getSource(Graph G){
	if (G == NULL){
		printf("getSource() Error: Called on Null Graph!");
		exit(EXIT_FAILURE);
	}
	return G->source;
}

//getParent
//return the parent parent of vertex u in BFS
//or NIL if BFS has not been called.
int getParent(Graph G, int u){
	if (G == NULL){
		printf("getParent() Error: Called on Null Graph!");
		exit(EXIT_FAILURE);

	}
	if( u < 1 || u > getOrder(G)){
		printf("getParent() Error: Called on unknown value for u!");
		exit(EXIT_FAILURE);

	}
	return G->parent[u];
}


//getDist()
//returns distance from recent BFS source to vertex U
//or inf if BFS has not been called
int getDist(Graph G, int u){
	if (G == NULL){
		printf("getDist() Error: Called no Null Graph!");
		exit(EXIT_FAILURE);

	}
	if ( u < 1 || u > getOrder(G)){
		printf("getDist() Error: Called on invalid u!");
		exit(EXIT_FAILURE);

	}
	if(getSource(G) == NIL) {
		return INF;
	}
	else{
		return G->distance[u];
	}
}

//getPath()
//appends List L the vertices of a shortest path in G from source u
//or appends to L the value NIL if no path exits
//pre: getSource() != NIL
void getPath(List L, Graph G, int u){
	if ( getSource(G) == NIL){
		printf("getPath() Error: Source is Nil!");
		exit(EXIT_FAILURE);

	}
	if ( u < 1 || u > getOrder(G)){
		printf("getPath() Error: Invalid u!");
		exit(EXIT_FAILURE);

	}
	if( u == G->source){
		prepend(L,u);
	}
	else if (G->parent[u] == NIL){
		append(L, NIL);
	}
	else{
		prepend(L,u);
		getPath(L,G,G->parent[u]);
	}
}

//MANIPULIATION PROCEDURES

//makeNull
//Deletes all edges of Graph G
void makeNull(Graph G){
	for ( int i =1; i<=getOrder(G); i++){
		clear(G->adjacent[i]);
		G->color[i] = WHITE;
		G->distance[i] = NIL;
		G->parent[i] = INF;
	}
	G->source = NIL;
	G->size = 0;
}

//addEdge()
//Inserts new edge joniing u to v
//u is added to the adjacency list of V
void addEdge(Graph G, int u, int v) {
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addEdge() with verticies out of bounds\n");
		exit(EXIT_FAILURE);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

// Adds a directed edge to the Graph G from u to v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addArc() with verticies out of bounds\n");
		exit(EXIT_FAILURE);

	}
	moveFront(G->adjacent[u]);
	while(index(G->adjacent[u]) > -1 && v > get(G->adjacent[u])) {
		moveNext(G->adjacent[u]);
	}
	if(index(G->adjacent[u]) == -1)
		append(G->adjacent[u], v);
	else
		insertBefore(G->adjacent[u], v);
	G->size++;
}

// Performs Breadth-first search on the Graph G with the
// given source vertex s.
//based off of CLRS BFS psuedo code
void BFS(Graph G, int s) {
	int u;
	int v;
	G->source = s;
	for ( int i = 0; i<=getOrder(G); i++){
		G->color[i] = WHITE;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;

	List Q = newList();
	append(Q,s);

	while(length(Q) != 0){
		u = front(Q);
		deleteFront(Q);
		moveFront(G->adjacent[u]);

		while(index(G->adjacent[u])!=-1){
			v = get(G->adjacent[u]);

			if(G->color[v] == WHITE){
				G->color[v] = GRAY;
				G->distance[v] = G->distance[u]+1;
				G->parent[v] = u;
				append(Q,v);
			}
			moveNext(G->adjacent[u]);
		}
		G->color[u] = BLACK;
	}
	freeList(&Q);
	Q = NULL;

}

// Prints out the Graph by iterating over and printing out
// each adjacency list with the row number preceeding it.
void printGraph(FILE *out, Graph G) {
	if(out == NULL || G == NULL) {
		printf("Graph Error: called printGraph() on a null reference");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); ++i) {
		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]);
		fprintf(out, "\n");
	}
}
