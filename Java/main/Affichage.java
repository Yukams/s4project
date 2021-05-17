/**
 * 
 */
package main;
import java.util.Scanner;

public class Affichage{
	private Scanner sc;
	public Affichage(Scanner listener){
		this.sc = listener;
	}
	
	public int choixDifficuly() {
		System.out.print("Difficulty? => ");
		int diff = sc.nextInt();
		return diff;
	}
	public int choixMaxBlock() {
		System.out.print("Nombre de blocs? => ");
		int maxBlock = sc.nextInt();
		while(maxBlock <=1) {System.out.print("Nombre de blocs (min 2)=> "); maxBlock = sc.nextInt();}
		return maxBlock;
	}
	public int choixMaxTrans() {
		System.out.print("Nombre de Transactions/Bloc? => ");
		int maxTrans = sc.nextInt();
		while(maxTrans < 1) {System.out.print("Nombre de Transactions/Bloc (min 1)=> "); maxTrans = sc.nextInt();}
		return maxTrans;
	}
	
	
	
}
