#include "blockchain.h"

struct blockchain_s {
    int difficulty;
    int nb_blocs;
    int max_size;
    Block *block_list; //[b1][b2][b3][b4]
};

/* PUBLIC */
Blockchain create_blockchain(int difficulty, int max_size) {
    Transactions tList = create_transaction_list();
    add_transaction_genesis(tList);
    
    Block genesis = create_block(0, "0", &tList);

    Blockchain blockchain = malloc(sizeof(struct blockchain_s));
    blockchain->block_list = malloc(max_size * sizeof(Block));
    if(blockchain == NULL) {
        printf("\n*** Error : malloc blockchain ***\n");
    }
    blockchain->difficulty = difficulty;
    blockchain->max_size = max_size;
    blockchain->block_list[0] = genesis;
    blockchain->nb_blocs = 1;
    
    return blockchain;
}

void find_good_hash (Block b, int difficulty) {
    //vérification du hash
    char chaine[SHA256_BLOCK_SIZE*2 + 1];
    strcpy(chaine, getHash(b));

    if(strncmp(chaine, "0000000000", difficulty)!=0){   //le hash ne convient pas
        while (strncmp(chaine, "0000000000",difficulty)!=0)
        {
            incrementNonce(b);
            create_hash(b);
            strcpy(chaine, getHash(b));
        }
    }
}

void add_block(Blockchain blockchain, Transactions *transaction_list) {
    if(blockchain->nb_blocs != blockchain->max_size) {
        Block block = create_block(blockchain->nb_blocs, getHash(blockchain->block_list[blockchain->nb_blocs - 1]),
                                   transaction_list);
        if (getIndex(block) != 0) {
            //find_good_hash(block, blockchain->difficulty);
        }
        blockchain->block_list[blockchain->nb_blocs] = block;
        blockchain->nb_blocs += 1;
    }
}

void delete_blockchain(Blockchain blockchain) {
    free(blockchain);
}


/* FOR DEBUG PURPOSE */
int getDifficulty(Blockchain blockchain) {
    return blockchain->difficulty;
}

int getMax_size(Blockchain blockchain) {
    return blockchain->max_size;
}

int getNb_blocs(Blockchain blockchain) {
    return blockchain->nb_blocs;
}

Block *getBlock_list(Blockchain blockchain) {
    return blockchain->block_list;
}
