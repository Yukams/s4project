#include "block.h"

/*==================================================================*/
/* STRUCTURE */

struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char timestamp[DATE_LONG]; // la date au moment de la création
    char prev_hash[SHA256_BLOCK_SIZE*2 + 1]; // hash du block précédent dans la chaîne
    int nb_trans; // nombre de transactions
    Transaction trans_list[MAX_TRANS]; // liste des transactions
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

    for(int i = 0; i < b->nb_trans; i++) {
        Transaction transaction = b->trans_list[i];
        char *trans_string = getString(transaction);
        strcat(string, trans_string);
    }

    char hashString[200 + 140 * MAX_TRANS] = "";

    // Builds the whole string
    sprintf(hashString, "%d %s %s %s %d %d %s", b->index, b->timestamp, b->prev_hash, b->hash_root, b->nonce, b->nb_trans, string);
    //sprintf(hashString, "%d %s %s %d %s", b->index, b->timestamp, b->prev_hash, b->nonce, string);
    // manque nb_trans et hash_root provoquent des erreurs memoire

    // Transforms into SHA256 string
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
    strcpy(item, hashString); // c'est elle
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item

    strcpy(b->hash, hashRes);
}

void delete_block(Block block) {
    for(int i = 0; i < block->nb_trans; i++) {
        delete_transaction(block->trans_list[i]);
    }

    free(block);
}

Block create_block() {
    Block block = malloc(sizeof(struct block_s));
    if(block == NULL) {
        printf("\n*** Error : malloc block ***\n");
    }
    return block;
}

void init_block(Block block, int index, char* prev_hash, int nb_trans, Transaction *trans_list) {
    block->index = index;
    strcpy(block->timestamp, getTimeStamp());

    strcpy(block->prev_hash, prev_hash);

    block->nb_trans = nb_trans;
    for(int i=0; i<nb_trans; i++) {
        block->trans_list[i] = trans_list[i];
    }
    char *hash_root = "null";
    strcpy(block->hash_root, hash_root); // TO ADD
    block->nonce = 0;

    create_hash(block);
}

/* FOR DEBUG PURPOSE */
int getIndex(Block b) {
    return b->index;
}

char * getPrev_hash(Block b) {
    return b->prev_hash;
}

int getNb_trans(Block b) {
    return b->nb_trans;
}

Transaction * getTrans_list(Block b){
    return b->trans_list;
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
