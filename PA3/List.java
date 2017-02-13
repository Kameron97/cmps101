//Kameron Gill
//kgill2@ucsc.edu1
//1476833
//PA3

//ADT list
//based off of List.java from PA1

public class List{
	private class Node{
		//Fields
		Object data;
		Node next;
		Node prev;

		//Constructors
		Node(Object data){
			this.data = data;
			next = null;
			prev = null;
		}


		// Returns String representation of the data property.
		public String toString() {
			return String.valueOf(data);
		}

		// Returns true if two Nodes data properties are equal.
		
	}


	//Fields
	private int length;
	private int index = -1;
	private Node front;
	private Node back;
	private Node cursor;


	//Constructor
	//creates a new empty list
	List(){
		front = back = cursor = null;
		length = 0;
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
	Object front(){
		if(length<1){
			throw new RuntimeException("List Error: front() called on empty list!");
		}
		return front.data;
	}

	boolean isEmpty(){
		return length==0;
	}

	//Retrusn back element. Pre: length() >0
	Object back(){
		if(length<1){
			throw new RuntimeException("List Error: back() called on empty list!");
		}
		return back.data;
	}

	//Returns cursor element. Pre: length()> 0, index >= 0
	Object get(){
		if(index<0 || length<1){
			throw new RuntimeException("List Error: get() called on empty list!");
		}
		return cursor.data;
	}

	//Returns true if this List and L are the same integer
	//sequence. The cursor is ignored in both lists.
	boolean equals(List L){
		 boolean flag  = true;
		 Node N = this.front;
		 Node M = L.front;

		 if( this.length==L.length ){
				while( flag && N!=null){
					 flag = (N.data==M.data);
					 N = N.next;
					 M = M.next;
				}
				return flag;
		 }else{
				return false;
		 }
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
		if(length > 0) {
			cursor = front;
			index = 0;
		}
	}

	void moveBack() {
		if(length > 0) {
			cursor = back;
			index = length - 1;
		}
	}

	// If cursor is defined and not at front, moves cursor one step
	// toward front of this List, if cursor is defined and at front,
	// cursor becomes undefined, if cursor is undefined does nothing.
	void movePrev() {
		if(cursor != null && index != 0) {
			cursor = cursor.prev;
			index--;
		}
		else if(cursor != null && index == 0) {
			cursor = null;
			index = -1;
		}
	}

	// If cursor is defined and not at back, moves cursor one step
	// toward back of this List, if cursor is defined and at back,
	// cursor becomes undefined, if cursor is undefined does nothing.
	void moveNext() {
		if(cursor != null && index != length - 1) {
			cursor = cursor.next;
			index++;
		}
		else if(cursor != null && index == length - 1) {
			cursor = null;
			index = -1;
		}
	}
	//Insert new element into this List. if List is non-empty,
	//insertion takes place before front element
	void prepend(Object data){
		Node temp = new Node(data);
		if(front == null){
			front = back = temp;
		}
		else{
			front.prev = temp;
			temp.next = front;
			front = temp;
			index++;
		}
		length++;
	}

	//insert new element into this List. If list is non-empty,
	//insertion takes place after back element
	void append(Object data){
		Node temp = new Node(data);
		if(front == null){
			front = back = temp;
		}
		else{
			back.next = temp;
			temp.prev = back;
			back = temp;

		}
		length++;
	}

	// Inserts new element before cursor element in this List. Pre: length()>0, getIndex()>=0
	void insertBefore(Object data){
		Node node = new Node(data);
		if(length ==0){
			throw new RuntimeException("List Error: insertBefore() called on empty list!");
		}
		else{
			node.next = cursor;
			if(cursor.prev != null){
				node.prev = cursor.prev;
				cursor.prev.next = node;
			}
			cursor.prev = node;
			if (node.prev == null)
				front = node;
		}
		index++;
		length++;
	}

	// Inserts new element after cursor element in this
	// List. Pre: length()>0, getIndex()>=0
	void insertAfter(Object data) {
		if(length() < 0 && index < 0)
			throw new RuntimeException("List error: insertAfter() called on empty List");
		if(cursor == back) {
			append(data);
		}
		else {
			Node temp = new Node(data);
			cursor.next.prev = temp;
			temp.next = cursor.next;
			temp.prev = cursor;
			cursor.next = temp;
			length++;
		}
	}

	// Deletes the front element.
	// Pre: length() > 0
	void deleteFront() {
		if(length < 1)
			throw new RuntimeException("List Error: deleteFront() called on an empty List");
		if(cursor == front) {
			cursor = null;
			index = -1;
		}
		front = front.next;
		front.prev = null;
		length--;
	}

	// Deletes the back element.
	// Pre: length() > 0
	void deleteBack() {
		if(length < 1)
			throw new RuntimeException("List Error: deleteBack() called on an empty List");
		if(cursor == back) {
			cursor = null;
			index = -1;
		}
		back = back.prev;
		back.next = null;
		length--;
	}

	// Deletes cursor element, making cursor undefined.
	// Pre: length() > 0, index() >= 0
	void delete() {
		if(index < 0)
			throw new RuntimeException("List Error: delete() called with an undefined index on List");
		if(length < 1)
			throw new RuntimeException("List Error: delete() called on an empty List");
		if(cursor == back)
			deleteBack();
		else if(cursor == front)
			deleteFront();
		else {
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			index = -1;
			length--;
		}
	}


	//Other methods

	public String toString() {
		String str = "";

		for(Node temp = front; temp != null; temp = temp.next){
			str+= temp.toString() + " ";
		}
		return str;
	}


}
