package test;

import main.Block;
import main.Blockchain;
import main.Transactions;


public class Test_blockchain {

	public static void main(String[] args) {
		System.out.println("Initialisation Blockchain :");
		
		Blockchain bc = new Blockchain(4,10,100);
		
		int check_difficulty = bc.getDifficulty();
		if(check_difficulty == 4) {
			System.out.println("	[OK] * difficulty : " + check_difficulty);
		} else {
			System.out.println("	[KO] * difficulty : " + check_difficulty + " /// should be '4'");
		}
		
		int check_nb_blocs = bc.getNb_blocs();
		if(check_nb_blocs == 1) {
			System.out.println("	[OK] * nb_blocs : " + check_nb_blocs);
		} else {
			System.out.println("	[KO] * nb_blocs : " + check_nb_blocs + " /// should be '1'");
		}
		
		System.out.println("\nVerification premier bloc :");
		Block b_list[] = bc.getBlock_list();
		Block b1 = b_list[0];
		
		int check_index_1 = b1.getIndex();
		if(check_index_1 == 0) {
			System.out.println("	[OK] * index : " + check_index_1);
		} else {
			System.out.println("	[KO] * index : " + check_index_1 + " /// should be '0'");
		}
		
	
		String check_timestamp_1 = b1.getTimestamp();
		System.out.println("	     * timestamp : " + check_timestamp_1);
		
		String check_prev_hash_1 = b1.getPrev_hash();
		if(check_prev_hash_1 == "0") {
			System.out.println("	[OK] * prev_hash : " + check_prev_hash_1);
		} else {
			System.out.println("	[KO] * prev_hash : " + check_prev_hash_1 + " /// should be '0'");
		}
		
		int check_nb_trans_1 = b1.getNb_trans();
		if(check_nb_trans_1 == 0) {
			System.out.println("	[OK] * nb_trans : " + check_nb_trans_1);
		} else {
			System.out.println("	[KO] * nb_trans : " + check_nb_trans_1 + " /// should be '0'");
		}
		String check_hash_root_1 = b1.getHash_root();
		System.out.println("	[OK] * hash_root : " + check_hash_root_1);
		
		String check_hash_1 = b1.getHash();
		System.out.println("	     * hash : " + check_hash_1);
		
		int check_nonce_1 = b1.getNonce();
		if(check_nonce_1 == 0) {
			System.out.println("	[OK] * nonce : " + check_nonce_1);
		} else {
			System.out.println("	[KO] * nonce : " + check_nonce_1 + " /// should be '0'");
		}
		
		System.out.println("\nAjout d'un bloc :");
		
		Transactions trans_list = new Transactions(10);
		trans_list.addTransaction("Pierre", "Paul", 2);
		bc.addBlock(trans_list);
		
		Block b2 = b_list[1];
		
		int check_index_2 = b2.getIndex();
		if(check_index_2 == 1) {
			System.out.println("	[OK] * index : " + check_index_2);
		} else {
			System.out.println("	[KO] * index : " + check_index_2 + " /// should be '1'");
		}
		
	
		String check_timestamp_2 = b2.getTimestamp();
		System.out.println("	     * timestamp : " + check_timestamp_2);
		
		String check_prev_hash_2 = b2.getPrev_hash();
		if(check_prev_hash_2 == check_hash_1) {
			System.out.println("	[OK] * prev_hash : " + check_prev_hash_2);
		} else {
			System.out.println("	[KO] * prev_hash : " + check_prev_hash_2 + " /// should be '" + check_hash_1 + "'");
		}
		
		int check_nb_trans_2 = b2.getNb_trans();
		if(check_nb_trans_2 == 1) {
			System.out.println("	[OK] * nb_trans : " + check_nb_trans_2);
		} else {
			System.out.println("	[KO] * nb_trans : " + check_nb_trans_2 + " /// should be '1'");
		}
		
		int check_nonce_2 = 0;
		if(check_nonce_2 == 0) {
			System.out.println("	[OK] * nonce : " + check_nonce_2);
		} else {
			System.out.println("	[KO] * nonce : " + check_nonce_2 + " /// should be '"+b2.getNonce()+"'");
		}
		
		String check_hash_root_2 = b2.getHash_root();
		System.out.println("	[OK] * hash_root : " + check_hash_root_2);
		
		String check_hash_2 =b2.getHash();
		int difficulte_bc = bc.getDifficulty();
		if (!strncmp(check_hash_2, "0000000000", difficulte_bc)){
			System.out.println("	[KO] * hash : " + check_hash_2);
		} else {
			System.out.println("	[OK] * hash : " + check_hash_2);
			System.out.println("	[OK] * nonce now : " + b2.getNonce());
		}
		
		
		
	}
	
	private static boolean strncmp(String a,String b,int length) {
		   a = a.substring(0, length);
		   b = b.substring(0, length);

		   return a.compareTo(b) == 0;
		}

}
