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

typedef struct GraphObj{
	List *adjacent;
	int order;
	int size;
	int source;
	int *parent;
	int *distance;
	int *color;
}GraphObj;

//Constructors below

//newGraph() function
Graph newGraph(int n){
	//intialization for Graph
	Graph G = malloc(sizeof(GraphObj));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));
	G->color = calloc(n+1, sizeof(int));

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

	*pG->adjacent = NULL;
	*pG->parent = NULL;
	*pG->distance = NULL;
	*pG->color = NULL;

	free(*pG);
	*pG = NULL;
}

//getOrder
//returns order
int getOrder(Graph G){
	return G->order;
}
//getSize
//return size
int getSize(Graph G){
	return G->size;
}

