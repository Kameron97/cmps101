//Kameron Gill
//kgill2@ucsc.edu
//1476833

//Sparse.java
//based off of PA1's

import java.io.*;
import java.util.Scanner;

class Sparse {
	public static void main (String[]args) throws IOException{


		Scanner in = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(args[1]);
		int num, listA,listB;
		Matrix A,B;
		//checks for input and output in args
		if (args.length < 2) {
			throw new RuntimeException ("Error: Must have input and output args");
		}


		 num = in.nextInt();
		 A = new Matrix (num);
		B = new Matrix (num);
		listA = in.nextInt();
		listB = in.nextInt();


		in.nextLine();

		//Algorithms
		for (int i = 0; i < listA; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double val = in.nextDouble();
			A.changeEntry(row,col,val);
		}
		in.nextLine();
		for (int i = 0; i < listB; i++) {
			int row = in.nextInt();
			int col = in.nextInt();
			double val = in.nextDouble();
			B.changeEntry(row,col,val);
		}


		out.println("A has "+listA+" non-zero entries:");
		out.println(A);

		out.println("B has "+listB+" non-zero entries:");
		out.println(B);

		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));

		out.println("A+B =");
		out.println(A.add(B));

		out.println("A+A =");
		out.println(A.add(A));

		out.println("B-A =");
		out.println(B.sub(A));

		out.println("A-A =");
		out.println(A.sub(A));

		out.println("Transpose(A) =");
		out.println(A.transpose());

		out.println("A*B = ");
		out.println(A.mult(B));

		out.println("B*B = ");
		out.println(B.mult(B));

		in.close();
		out.close();
		return;
	}
}
