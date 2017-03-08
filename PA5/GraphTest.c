//GraphTest.c



#include <stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]){
	List S = newList();
	Graph G = newGraph(8);
	Graph T=NULL, C=NULL;
	//int n;

	fprintf(stdout, "%d\n", getDiscover(G, 8));

	fprintf(stdout, "%d\n", getFinish(G,8));


for(int i=1; i<=8; i++) {
	append(S, i);
}

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);

   printGraph(stdout, G);
	// for(int i=1; i<=8; i++) append(S, i);

	 DFS(G,S);
	 for(int i=1; i<=8; i++){
	      fprintf(stdout, "%d ",  getParent(G, i));
	   }
		 fprintf(stdout, "\n");


		 T = transpose(G);
		 C = copyGraph(G);
		 fprintf(stdout, "\n");

		 printGraph(stdout, T);
		 fprintf(stdout, "\n");

		 printGraph(stdout, C);

}
