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

	public void addBlock(Transactions trans_list) {
		this.block_list[this.nb_blocs] = new Block(this.nb_blocs, this.block_list[this.nb_blocs-1].getHash(), trans_list);
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
