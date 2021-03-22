#include "block.h"

/*==================================================================*/
/* STRUCTURE */

struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char timestamp[DATE_LONG]; // la date au moment de la création
    char prev_hash[SHA256_BLOCK_SIZE*2 + 1]; // hash du block précédent dans la chaîne
    Transactions *transaction_list; // liste des transactions
    char hash_root[SHA256_BLOCK_SIZE*2 + 1]; // hash root de l’arbre de Merkle des transactions
    char hash[SHA256_BLOCK_SIZE*2 + 1]; // hash du block courant
    int nonce; //
};

/*==================================================================*/
/* FONCTIONS */

char * getTimeStamp() {
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}


void create_hash(Block b) {
    // Constructs a string from each of transaction's string
    char string[MAX_STRING_LENGTH * MAX_TRANS];
    for(int i = 0; i < getNb_trans(*b->transaction_list); i++) {
        char trans_string[MAX_STRING_LENGTH];
        strcpy(trans_string, getTransactionString(*b->transaction_list, i));
        strcat(string, trans_string);
    }

    char hashString[200 + 140 * MAX_TRANS];

    // Builds the whole string
    sprintf(hashString, "%d %s %s %s %d %d %s", b->index, b->timestamp, b->prev_hash, b->hash_root, b->nonce, getNb_trans(*b->transaction_list), string);

    // Transforms into SHA256 string
    char hashRes[200 + 140 * MAX_TRANS];
    char * item = malloc((200 + 140 * MAX_TRANS)*sizeof(char));
    strcpy(item, hashString); // c'est elle
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item

    strcpy(b->hash, hashRes);
}

void delete_block(Block block) {
    delete_transaction_list(*block->transaction_list);

    free(block);
}

Block create_block(int index, char* prev_hash, Transactions *transaction_list) {
    Block block = malloc(sizeof(struct block_s));
    if(block == NULL) {
        printf("\n*** Error : malloc block ***\n");
    }

    block->index = index;
    strcpy(block->timestamp, getTimeStamp());

    strcpy(block->prev_hash, prev_hash);

    block->transaction_list = transaction_list;

    char *hash_root = "null";
    strcpy(block->hash_root, hash_root); // TO ADD
    block->nonce = 0;

    create_hash(block);

    return block;
}

/* FOR DEBUG PURPOSE */
int getIndex(Block b) {
    return b->index;
}

char * getPrev_hash(Block b) {
    return b->prev_hash;
}

Transactions getTrans_list(Block b){
    return *b->transaction_list;
}

char * getHash_root(Block b) {
    return b->hash_root;
}

char * getHash(Block b) {
    return b->hash;
}

int getNonce(Block b) {
    return b->nonce;
}
