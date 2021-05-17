package main;

public class Blockchain {
	private int difficulty;
    private int nb_blocs;
    private int nb_max_trans;
    private int nb_block_max;
    private Block block_list[];
	
	public Blockchain(int difficulty, int nb_max_max, int nb_block_max) {
		this.nb_blocs = 0;
		this.difficulty = difficulty;
		this.nb_max_trans = nb_max_max;
		this.nb_block_max = nb_block_max;
		this.block_list = new Block[nb_block_max];
		
		addGenesisBlock();
	}
	
	private boolean strncmp(String a,String b,int length) {
		   a = a.substring(0, length);
		   b = b.substring(0, length);

		   return a.compareTo(b) == 0;
		}
	
	
	
	private Block find_good_hash (Block b, int difficulte) {
		String chaine = b.getHash();
		
		if (!strncmp(chaine, "0000000000", difficulte)) {
			
			while (!strncmp(chaine, "0000000000", difficulte)) {
				
				b.incrementNonce();
				
				b.setHash(b.createHash());
				
				chaine =b.getHash();
			}
		}
		return b;
	}
	
	public void addBlock(Transactions trans_list) {
		Block block = new Block(this.nb_blocs, this.block_list[this.nb_blocs-1].getHash(), trans_list);
		int difficulte = this.difficulty;
		
		block = find_good_hash(block, difficulte);
		
		this.block_list[this.nb_blocs] = block;
		this.nb_blocs++;
	}
	
	private void addGenesisBlock() {
		Transactions genesis= new Transactions(this.nb_max_trans);
		genesis.addGenesisTransaction();
		this.block_list[this.nb_blocs] = new Block(0, "0", genesis);
		this.nb_blocs++;
	}

	/**
	 * @return the difficulty
	 */
	public int getDifficulty() {
		return difficulty;
	}

	/**
	 * @return the nb_blocs
	 */
	public int getNb_blocs() {
		return nb_blocs;
	}

	/**
	 * @return the block_list
	 */
	public Block[] getBlock_list() {
		return block_list;
	}

	/**
	 * @return the nb_trans_max
	 */
	public int getNb_max_trans() {
		return nb_max_trans;
	}
	/**
	 * @return nbTransTotal
	 */
	public int getNbTransTotal() {
		int compteur = 0;
		int nbBlocksCurrent = this.getNb_blocs();
		for(int i = 0; i<nbBlocksCurrent;i++) {
			compteur += this.getBlock_list()[i].getNb_trans();
		}
		return compteur;
		
	}

	/**
	 * @return the nb_block_max
	 */
	public int getNb_block_max() {
		return nb_block_max;
	}
}
