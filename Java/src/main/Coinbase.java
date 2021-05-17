package main;

import java.util.Random;

public class Coinbase { //super utilisateur coinbase
	
	private int masseMonetaire;
	private UserDB userDB;
	protected Blockchain blockchain;
	
	public Coinbase(Blockchain blockchain) {
		this.masseMonetaire = 0;
		this.userDB = new UserDB(blockchain);
		this.userDB.init_user_db();
		this.blockchain = blockchain; 
	}
	
	public void helicopterMoney() {
		int nbUsers = this.userDB.getNbUsers();
		int nbBlockChain,nbTransReste;
		int nbTransPast = 0;
		int nbTransMax = this.blockchain.getNb_max_trans();
		Block latestB;
		
		Transactions tl = new Transactions(nbTransMax);
		for(int i = 1; i< nbUsers; i++){
			
			nbBlockChain = this.blockchain.getNb_blocs(); //nb block de la bc
			latestB = this.blockchain.getBlock_list()[nbBlockChain-1];
			nbTransReste = nbTransMax-latestB.getNb_trans();
			User user = this.getUser(i);
			String userS = user.user_to_string();
			user.add_money(50);
			tl.addTransaction("Coinbase", userS, 50);
			nbTransPast++;
			if(nbTransPast == nbTransReste) {
				System.out.println("YOO");
				this.blockchain.addBlock(tl);
				tl = new Transactions(nbTransMax);
				nbTransPast = 0;
			}
		}
		if(nbTransPast != 0) {this.blockchain.addBlock(tl);}
	}
	
	private static int getRandomNumberInRange(int min, int max) {
        if (min >= max) {
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
	public int getMasseMonetaire() {
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
		for(int i = 0; i<this.userDB.getNbUsers();i++) {
			User user = this.getUser(i);
			System.out.println(user.user_to_string()+" {"+user.getWallet()+"} Bnb");
		}
	}
	
	
	
}
