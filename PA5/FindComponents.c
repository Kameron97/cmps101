//KAmeron gill
//kgill2@ucsc.edu
//1476833

//FindComponents.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"
#define MAX_LEN 255
int main(int argc, char* argv[]) {
	int n = 0;
	FILE *in, *out;
	char line[MAX_LEN];

	//checks to see if two files are chosen as arguemnts
	if(argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if(in == NULL) {
		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if(out == NULL) {
		fprintf(stderr, "Unable to open file %s for writingn\n", argv[2]);
		exit(1);
	}

	fgets(line, MAX_LEN, in);
	sscanf(line, "%d", &n);



	// Puts all vertices into a List
	List list = newList();
	for(int i = 1; i <= n; i++){
		append(list, i);
	}

	Graph graph = newGraph(n);

	while(fgets(line, MAX_LEN, in) != NULL){
		int x = 0;
		int y = 0;
		sscanf(line, "%d %d", &x, &y);
		if (x == 0 && y == 0){
			break;
		}
		addArc(graph, x, y);
	}


	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, graph);
	fprintf(out, "\n");

	DFS(graph, list);

	Graph transposed = transpose(graph);
	DFS(transposed, list);

	int sccCount = 0;
	for(int i = 1; i <= getOrder(transposed); i++){
		if(getParent(transposed, i) == NIL) sccCount++; // no parent = 1 tree
	}
	fprintf(out, "G contains %d strongly connected components:\n", sccCount);

	List *sccList = calloc(sccCount + 1, sizeof(List));
	for(int i = 1; i <= sccCount; i++) {
		sccList[i] = newList();
	}
	int sccCount2 = 1;
	int listLength = length(list);
	int last = front(list);
	for(int j = 1; j <= listLength - 1; j++) {
		int v = back(list);
		deleteBack(list);
		prepend(sccList[sccCount2], v);
		if (getParent(transposed, v) == NIL){
			sccCount2++;
		}
	}
	prepend(sccList[sccCount2], last);

	for(sccCount2 = 1; sccCount2 <= sccCount; sccCount2++) {
		fprintf(out, "Component %d: ", sccCount2);
		printList(out, sccList[sccCount2]); fprintf(out, "\n");
	}

	freeGraph(&graph);
	freeGraph(&transposed);
	for(sccCount2 = 0; sccCount2 <= sccCount; sccCount2++) {
		freeList(&sccList[sccCount2]);
	}
	freeList(&list);
	free(sccList);
	fclose(in); fclose(out);
	return(0);
}
