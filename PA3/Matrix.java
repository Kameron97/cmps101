//Kameron Gill
//1476833
//kgill2@ucsc.edu

//PA3.
//Matrix.java

public class Matrix {
	private class Entry {

		int column;
		double value;

		Entry(int column, double value){
			this.column = column;
			this.value = value;
		}
		//equals() method to check if value/column are equal
		public boolean equals(Object x) {
			boolean eq = false;
			Entry that;
			if(x instanceof Entry) {
				that = (Entry) x;
				eq = (this.column == that.column && this.value == that.value);
			}
			return eq;
		}

		//toString method
		public String toString() {
			return "(" + column + ", " + value + ")";
		}



	}



	private List[] row;
	private int NNZ = 0;

	//Makes a new n x n zero Matrix. pre: n>=1
	Matrix(int n){
		if(n <1) {
			throw new RuntimeException("Matrix error: Matrix not big enough!");
		}
		row = new List[n+1];
		for(int i = 1; i<n+1; i++) {
			row[i] = new List();
		}
	}


	//Access functions

	//returns n, the number of rows and column of this Matrix
	int getSize(){
		return row.length-1;
	}

	//returns the number of non-zero entries in this Matrix
	int getNNZ() {

		return NNZ;
	}


	//checks to see if two amtrixs are the same.
	public boolean equals(Object x){
		Matrix that;

		if(x instanceof Matrix){
			that = (Matrix)x;
			if(getSize() != that.getSize()){
				return false;
			}
			for(int i =1; i<=getSize(); i++){
				if(!(row[i].equals(that.row[i])))
					return false;
			}
		}
		return true;
	}
	///Manipulation procedures

	//sets this Matrix to the zero state
	void makeZero(){
		for(int i = 1; i<=getSize(); i++) {
			row[i].clear();
		}
		NNZ = 0;
	}

