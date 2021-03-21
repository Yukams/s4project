#include "blockchain.h"

struct blockchain_s {
    int difficulty;
    int nb_blocs;
    Block block_list[NB_BLOCKS];
};

/* PUBLIC */
Blockchain create_blockchain() {
    Blockchain blockchain = malloc(sizeof(struct blockchain_s));
    if(blockchain == NULL) {
        printf("\n*** Error : malloc block ***\n");
    }
    return blockchain;
}

void init_blockchain(Blockchain blockchain) {
    blockchain->nb_blocs = 0;

    // Création du Génesis
    Block genesis = create_block();
    init_block(genesis, 0, "0", 0, NULL);
    add_block(blockchain, genesis);

    blockchain->difficulty = 4;
}

void add_block(Blockchain blockchain, Block block) {
    blockchain->block_list[blockchain->nb_blocs] = block;
    blockchain->nb_blocs += 1;
}

void delete_blockchain(Blockchain blockchain) {
    for(int i = 0; i < blockchain->nb_blocs; i++) {
        delete_block(blockchain->block_list[i]);
    }

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
