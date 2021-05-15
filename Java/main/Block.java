package main;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import utils.HashUtil;

public class Block {
	private int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
	private String timestamp; // la date au moment de la création
	private String prev_hash; // hash du block précédent dans la chaîne
	private int nb_trans; // nombre de transactions
	private Transactions trans_list; // liste des transactions
	private String hash_root; // hash root de l’arbre de Merkle des transactions
	private String hash; // hash du block courant
	private int nonce; //

	protected Block(int index, String prev_hash, Transactions trans_list) {
		this.index = index;
		this.timestamp = setTimestamp();
		this.prev_hash = prev_hash;
		this.nb_trans = trans_list.getNb_trans();
		this.trans_list = trans_list;
		this.setHash_root(calcul_hash_root());
		this.setHash(createHash());
		this.nonce = 0;
	}
	
	private String setTimestamp() {
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");  
		LocalDateTime now = LocalDateTime.now();  
		return dtf.format(now);
	}
	
	protected String createHash() {
		String string = "";
		for(int i = 0; i < nb_trans ; i++) {
			string = string + trans_list.getTrans_list()[i];
		}
		return HashUtil.applySha256(index + timestamp + prev_hash + hash_root + nonce + nb_trans + string);
	}
	
	
	
	private String calcul_hash_root() {
		if (this.nb_trans == 0) {
			
			return "0";
		}
		String [] hash_trans= new String [10];
		int compteur_arbre = this.nb_trans;
		
		String hashRes;
		String transaction;
		for(int i = 0; i < nb_trans ; i++) {
			transaction = "" + trans_list.getTrans_list()[i];
			hashRes = HashUtil.applySha256(transaction);
			hash_trans[i]=hashRes;
		}
		
		while (compteur_arbre != 1) {
			if (compteur_arbre % 2 != 0) {
				for (int i = 0; i < compteur_arbre; i=i+2) {
					if (i == compteur_arbre) {
						hash_trans[i]=hash_trans[i]+hash_trans[i];
					} else {
						hash_trans[i]=hash_trans[i]+hash_trans[i+1];
					}
					if (i != 0) {
						hash_trans[i/2]=hash_trans[i];
					}
				}
				compteur_arbre= (compteur_arbre+1)/2;
			}
			
			else {
				for (int i = 0; i < compteur_arbre; i=i+2) {
	                
	                hash_trans[i]=hash_trans[i]+hash_trans[i+1];
	                
	                if (i != 0) {
	                    
	                    hash_trans[i/2]=hash_trans[i];
	                }
	        }
	        compteur_arbre = (compteur_arbre)/2;
			}
		}
		String hashFinal;
		hashFinal=HashUtil.applySha256(hash_trans[0]);
		return hashFinal;
		
	}
	
	/**
	 * @return the timestamp
	 */
	public String getTimestamp() {
		return timestamp;
	}
	
	

	/**
	 * @return the index
	 */
	public int getIndex() {
		return index;
	}

	/**
	 * @return the prev_hash
	 */
	public String getPrev_hash() {
		return prev_hash;
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
	public Transactions getTrans_list() {
		return trans_list;
	}

	/**
	 * @return the hash_root
	 */
	public String getHash_root() {
		return hash_root;
	}

	/**
	 * @return the hash
	 */
	public String getHash() {
		return hash;
	}

	/**
	 * @return the nonce
	 */
	public int getNonce() {
		return nonce;
	}
	
	public void incrementNonce() {
		this.nonce = this.nonce+1;
	}

	public void setHash(String hash) {
		this.hash = hash;
	}
	
	public void setHash_root(String hash) {
		this.hash_root = hash;
	}

}
