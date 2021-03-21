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
		this.hash_root = null;
		this.hash = createHash();
		this.nonce = 0;
	}
	
	private String setTimestamp() {
		DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd HH:mm:ss");  
		LocalDateTime now = LocalDateTime.now();  
		return dtf.format(now);
	}
	
	private String createHash() {
		String string = "";
		for(int i = 0; i < nb_trans ; i++) {
			string = string + trans_list.getTrans_list()[i];
		}
		return HashUtil.applySha256(index + timestamp + prev_hash + hash_root + nonce + nb_trans + string);
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

}
