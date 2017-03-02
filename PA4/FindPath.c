
//Kameron Gill
//1476833
//kgill2@ucsc.edu

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


int main (int argc, char* argv[]) {
	//variables
	FILE *in, *out;
	int size;
	int u,v; //vertices edges
	int source, dest;


    //check to see if two args
    if (argc != 3) {
        printf("Error: Must include two files in arguement\n");
        exit (1);
    }

    // read arguments
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

		//checks to see if in/out files are readable/writable
    if (in == NULL) {
        printf("Can't open file %s for reading.\n", argv[1]);
        exit(1);
    } if (out == NULL) {
        printf("Can't to open file %s for writing.\n", argv[2]);
        exit(1);
    }

		//gets size
    fscanf(in, "%d", &size);
    Graph G = newGraph(size);

    // read edges

    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) break;
        addEdge(G,u,v);
    }

    //print graph
    printGraph(out, G);


    List L = newList();
    // read all the lines of the input file
    while (fscanf(in, "%d %d", &source, &dest)) {
        if (source == 0 && dest == 0){
            break;
        }
        BFS(G, source);
        getPath(L, G, dest);
        if (getDist(G, dest) == -1) {
            fprintf(out, "\nThe distance from %d to %d is infinity \n", source, dest);
            fprintf(out, "No %d-%d path exists\n", source, dest);
        }
				else {
            fprintf(out, "\nThe distance from %d to %d is %d \n", source, dest, getDist(G, dest));
            fprintf(out, "A shortest %d-%d path is: ", source, dest);
            printList(out, L);
            fprintf(out, "\n");
        }
        clear(L);
    }

		//free memory
    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out);
}
