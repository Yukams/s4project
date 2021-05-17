package main;
import java.util.Scanner;

public class main {
	
	public static void main(String[] args) {
		int difficulty,maxTrans,nbMaxBlock,nbUsers;
		Scanner scanner = new Scanner(System.in);
		Affichage disp = new Affichage(scanner);
		
		System.out.print("Display? (y or n): ");
		String choice = "";
		choice = scanner.nextLine();
		while(choice.equals("y") == false || choice.equals("Y") == false || choice.equals("n") == false || choice.equals("N") == false) {
			if(choice.equals("y") || choice.equals("Y")){
				difficulty = disp.choixDifficuly();
				maxTrans = disp.choixMaxTrans();
				nbMaxBlock = disp.choixMaxBlock();
				Blockchain bc = new Blockchain(difficulty,maxTrans,nbMaxBlock);
				Coinbase cb = new Coinbase(bc);
				UserDB ub = cb.getUserDB();
				
				break;
			}
			else if(choice.equals("n") || choice.equals("N")){
				System.out.println("GOOD BYE");
			}
			else {System.out.print("Display? (y or n): ");}
			choice = scanner.nextLine();
		}
	}

}
