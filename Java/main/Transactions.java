package main;

public class Transactions {
	private int nb_trans; // nombre de transactions
	private TransactionUnit trans_list[]; // liste des transactions

	public Transactions() {
		this.nb_trans = 0;
		this.trans_list = new TransactionUnit[10];
	}
	
	public void addTransaction(String source, String destination, double value) {
		this.trans_list[this.nb_trans] = new TransactionUnit(source, destination, value);
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
