package main;

public class Blockchain {
	private int difficulty;
    private int nb_blocs;
    private Block block_list[];
	
	public Blockchain() {
		this.nb_blocs = 0;
		this.difficulty = 4;
		this.block_list = new Block[100];
		
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
		this.block_list[this.nb_blocs] = new Block(0, "0", new Transactions());
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

}
