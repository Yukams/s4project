#include "transaction.h"
#include "block.h"
#include "../../../utils/C_Packages/Sha256/sha256.h"
#include "../../../utils/C_Packages/Sha256/sha256_utils.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DATE_LONG 30

/*==================================================================*/
/* STRUCTURE */

struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char timestamp[DATE_LONG]; // la date au moment de la création
    char prev_hash[SHA256_BLOCK_SIZE*2 + 1]; // hash du block précédent dans la chaîne
    int nb_trans; // nombre de transactions
    Transaction trans_list[MAX_TRANS]; // liste des transactions
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
    char string[MAX_STRING_LENGTH * MAX_TRANS] = "";
    for(int i = 0; i < b->nb_trans; i++) {
        strcat(string, b->trans_list[i]);
    }
    sprintf(string, "%d%s%s%s%s%d%d%s", b->index, b->timestamp, b->prev_hash, b->hash_root, b->hash, b->nonce, b->nb_trans, string);

    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
    strcpy(item, string); // c'est elle
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item

    strcpy(b->hash, hashRes);
}

Block create_block(int index, char* prev_hash, int nb_trans, Transaction trans_list) {
    Block block = malloc(sizeof(struct block_s));
    
    block->index = index;
    strcpy(block->timestamp, getTimeStamp());

    if(index > 0) {strcpy(block->prev_hash, prev_hash);}
    else {block->prev_hash = "0";}

    block->nb_trans = nb_trans;
    block->trans_list = trans_list;
    block->hash_root = NULL; // TO ADD
    block->nonce = 0;

    create_hash(block);

    return block;
}