#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transaction.h"
#include "block.h"
#include "../../../utils/C_Packages/Sha256/sha256.h"
#include "../../../utils/C_Packages/Sha256/sha256_utils.h"

/*==================================================================*/
/* STRUCTURE */

struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char timestamp[DATE_LONG]; // la date au moment de la création
    char prev_hash[SHA256_BLOCK_SIZE*2 + 1]; // hash du block précédent dans la chaîne
    int nb_trans; // nombre de transactions
    Transaction *trans_list; // liste des transactions
    char *hash_root; // hash root de l’arbre de Merkle des transactions
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
    Transaction *trans_list = b->trans_list;

    for(int i = 0; i < b->nb_trans; i++) {
        Transaction transaction = trans_list[i];
        char *trans_string = getString(transaction);
        strcat(string, trans_string);
    }

    // Builds the whole string
    sprintf(string, "%d %s %s %s %s %d %d %s", b->index, b->timestamp, b->prev_hash, b->hash_root, b->hash, b->nonce, b->nb_trans, string);

    // Transforms into SHA256 string
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
    strcpy(item, string); // c'est elle
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item

    strcpy(b->hash, hashRes);
}


Block create_block(int index, char* prev_hash, int nb_trans, Transaction *trans_list) {
    Block block = malloc(sizeof(struct block_s));
    
    block->index = index;
    strcpy(block->timestamp, getTimeStamp());

    strcpy(block->prev_hash, prev_hash);

    block->nb_trans = nb_trans;
    block->trans_list = trans_list;
    block->hash_root = "null"; // TO ADD
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
