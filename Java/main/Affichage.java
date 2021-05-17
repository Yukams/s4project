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
		System.out.print("Difficulté? => ");
		int diff = sc.nextInt();
		while(diff <=1 || diff > 6) {System.out.print("Difficulté (min 2, max 6 déconseillé)=> "); diff = sc.nextInt();}
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
	
	public int choixNbUsers() {
		int nbUsers = 0;
		System.out.print("Nombre d'utilisateur à ajouter? => ");
		nbUsers = sc.nextInt();
		while(nbUsers < 1) {System.out.print("Nombre d'utilisateur à ajouter? (Creator existe déjà)=> "); nbUsers = sc.nextInt();}
		System.out.println("\n        ***... Ajout de "+nbUsers+" utilisateur ...***");
		return nbUsers;
	}
	
	public void dispBlockChain(Blockchain blockchain){
		int nbBlock = blockchain.getNb_blocs();
		System.out.println("\n====================================[BLOCKCHAIN (MAX "+blockchain.getNb_block_max()+")]====================================");
		for(int i = 0; i<nbBlock;i++) {
			Block b = blockchain.getBlock_list()[i];
			System.out.println("--------------------------------------------(Block "+i+")---------------------------------------");
			System.out.println("	[PrevHash      ] => "+b.getPrev_hash());
			System.out.println("	[Hash          ] => "+b.getHash());
			System.out.println("	[nbTransactions] => "+b.getNb_trans());
			System.out.println("--------------------------------------------------------------------------------------------");
		}
		System.out.println("============================================================================================");
	}
	
	public void dispUsers(Coinbase coinbase){
		int nbUsersTotal = coinbase.getUserDB().getNbUsers();
		System.out.println("\n================[USERS (TOTAL "+nbUsersTotal+")]===============");
		for(int i = 0; i<nbUsersTotal;i++) {
			User user = coinbase.getUser(i);
			if(user.getIdentifiant() == 0) {System.out.println("------------------(Creator)---------------------");}
			else {System.out.println("------------------(User "+i+")-----------------------");}
				System.out.println("[Wallet] => "+user.getWallet());
		}
		System.out.println("=================================================");
		
	}
	public void dispHelp(){
		System.out.println("</>===========</>[HELP]</>=========</>");
		System.out.println("	=>(  h  ) Afficher l'aide actuel");
		System.out.println("	=>(  b  ) Afficher les détails sur la Blockchain");
		System.out.println("	=>(  u  ) Afficher les détails sur la Base de donnée d'utilisateur");
		System.out.println("	=>( hm  ) Initialisation de la phase 'Helicopter Money'");
		System.out.println("	=>( rt  ) Initialisation de la phase 'Transactions Aléatoires'");
		System.out.println("	=>(money) Afficher la masse monétaire");
		System.out.println("	=>(add  ) Ajouter un ou plusieurs utilisateurs");
		System.out.println("	=>(  q  ) Quitter");
		System.out.println("</>========</>[FIN HELP]</>========</>");
	}
	public void dispHelico(Coinbase coinbase){
		double totalMoney = coinbase.getMasseMonetaire();
		System.out.println("\n	+*+*+*+*+... %HelicopterMoney% ...+*+*+*+*+");
		System.out.println("=============[MONEY (TOTAL APRES: "+totalMoney+"Bnb)]================");
		
	}
	public void dispTotal(Coinbase coinbase){
		double totalMoney = coinbase.getMasseMonetaire();
		System.out.println("===========[TOTAL MONEY: ("+totalMoney+"Bnb)]===============");
	}
	
	public void clearTerminal() {
		for(int i = 0; i<20; i++) 
			System.out.println("\n");
		
	}
	
	
}
