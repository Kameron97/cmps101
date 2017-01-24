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

//newNode()
//Retursn reference to Node object. Initializes next and data fields.
//Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL.
//Private
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//List newList()
//returns refernce to new empty List Object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front =L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	return(L);
}

//freeList()
//frees all heap memory associated with List *pQ and sets *pQ to NULL
void freeList(List* pL) {
   if(pL != NULL && *pL != NULL) {
      Node tmp = (*pL)->front;
      while(tmp != NULL) {
         Node cur = tmp;
         tmp = tmp->next;
         free(cur);
      }
      free(*pL);
      *pL = NULL;
   }
}

//Access functions ==========================================


//isEmpty()
//checks to see if List is empty
int isEmpty(List L){
	if(L == NULL){
		printf("List Error: Calling isEmpty() on NULL QUEUE reference\n");
		exit(1);
	}
	return(L->length==0);
}

//length()
//Retursn the Length of L
int length(List L){
	if(L == NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

//index()
//Returns the index
int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}

//front()
//returns the value at the front of L
//pre: !isEmpty(L);
int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List Reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling front() on empty List reference\n");
		exit(1);
	}
	return(L->front->data);
}

//back()
//returns the value at the back of L
//Pre: !isEmpty(L);
int back(List L){
	if( L == NULL){
		printf("List Error: calling back on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling back on empty List reference\n");
		exit(1);
	}
	return(L->back->data);
}

//get()
//returns value at cursor
//pre: !isEmpty(L);
int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	return(L->cursor->data);
}

//equals()
//returns true(1) if A is identical to B, false (0) otherwise
//inspired off of Queue.c
int equals(List A, List B){
	int eq = 0;
	Node N = NULL;
	Node M = NULL;

	if( A == NULL || B == NULL){
		printf("List error: calling equals() on NULL List reference\n");
		exit(1);
	}

	eq = (A->length == B->length);
	N= A->front;
	M = B->front;
	while(eq && N != NULL){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

//Manipultation procedure ==================

//clear()
//emptys entire List to make it empty
void clear(List L){
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = 0;
}

//moveFront()
//will move cursor to the front of the List
//Pre: !isEmpty();
void moveFront(List L){
	if(L == NULL){
		printf("List error: calling moveFront() on NULL list reference\n");
		exit(1);
	}
	if( isEmpty(L)){
		printf("List error: calling moveFront() on empty List reference\n");
		exit(1);
	}

	L->cursor = L->front;
	L-> index = 0;
}

//moveBack()
//will move cursor to the back of the List
//pre: !isEmpty();
void moveBack(List L){
	if(L == NULL){
		printf("List error: calling moveBack() on NULL list reference\n");
		exit(1);
	}
	if( isEmpty(L)){
		printf("List error: calling moveBack() on empty List reference \n");
		exit(1);
	}
	L->cursor = L->back;
	L->index = L->length -1;
}

//movePrev()
//Move cursor one spot toward begginging of List
//if cursor is at front and called, becomes undefined
//undefined, does nothing
void movePrev(List L){
	if(L->cursor != NULL && L->index != 0){
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if(L->cursor != NULL && L->index == 0){
		L->cursor = NULL;
		L->index = -1;
	}
}

//moveNext()
//Move cursor one spot back of the List
//if cursor is define and at back, becomes undefined
//if undefined does nothing
void moveNext(List L){
	if(L->cursor != NULL && L->index != L->index -1){
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if (L->cursor != NULL && L->index == L->length -1){
		L->cursor = NULL;
		L->index = -1;
	}
}

//prepend()
//insert new element into this List. If List in non-empty.
//insertion takes place before fornt elemnt
void prepend(List L,int data){
	Node temp = newNode(data);

	if(L->front == NULL){
		L->front = L->back = temp;
	}
	else{
		L->front->prev = temp;
		temp->next = L->front;
		L->front = temp;
		L->index++;
	}
	L->length++;
}

//append()
//insert new elment into this List. If list in no-empty,
//insertion takes place after back element
void append(List L, int data){
	Node temp = newNode(data);

	if(L->front == NULL){
		L->front = L->back = temp;
	}
	else{
		L->back->next = temp;
		temp->prev = L->back;
		L->back = temp;
	}
	L->length++;
}

//insertBefore()
//Inserts new element before cursor element in this List.
//Pre: length()>0, index() >= 0
void insertBefore(List L, int data){
	Node temp = newNode(data);

	if( isEmpty(L)){
		printf("List error: insertBefore() called on empty List reference\n");
		exit(1);
	}else {
		temp->next = L->cursor;

		if(L->cursor->prev != NULL){
			temp->prev = L->cursor->prev;
			L->cursor->prev->next = temp;
		}
		L->cursor->prev = temp;
		if(temp->prev == NULL){
			L->front = temp;
		}
		L->index++;
		L->length++;
	}
}

//insertAfter()
//inserts new elemeemt after cursor element in this List.
//Pre: length()>0, index>=0
void insertAfter(List L, int data){
	Node temp = newNode(data);

	if( isEmpty(L)){
		printf("List Error: insertAfter() called on empty List Reference\n");
		exit(1);

	}else {
		L->cursor->next->prev = temp;
		temp->next = L->cursor->next;
		temp->prev = L->cursor;
		L->cursor->next = temp;
		L->length++;
	}
}

//deleteFront(){
//pre: length() >0
void deleteFront(List L){
	if( isEmpty(L)){
		printf("List Error: deleteFront called on empty List reference \n");
		exit(1);
	}

	if(L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}
	L->front = L->front->next;
	L->front->prev = NULL;
	L->length--;
//	freeNode(&
}
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling DeList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling DeList on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( L->length > 1 ) {L->back = L->back->prev; }
   else {
      L->front = L->back = NULL;
      //freeNode(L->front);
   }
   L->length--;
   N = NULL;
   freeNode(&N);
}

//delete
//delete element at cursor
void delete(List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling DeList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling DeList on an empty List\n");
      exit(1);
   }else if(index(L) == -1){
      printf("List Error: calling delete on a null cursor");
      exit(1);
   }else if(index(L) >= 0){
      if(L->cursor->prev == NULL){
         L->front = L->cursor->next;
      }
      else if(L->cursor->next == NULL){
         L->back = L->cursor->prev;
      }
      N = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->cursor = NULL;
      L->length--;
      L->index = -1;
      freeNode(&N);
   }


}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      printf("%d ", N->data);
   }
   printf("\n");
}

   // copy(): returns a new List identical to this one.
   List copyList(List L){
      List A = newList();
      Node N = L->front;

      while( N!=NULL ){
         append(A, N->data);
         N = N->next;
      }
      return A;
   }
