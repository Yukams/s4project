package main;

import java.util.Random;

public class UserDB{
	private User userList[];
	private int nbUsers;
	private final int NB_MAX_USERS = 100;
	private Blockchain blockchain;
	
	public UserDB(Blockchain blockchain) {
		this.userList = new User[NB_MAX_USERS];
		this.nbUsers = 0;
		this.blockchain = blockchain;
	}
	
	
	//INIT BD + INIT CREATOR
	public void init_user_db() { //creator
		//creation de la genesis par le creator
		if(blockchain.getNb_blocs() == 1) {
			int nbTransMaxBlock = blockchain.getNb_max_trans(); //nbMax de transaction par block
			Transactions tl = new Transactions(nbTransMaxBlock);
			User Creator = new User(this.nbUsers);//Id = 0 pour Creator
			String userS = Creator.user_to_string();
			this.userList[this.nbUsers] = Creator;
			this.nbUsers++;
			Creator.add_money(50);
			tl.addTransaction("Coinbase", userS, 50);
			
			blockchain.addBlock(tl);							

		}
		else {System.out.println("*** Erreur : Impossible d'initialiser une base de donnée pour la blockchain ***");}
	}
	
	
	
	public void add_user_to_db() {
		if(this.nbUsers<NB_MAX_USERS) {
			this.userList[this.nbUsers] = new User(this.nbUsers);
			this.nbUsers++;
		}
		else {System.out.println("*** Erreur : NB_MAX_USERS atteint ***");}
	}


	/**
	 * @return the userList
	 */
	public User[] getUserList() {
		return userList;
	}


	/**
	 * @return the nbUsers
	 */
	public int getNbUsers() {
		return nbUsers;
	}


	/**
	 * @return the nB_MAX_USERS
	 */
	public int getNB_MAX_USERS() {
		return NB_MAX_USERS;
	}


	/**
	 * @return the blockchain
	 */
	public Blockchain getBlockchain() {
		return blockchain;
	}
	
	
	
	
}
