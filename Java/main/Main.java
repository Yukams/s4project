package main;
import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
		int difficulty,maxTrans,nbMaxBlock,nbUsers;
		Scanner scanner = new Scanner(System.in);
		Affichage disp = new Affichage(scanner);
		
		System.out.print("Affichage? (o ou n): ");
		String choice = "";
		choice = scanner.nextLine();
		while(choice.equals("o") == false || choice.equals("O") == false || choice.equals("n") == false || choice.equals("N") == false) {
			if(choice.equals("o") || choice.equals("O")){
				System.out.println("*-*-*-*-{Initialisation}-*-*-*-*");
				difficulty = disp.choixDifficuly();
				maxTrans = disp.choixMaxTrans();
				nbMaxBlock = disp.choixMaxBlock();
				Blockchain bc = new Blockchain(difficulty,maxTrans,nbMaxBlock);
				Coinbase cb = new Coinbase(bc);
				try{Thread.sleep(1000);}
				catch(InterruptedException ex){Thread.currentThread().interrupt();}
				
				String innerChoice = "h";
				disp.clearTerminal();
				disp.dispHelp();
				System.out.print("Choix ? ");
				while(innerChoice.equals("q") == false) {
					
					innerChoice = scanner.nextLine();
					if(innerChoice.equals("q")) {
						disp.clearTerminal();
						System.out.println("Au revoir.");
						break;
					}
					else if(innerChoice.equals("h")) {
						disp.clearTerminal();
						disp.dispHelp();
						System.out.print("Choix ? ");
					}
					else if(innerChoice.equals("b")) {
						disp.clearTerminal();
						disp.dispBlockChain(bc);
						System.out.print("Choix ? ");
					}
					else if(innerChoice.equals("u")) {
						disp.clearTerminal();
						disp.dispUsers(cb);
						System.out.print("Choix ? ");
					}
					else if(innerChoice.equals("hm")) {
						disp.clearTerminal();
						cb.helicopterMoney();
						disp.dispHelico(cb);
						System.out.print("Choix ? ");
					}
					else if(innerChoice.equals("rt")) {
						disp.clearTerminal();
						cb.trans_aleatoire();
						System.out.print("Choix ? ");
					}
					else if(innerChoice.equals("money")) {
						disp.clearTerminal();
						disp.dispTotal(cb);
						System.out.print("Choix ? ");
					}
					else if(innerChoice.equals("add")) {
						disp.clearTerminal();
						nbUsers = disp.choixNbUsers();
						cb.add_users_cb(nbUsers);
						System.out.print("Choix ? ");
					}
				}
				break;
			}
			else if(choice.equals("n") || choice.equals("N")){
				System.out.println("Au revoir.");
				break;
			}
			else {System.out.print("Affichage? (o or n): ");choice = scanner.nextLine();}
			
		}
	}

}
