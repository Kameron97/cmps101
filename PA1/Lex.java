//Kameron Gill
//1476833
//Lex.java

//Influenced from FilIO.java

import java.io.*;
import java.util.Scanner;

class Lex{
	public static void main(String[] args) throws IOException{
		Scanner in = null;
		PrintWriter out = null;
		String[] token = null;
		int i, n, lineNumber = 0;

		if(args.length <2){
			System.err.println("Usage: Lex infile outfile");
			System.exit(1);
		}

		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));
	}
}

