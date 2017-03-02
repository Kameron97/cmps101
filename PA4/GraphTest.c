//Kameron Gill

//GraphTest.c
//used parts from GraphClient.

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]){
int n = 8;

Graph G = NULL;

G = newGraph(n);

fprintf(stdout, "%d\n",getOrder(G) );

return(0);
}
