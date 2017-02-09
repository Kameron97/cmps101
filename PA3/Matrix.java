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
		if(n <1){
			throw new RuntimeException("Matrix error: Matrix not big enough!");
		}
		size = n;
		row = new List[size];

		for(int i = 0; i<size; i++){
			row[i] = new List();
		}
	}


	//Access functions

	//returns n, the number of rows and column of this Matrix
	int getSize(){
		return size;
	}

	//returns the number of non-zero entries in this Matrix
	int getNNZ(){
		return NNZ;
	}

	public boolean equals(Object x){
		Matrix temp = (Matrix) x;

		if(getSize() != ((Matrix) x).getSize()){
			return false;

			for(int i = 0; i<=getSize(); i++){
				if(!( row[i].equals((Matrix) x).row[i])){
					return false;
				}
			}
		}
		return true;
	}

	///Manipulation procedures

	//sets this Matrix to the zero state
	void makeZero(){
		for(int i = 0; i<=getSize(); i++){
			row[i].clear();
		}
		NNZ = 0;
	}

	//returns a new Matrix having the same entries as this Matrix
	Matrix copy(){
		Matrix ret = new Matrix(size);

		for(int i = 0; i<size; i++){
			M.row[i]


