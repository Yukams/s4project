package main;

public class Transactions {
	private int nb_trans; // nombre de transactions
	private TransactionUnit trans_list[]; // liste des transactions

	public Transactions(int nb_transactions_max) { //nb trans max par block
		this.nb_trans = 0;
		this.trans_list = new TransactionUnit[nb_transactions_max];
	}
	
	public void addTransaction(String source, String destination, double value) {
		this.trans_list[this.nb_trans] = new TransactionUnit(source, destination, value);
		this.nb_trans++;
	}

	public void addGenesisTransaction() {
		this.trans_list[0]= new TransactionUnit();
		this.nb_trans++;
	}
	
	/**
	 * @return the nb_trans
	 */
	public int getNb_trans() {
		return nb_trans;
	}

	/**
	 * @return the trans_list
	 */
	public TransactionUnit[] getTrans_list() {
		return trans_list;
	}
	
	
}