	// Returns a new Matrix having the same entries as this Matrix.
	Matrix copy() {
		Matrix temp = new Matrix(getSize());

		for(int i = 1; i<= getSize(); i++) {
			for(row[i].moveFront(); row[i].index() != -1; row[i].moveNext()) {
				Entry E = (Entry)row[i].get();

				temp.changeEntry(i, E.column, E.value);
			}

		}
		temp.NNZ = NNZ;
		return temp;
	}

	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x) {
		if(i < 1 || i > getSize() || j < 1 || j > getSize()) {
			throw new RuntimeException("changeEntry() called on Matrix with invalid ith, jth position");
		}

		boolean find = false;
		row[i].moveFront();
		while(row[i].index() >= 0) {
			Entry entry = (Entry) row[i].get();
			find = (entry.column == j );
			if(find == true) {
				if(x == 0.0) {
					row[i].delete();
					NNZ--;
					return;
				}
				else {
					entry.value = x; return;
				}
			}
			row[i].moveNext();
		}

		if(!find && x != 0.0) {
			row[i].moveFront();
			if(row[i].index() == -1) {
				row[i].append(new Entry(j, x));
				NNZ++;
				return;
			}
			else {
				while(row[i].index() > -1 && ((Entry)row[i].get()).column < j) {
					row[i].moveNext();
				}
				if(row[i].index() > -1) {
					row[i].insertBefore(new Entry(j, x));
					NNZ++;
					return;
				}
				else {
					row[i].append(new Entry(j, x));
					NNZ++;
					return;
				}
			}
		}
	}

	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x){
		int col = 0;
		double val1 = 0, valFinal = 0;
		Entry tempEntry;
		Matrix tempMatrix = new Matrix(getSize());

		tempMatrix.NNZ = NNZ;
		//iterates through Matrix.
		for(int i = 1; i < row.length; i++) {
			if(row[i].isEmpty() == false) {
				row[i].moveFront();

				while(row[i].index() != -1) {
					//takes value of old value in matrix
					val1 =(((Entry)row[i].get()).value);
					//old value of column
					col =(((Entry)row[i].get()).column);
					valFinal = val1*x; //new value of value.
					tempEntry = new Entry(col, valFinal);
					tempMatrix.row[i].append(tempEntry);
					row[i].moveNext();
				}
			}
		}
		return tempMatrix;
	}

	//returns a new matrix that is the sum of this MAtrix with M
	//pre: getSize()==M.getsize();
	Matrix add(Matrix M){
		if(getSize() != M.getSize()) {
			throw new RuntimeException("Matrix Error: Matrices must be the same size");
		}
		int c = 0, e2 = 0;
		double v1 = 0, v2 = 0;
		List temp1, temp2;
		Matrix ret = new Matrix(getSize());

		//iterate through 1->end of Matrix
		for(int i = 1; i < row.length; i++) {
			temp1 = M.row[i];
			temp2 = this.row[i];

			//go through all types

			//if one Matrix is empty.
			if(temp1.isEmpty() && !temp2.isEmpty()) {
				temp2.moveFront();
				while(temp2.index() != -1) {
					ret.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
					temp2.moveNext();
					ret.NNZ++;
				}

			}else if(!temp1.isEmpty() && temp2.isEmpty()) {
				temp1.moveFront();
				while(temp1.index() != -1) {
					ret.changeEntry(i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
					temp1.moveNext();
					ret.NNZ++;
				}
				//not empty Matrix
			}else if(!temp1.isEmpty() && !temp2.isEmpty()) {
				temp2.moveFront();
				temp1.moveFront();

				//checks to see if at Matrix is empty/at end
				while(temp1.index() != -1 && temp2.index() != -1) {
					//equal
					if(((Entry)temp1.get()).column == ((Entry)temp2.get()).column) {
						v1 = ((Entry)temp1.get()).value;
						v2 = ((Entry)temp2.get()).value;
						c = ((Entry)temp2.get()).column;
						ret.changeEntry(i, c, (v1+v2));
						temp1.moveNext();
						if(!this.equals(M))
							temp2.moveNext();
						///if temp1 < temp2
						//this < M
					}else if(((Entry)temp1.get()).column < ((Entry)temp2.get()).column) {
						v1 = ((Entry)temp1.get()).value;
						c = ((Entry)temp1.get()).column;
						ret.changeEntry(i, c, v1);
						temp1.moveNext();
						ret.NNZ++;
						//if temp1>temp2
					}else if(((Entry)temp1.get()).column > ((Entry)temp2.get()).column) {
						v2 = ((Entry)temp2.get()).value;
						c = ((Entry)temp2.get()).column;
						ret.changeEntry(i, c, v2);
						temp2.moveNext();
						ret.NNZ++;
					}
				}

				while(temp1.index() != -1) {
					ret.changeEntry( i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
					temp1.moveNext();
					ret.NNZ++;
				}

				while(temp2.index() != -1) {
					ret.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
					temp2.moveNext();
					ret.NNZ++;
				}
			}
		}
		return ret;
	}

	//returns a new Matrix that is the difference of the Matrix with M
	//pre: getSize() ==M.getSize()
	//rehash of add() except it minuses
	Matrix sub(Matrix M){
		if(getSize() != M.getSize()) {
			throw new RuntimeException("Matrix Error: Matrices must be the same size");
		}

		//add the negative
		Matrix A = new Matrix(getSize());
		M = (M.scalarMult(-1));
		A = (this.add(M));
		return A;
	}
	//returns a new Matrix that is the transpose of this Matrix
	Matrix transpose(){
		Matrix temp = new Matrix(getSize());
		for(int i = 1; i<= getSize(); i++) {
			row[i].moveFront();

			while(row[i].index() != -1) {
				temp.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).value);
				row[i].moveNext();

			}
		}
		return temp;
	}

	//return a new Matrix that is the product of this Matrix with M
	//pre :getSize() == M.igetSize()
	Matrix mult(Matrix M) {
		if(getSize() != M.getSize()) {
			throw new RuntimeException("mult() called on two Matricies with different sizes");
		}
		Matrix temp1 = new Matrix(getSize()); //ret Matrix
		Matrix temp2 = M.transpose();  //M Matrix transposed
		for(int i = 1; i <= getSize(); ++i) {
			if(row[i].length() == 0) continue;
			for(int j = 1; j <= getSize(); ++j) {
				if(temp2.row[j].length() == 0) continue;
				temp1.changeEntry(i, j, dot(row[i], temp2.row[j]));
			}
		}
		return temp1;
	}

	// Overrides Object's toString() method.
	public String toString(){
		String a = "";
		for(int i = 1; i < row.length; i++) {
			if(!row[i].isEmpty()) {
				a += i+ ":";
				a += String.valueOf(row[i]) + "\n";
			}
		}
		return a;

	}

	// Helper for dot product of two Lists
	private static double dot(List P, List Q) {
		double product = 0.0;
		P.moveFront();
		Q.moveFront();
		while(P.index() >= 0 && Q.index() >= 0) {
			Entry a = (Entry) P.get();
			Entry b = (Entry) Q.get();
			if(a.column > b.column) {
				Q.moveNext();
			} else if(a.column < b.column) {
				P.moveNext();
			} else {
				product += (a.value * b.value);
				P.moveNext();
				Q.moveNext();
			}
		}
		return product;
	}
}
