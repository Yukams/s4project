#include "blockchain.h"

struct blockchain_s {
    int difficulty;
    int nb_blocs;
    int max_size;
    Block *block_list;
};


/* PUBLIC */
Blockchain create_blockchain(int difficulty, int max_size) {
    Transactions tList = create_transaction_list();
    
    Block genesis = create_block(0, "0", &tList);

    Blockchain blockchain = malloc(sizeof(struct blockchain_s));
    if(blockchain == NULL) {
        printf("\n*** Error : malloc blockchain ***\n");
    }
    blockchain->block_list = malloc(max_size * sizeof(Block *));
    if(blockchain->block_list == NULL) {
        printf("\n*** Error : malloc blockchain block list ***\n");
    }
    printf("ok1\n");
    blockchain->difficulty = difficulty;
    printf("ok2\n");
    blockchain->block_list[0] = genesis;
    printf("ok3\n");
    blockchain->nb_blocs = 1;
    printf("ok4\n");
    return blockchain;
}

void calcul_hash(Block b) {
    // Constructs a string from each of transaction's string
    char string[MAX_STRING_LENGTH * MAX_TRANS];
    int nb_trans =getNb_trans((getTrans_list(b)));

    for(int i = 0; i < nb_trans; i++) {
        char *trans_string = getTransactionString(getTrans_list(b), i);
        strcat(string, trans_string);
    }

    char hashString[200 + 140 * MAX_TRANS] = "";

    // Builds the whole string
    sprintf(hashString, "%d %s %s %s %d %d %s",getIndex(b),getTimestamp(b),getPrev_hash(b),getHash_root(b),getNonce(b),nb_trans, string);

    // Transforms into SHA256 string
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    char item[200 + 140 * MAX_TRANS]; // contiendra la chaîne à hasher
    
    strcpy(item, hashString); // c'est elle 
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item
    strcpy(getHash(b), hashRes);
}

void find_good_hash (Block b, int difficulte) {

    //vérification du hash
    char* chaine=getHash(b);

    if(strncmp(chaine, "0000000000", difficulte)!=0){   //le hash ne convient pas
        while (strncmp(chaine, "0000000000",difficulte)!=0)
        {
            incrementNonce(b);
            calcul_hash(b); 
            chaine=getHash(b);
        }
    }
   
}

void add_block(Blockchain blockchain, Transactions *transaction_list) {
    printf("gougaga1");
    if(blockchain->nb_blocs != blockchain->max_size) {
        printf("gougaga2");
        Block block = create_block(blockchain->nb_blocs, getHash(blockchain->block_list[blockchain->nb_blocs - 1]),
                                   transaction_list);
        printf("gougaga2bis");
        if (getIndex(block) != 0) {
            find_good_hash(block, blockchain->difficulty);
        }
        printf("gougaga3");
        blockchain->block_list[blockchain->nb_blocs] = block;
        printf("gougaga4");
        blockchain->nb_blocs += 1;
        printf("gougaga5");
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
