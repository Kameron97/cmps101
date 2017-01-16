//Kameron GIll
//1476833
//PA1

//ADT list
//based off of Queue.java

class List{
	private class Node{
		int data;
		Node next;
		Node prev;
		
		Node(int data){
			this.data = data;
			next = null;
			prev = null;
		}
		
