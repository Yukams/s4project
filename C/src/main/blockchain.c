#include "blockchain.h"

struct blockchain_s {
    int difficulty;
    int nb_blocs;
    Block block_list[NB_BLOCKS];
};


/* PUBLIC */
Blockchain create_blockchain() {
    
    Transactions tList = create_transaction_list();
    
    Block genesis = create_block(0, "0", &tList);
    
    Blockchain blockchain = malloc(sizeof(struct blockchain_s));
    
    if(blockchain == NULL) {
        printf("\n*** Error : malloc block ***\n");
    }

    blockchain->block_list[0] = genesis;
    blockchain->nb_blocs = 1;
    blockchain->difficulty = 4;
    printf("%d sheesh\n",getNb_trans( getTrans_list( getBlock_list(blockchain)[0])));
    return blockchain;
}

void add_block(Blockchain blockchain, Transactions *transaction_list) {
    Block block = create_block(blockchain->nb_blocs, getHash(blockchain->block_list[blockchain->nb_blocs-1]), transaction_list);
    blockchain->block_list[blockchain->nb_blocs] = block;
    blockchain->nb_blocs += 1;
}

void delete_blockchain(Blockchain blockchain) {
    free(blockchain);
}


/* FOR DEBUG PURPOSE */
int getDifficulty(Blockchain blockchain) {
    return blockchain->difficulty;
}

int getNb_blocs(Blockchain blockchain) {
    return blockchain->nb_blocs;
}

Block *getBlock_list(Blockchain blockchain) {
    return blockchain->block_list;
}
