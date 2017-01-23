//Kameron Gill
//kgill2@ucsc.edu
//1476833

//List.c Implementation for List ADT!
//based off of Queue.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//Structs ==================

typedef struct NodeObj {
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj tyoe
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//Constructors Destructors ==============

//newNode(in
