package main;

public class User {
	private int identifiant;
	double wallet;
	
	public User(int identifiant) {
		this.identifiant = identifiant;
		this.wallet = 0;
	}
	
	public String user_to_string() {
		return "User"+Integer.toString(this.identifiant);
	}

	public void add_money(int value) {
		this.wallet += value;
	}
	
	/**
	 * @return the identifiant
	 */
	public int getIdentifiant() {
		return identifiant;
	}

	/**
	 * @return the wallet
	 */
	public double getWallet() {
		return wallet;
	}
	
	
	
	
}
