//Kameron GIll
//1476833
//PA1

//ADT list
//based off of Queue.java

class List{
	private class Node{
		//Fields
		int data;
		Node next;
		Node prev;

		//Constructors
		Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}

	}

	//Fields
	private int length;
	private int index;
	private Node front;
	private Node back;
	private Node cursor;


	//Constructor
	//creates a new empty list
	List(){
		front = back = cursor = null;
		length = 0;
		index = -1;
	}
	// Access functions


	//returns the number of elements in this List
	int length(){
		return length;
	}

	//if cursor is defined, returns the index of the cursor element,
	//otherwise returns -1.
	int index(){
		return index;
	}

	//Returns front element. pre:length()>0
	int front(){
		if(length<1){
			throw new RuntimeException("List Error: front() called on empty list!);
		}
		return front.data;
	}

	//Retrusn back element. Pre: length() >0
	int back(){
		if(length<1){
			throw new RuntimeException("List Error: back() called on empty list!);
		}
		return back.data;
	}

	//Returns cursor element. Pre: length()> 0, index >= 0
	int get(){
		if(index<0 || length<1){
			throw new RuntimeException("List Error: get() called on empty list!");
		}
		return cursor.data;
	}

	//Returns true if this List and L are the same integer
	//sequence. The cursor is ignored in both lists.
	boolean equals(List L){
		boolean eq = false;
		Node N = this.front;
		Node M = L.front;

		eq = (this.length == M.length);

		while(eq && N != null){
			eq = (N.equals(M.data));
			N = N.next;
			M = M.next;
		}
	return eq;
	}


	//Manipulation procedures

	//Resets this List to its original empty state
	void clear(){
		front = back = cursor = null;
		length = 0;
		index = -1;
	}

	//If List is non-empty, place the cursor  under the front element,
	//otherwise does nothing
	void moveFront(){
