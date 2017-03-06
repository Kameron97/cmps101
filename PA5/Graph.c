//Kameron Gill
//1467833

//Graph ADT for PA5

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define BLACK 0
#define GRAY 1
#define WHITE 2

#define INF -1
#define NIL 0

//Values of Graph

typedef struct GraphObj{
	List *adjacent;
	int order;
	int size;

	int *discover;
	int *parent;
	int *color;
	int *finish;
}GraphObj;

//Costructors===========================

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));

	G->adjacent = calloc(n+1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->discover = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->finish = calloc(n+1, sizeof(int));

	G->order = n;
	G->size = 0;

	//sets all variables to apprioate starting
	for(int i = 0; i <n+1; i++){
		G->adjacent[i] = newList();
		G->color[i] = WHITE;
		G->parent[i]= NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	return G;
}

//Free memory Function
//freeGraph()

void freeGraph(Graph *pG){
	for(int i=1; i<=(*pG)->order; i++){
		freeList(&((*pG)->adjacent[i]));
	}
	free((*pG)->adjacent);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);
	free((*pG)->color);
	free(*pG);
	*pG = NULL;
}


//retursn # of vertices
int getOrder(Graph G){
	if (G == NULL){
		printf("getOrder() Error: Called no Null Graph!");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

//return # of edges in G
int getSize(Graph G){
	if (G == NULL){
		printf("getSize() Error: Called on NULL graph!");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

//getParent()
//returns parents at vertex u
int getParent(Graph G, int u){
	if (G == NULL){
		printf("getParent() Error: Called on Null Graph!");
		exit(EXIT_FAILURE);
	}

	//parameters check
	if( u < 1 || u > getOrder(G)){
		printf("getParent() Error: Vertex U not in parameter!");
		exit(EXIT_FAILURE);
	}

	return G->parent[u];
}

//getFinish()
//returns finish time of certain vertex u
int getFinish(Graph G, int u){
	if (G == NULL){
		printf("getFinish() Error: Called on NULL graph!");
		exit(EXIT_FAILURE);
	}

	//checked if parameter is true
	if( u < 1 || u > getOrder(G)){
		printf("getFinish() Error: Vertex U not in parameter!");
		exit(EXIT_FAILURE);
	}

	return G->finish[u];
}

//getDiscover()
//returns discovery time of certain vertex u
int getDiscover(Graph G, int u){
	if ( G == NULL){
		printf("getDiscover() Error: Called on NULL graph!");
		exit(EXIT_FAILURE);
	}

	//checks parameter
	if (u < 1 || u > getOrder(G)){
		printf("getDiscover() Error: Vertex U not in parameter!");
		exit(EXIT_FAILURE);
	}

	return G->discover[u];
}


//addedge and addarc are copies form pa4

void addEdge(Graph G, int u, int v) {
   if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
     printf("Graph Error: calling addEdge() with verticies out of bounds\n");
     exit(1);
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
     exit(1);
   }
   List S = G->adjacent[u];
   moveFront(S);
   while(index(S) > -1 && v > get(S)) {
      moveNext(S);
   }
   if(index(S) == -1)
      append(S, v);
   else
      insertBefore(S, v);
   G->size++;
}


void Visit(Graph G, List S, int u, int *time) {
   G->color[u] = GRAY;
   G->discover[u] = ++*time;
   moveFront(G->adjacent[u]);
   while(index(G->adjacent[u]) >= 0) {
      int v = get(G->adjacent[u]);
      if(G->color[v] == WHITE) {
         G->parent[v] = u;
         Visit(G, S, v, time);
      }
      moveNext(G->adjacent[u]);
   }
   G->color[u] = BLACK;
   G->finish[u] = ++*time;
   prepend(S, u);
}
//DFS Based off of CLRS DFS

void DFS(Graph G, List S){

	if (length(S) != getOrder(G)){
		printf("DFS() Error: List S not same size as G!");
		exit(EXIT_FAILURE);
	}


	for( int i = 0; i < getOrder(G); i++){
		G->parent[i] = NIL;
		G->color[i] = WHITE;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}

	int time = 0;
	moveFront(S);

	while( index(S) >= 0){
		if(G->color[get(S)] == WHITE){
			Visit(G, S, get(S), &time);
		}

		moveNext(S);
	}
	for(int size = length(S)/2; size > 0 ; size--){
		deleteBack(S);
	}
}




//transpose()
//gets G^T
Graph transpose(Graph G){
	if (G == NULL){
		printf("Transpose() error: Calling on Null Graph!");
		exit(EXIT_FAILURE);
	}

	Graph temp = newGraph(getOrder(G));	//temp = size of G
	for (int i = 0; i <= getOrder(G); i++){
		moveFront(G->adjacent[i]);

		while(index(G->adjacent[i]) != -1){
			addArc(temp, get(G->adjacent[i]), i);
			moveNext(G->adjacent[i]);
		}
	}
	return temp;
}


void printGraph(FILE *out, Graph G) {
   if(out == NULL || G == NULL) {
      printf("Graph Error: called printGraph() on a null reference\n");
      exit(1);
   }
   for(int i = 1; i <= getOrder(G); ++i) {
      fprintf(out, "%d: ", i);
      printList(out, G->adjacent[i]);
      fprintf(out, "\n");
   }
}

// Returns a copy of a given Graph
Graph copyGraph(Graph G) {
   Graph C = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); ++i) {
      moveFront(G->adjacent[i]);
      while(index(G->adjacent[i]) >= 0) {
         addArc(C, i, get(G->adjacent[i]));
         moveNext(G->adjacent[i]);
      }
   }
   return C;
}
