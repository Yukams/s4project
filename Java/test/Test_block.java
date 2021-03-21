package test;

import main.Block;
import main.Blockchain;
import main.TransactionUnit;
import main.Transactions;

public class Test_block {

	public static void main(String[] args) {
		System.out.println("Block 1 :");
		
		Transactions tList_1 = new Transactions();
		tList_1.addTransaction("Pierre", "Paul", 0.1);
		tList_1.addTransaction("Paul", "Pierre", 1);
		
		
		Blockchain bc = new Blockchain();
		bc.addBlock(tList_1);
		
		Block b1 = bc.getBlock_list()[1];
		
		int check_index_1 = b1.getIndex();
		if(check_index_1 == 1) {
			System.out.println("	[OK] * index : " + check_index_1);
		} else {
			System.out.println("	[KO] * index : " + check_index_1 + " /// should be '1'");
		}
		
	
		String check_timestamp_1 = b1.getTimestamp();
		System.out.println("	     * timestamp : " + check_timestamp_1);
		
		Block b0 = bc.getBlock_list()[0];
		String check_prev_hash_1 = b0.getPrev_hash();
		if(check_prev_hash_1 == "0") {
			System.out.println("	[OK] * prev_hash : " + check_prev_hash_1);
		} else {
			System.out.println("	[KO] * prev_hash : " + check_prev_hash_1 + " /// should be '0'");
		}
		
		int check_nb_trans_1 = b1.getNb_trans();
		if(check_nb_trans_1 == 2) {
			System.out.println("	[OK] * nb_trans : " + check_nb_trans_1);
		} else {
			System.out.println("	[KO] * nb_trans : " + check_nb_trans_1 + " /// should be '2'");
		}
		
		Transactions check_trans_list_1 = b1.getTrans_list();
		TransactionUnit[] check_trans_list_unit_1 = check_trans_list_1.getTrans_list();
		for(int i = 0; i < check_nb_trans_1; i++) {
			String check_source_1 = check_trans_list_unit_1[i].getSource();
			String check_destination_1 = check_trans_list_unit_1[i].getDestination();
			double check_value_1 = check_trans_list_unit_1[i].getValue();
			int check_randint_1 = check_trans_list_unit_1[i].getRandint();
			String check_string_1 = check_trans_list_unit_1[i].getString();
			
			if(check_source_1 == tList_1.getTrans_list()[i].getSource() && check_destination_1 == tList_1.getTrans_list()[i].getDestination() && check_value_1 == tList_1.getTrans_list()[i].getValue() && check_randint_1 == tList_1.getTrans_list()[i].getRandint() && check_string_1 == tList_1.getTrans_list()[i].getString()) {
				System.out.println("	[OK] * transaction " + (i+1));
			} else {
				System.out.println("	[KO] * transaction " + (i+1));
			}
		}
		
		String check_hash_1 = b1.getHash();
		System.out.println("	     * hash : " + check_hash_1);
		
		int check_nonce_1 = b1.getNonce();
		if(check_nonce_1 == 0) {
			System.out.println("	[OK] * nonce : " + check_nonce_1);
		} else {
			System.out.println("	[KO] * nonce : " + check_nonce_1 + " /// should be '0'");
		}
		
		
		System.out.println("\n\nBlock 2 :");
		
		Transactions tList_2 = new Transactions();
		tList_2.addTransaction("Pierre", "Paul", 0.1);
		tList_2.addTransaction("Paul", "Pierre", 1);
		tList_2.addTransaction("Paul", "Pierre", 3);
		
		bc.addBlock(tList_2);
		Block b2 = bc.getBlock_list()[2];
		
		int check_index_2 = b2.getIndex();
		if(check_index_2 == 2) {
			System.out.println("	[OK] * index : " + check_index_2);
		} else {
			System.out.println("	[KO] * index : " + check_index_2 + " /// should be '2'");
		}
		
	
		String check_timestamp_2 = b2.getTimestamp();
		System.out.println("	     * timestamp : " + check_timestamp_2);
		
		String check_prev_hash_2 = b2.getPrev_hash();
		if(check_prev_hash_2 == check_hash_1) {
			System.out.println("	[OK] * prev_hash : " + check_prev_hash_2);
		} else {
			System.out.println("	[KO] * prev_hash : " + check_prev_hash_2 + " /// should be '" + check_hash_1 +"'");
		}
		
		int check_nb_trans_2 = b2.getNb_trans();
		if(check_nb_trans_2 == 3) {
			System.out.println("	[OK] * nb_trans : " + check_nb_trans_2);
		} else {
			System.out.println("	[KO] * nb_trans : " + check_nb_trans_2 + " /// should be '3'");
		}
		
		Transactions check_trans_list_2 = b2.getTrans_list();
		TransactionUnit[] check_trans_list_unit_2 = check_trans_list_2.getTrans_list();
		for(int i = 0; i < check_nb_trans_2; i++) {
			String check_source_2 = check_trans_list_unit_2[i].getSource();
			String check_destination_2 = check_trans_list_unit_2[i].getDestination();
			double check_value_2 = check_trans_list_unit_2[i].getValue();
			int check_randint_2 = check_trans_list_unit_2[i].getRandint();
			String check_string_2 = check_trans_list_unit_2[i].getString();
			
			if(check_source_2 == tList_2.getTrans_list()[i].getSource() && check_destination_2 == tList_2.getTrans_list()[i].getDestination() && check_value_2 == tList_2.getTrans_list()[i].getValue() && check_randint_2 == tList_2.getTrans_list()[i].getRandint() && check_string_2 == tList_2.getTrans_list()[i].getString()) {
				System.out.println("	[OK] * transaction " + (i+1));
			} else {
				System.out.println("	[KO] * transaction " + (i+1));
			}
		}
		
		String check_hash_2 = b2.getHash();
		System.out.println("	     * hash : " + check_hash_2);
		
		int check_nonce_2 = b2.getNonce();
		if(check_nonce_1 == 0) {
			System.out.println("	[OK] * nonce : " + check_nonce_2);
		} else {
			System.out.println("	[KO] * nonce : " + check_nonce_2 + " /// should be '0'");
		}
	}

}
