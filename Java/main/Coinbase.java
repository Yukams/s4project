package main;

import java.util.Random;

public class Coinbase { //super utilisateur coinbase
	
	private double masseMonetaire;
	private UserDB userDB;
	private Blockchain blockchain;
	private final int MAX_VALUE_PER_TRANS = 10;
	
	public Coinbase(Blockchain blockchain) {
		this.userDB = new UserDB(blockchain);
		this.userDB.init_user_db();
		this.masseMonetaire = 50;
		this.blockchain = blockchain; 
	}
	
	public void helicopterMoney() {
		int nbUsers = this.userDB.getNbUsers();
		int nbTransMax = this.blockchain.getNb_max_trans();
		
		int nbBlockChain,nbTransReste;
		Block latestB;
		
		
		int nbTransPast = 0;
		
		
		Transactions tl = new Transactions(nbTransMax);
		for(int i = 1; i< nbUsers; i++){
			if(this.blockchain.getNb_blocs() == this.blockchain.getNb_block_max()) {
				System.out.println("Le maximum de la Blockchain est atteint");
				return;
			}
			nbBlockChain = this.blockchain.getNb_blocs();//nb block de la bc
			latestB = this.blockchain.getBlock_list()[nbBlockChain-1];
			nbTransReste = nbTransMax-latestB.getNb_trans();
			User user = this.getUser(i);
			String userS = user.user_to_string();
			user.add_money(50.0);
			this.masseMonetaire += 50;
			tl.addTransaction("Coinbase", userS, 50);
			nbTransPast++;
			if(nbTransPast == nbTransReste) {
				this.blockchain.addBlock(tl);
				tl = new Transactions(nbTransMax);
				nbTransPast = 0;
			}
			
		}
		if(nbTransPast != 0) {this.blockchain.addBlock(tl);}
	}
	
	void trans_aleatoire() {
		int nbUsersInDB = this.userDB.getNbUsers();
		if (nbUsersInDB <= 1){
            System.out.println("Il faut au moins deux utilisateurs pour effectuer cette action");
            return;
        }
		int nbBlockRestant = this.blockchain.getNb_block_max() - this.blockchain.getNb_blocs();
		int nbRandTotal = getRandomNumberInRange(1,nbBlockRestant-1);
		int nbTransMaxBlock = this.blockchain.getNb_max_trans();
		int nbTransBlock, randU1, randU2;
		double value;
		User user1, user2;
		String user1S, user2S;
		Transactions tl;
		System.out.print("\n	+*+*+*+*+... %RandomTransactions% ...+*+*+*+*+");
		for(int i = 0; i<nbRandTotal; i++) {
			tl = new Transactions(nbTransMaxBlock);
			nbTransBlock = getRandomNumberInRange(1,nbTransMaxBlock-1);
			System.out.println("\n/[B"+i+"]/");
			for(int j = 0; j<nbTransBlock; j++) {
				
				randU1 = getRandomNumberInRange(1,nbUsersInDB-1);
				randU2 = getRandomNumberInRange(1,nbUsersInDB-1);
				value = getRandomNumberInRange(1,MAX_VALUE_PER_TRANS);
				
				user1 = this.getUser(randU1);
				user2 = this.getUser(randU2);
				user1S = user1.user_to_string();
				user2S = user2.user_to_string();
				if(value<=user1.getWallet()){
					tl.addTransaction(user1S, user2S, value);
					user1.sub_money(value);
					user2.add_money(value);
					System.out.println("(T"+j+")"+user1S+" envoie "+value+" Bnb à "+user2S);
				}
				else {
					System.out.println(user1S+" n'a pas assez d'argent pour envoyer "+value+" Bnb à "+user2S);
				}
			}
			this.blockchain.addBlock(tl);
			tl = new Transactions(nbTransMaxBlock);
		}
	}
	
	
	
	private static int getRandomNumberInRange(int min, int max) {
        if (min > max) {
            throw new IllegalArgumentException("max must be greater than min");
        }

        Random r = new Random();
        return r.nextInt((max - min) + 1) + min;
    }
	
	
	public void add_users_cb(int nbUsers) {
		
		for(int i = 0; i<nbUsers;i++) {//sans le createur
			this.userDB.add_user_to_db();
		}
	}
	
	/**
	 * @return the masseMonetaire
	 */
	public double getMasseMonetaire() {
		return masseMonetaire;
	}
	/**
	 * @return the userDB
	 */
	public UserDB getUserDB() {
		return userDB;
	}
	public User getUser(int index) {
		return userDB.getUserList()[index];
	}
	public void displayAllWallets() {
		System.out.println("\n[Wallets]");
		for(int i = 0; i<this.userDB.getNbUsers();i++) {
			User user = this.getUser(i);
			System.out.println(user.user_to_string()+" {"+user.getWallet()+" Bnb}");
			System.out.println("*--------------*");
		}
	}
	
	
	
}
