//Kameron Gill
//1476833
//kgill2@ucsc.edu

//PA3.
//Matrix.java

public class Matrix{
	private class Entry{
		
		int column;
		double value;

		Entry(int column, double value){
			this.column = column;
			this.value = value;
		}

	
		//toString method
		public String toString(){
			return "("+ column+", "+value+")";
		}

	}

	private List[] row;
	private int size;
	private int NNZ = 0;

	//Makes a new n x n zero Matrix. pre: n>=1
	void Matrix(int n){
