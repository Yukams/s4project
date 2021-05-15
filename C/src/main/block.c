#include "block.h"

/*==================================================================*/
/* STRUCTURE */

struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char timestamp[DATE_LONG]; // la date au moment de la création
    char prev_hash[SHA256_BLOCK_SIZE*2 + 1]; // hash du block précédent dans la chaîne
    Transactions transaction_list; // liste des transactions
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
    char string[MAX_STRING_LENGTH * MAX_TRANS] = "";
    for(int i = 0; i < getNb_trans(b->transaction_list); i++) {
        char trans_string[MAX_STRING_LENGTH];
        strcpy(trans_string, getTransactionString(b->transaction_list, i));
        strcat(string, trans_string);
    }

    char hashString[200 + 140 * MAX_TRANS];

    // Builds the whole string
    sprintf(hashString, "%d %s %s %s %d %d %s", b->index, b->timestamp, b->prev_hash, b->hash_root, b->nonce, getNb_trans(b->transaction_list), string);

    // Transforms into SHA256 string
    char hashRes[200 + 140 * MAX_TRANS];
    char * item = malloc((200 + 140 * MAX_TRANS)*sizeof(char));
    strcpy(item, hashString); // c'est elle
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item

    strcpy(b->hash, hashRes);
}

void delete_block(Block block) {
    delete_transaction_list(block->transaction_list);

    free(block);
}


void calcul_hash_root(Block b) {
    int nb_trans = getNb_trans(getTrans_list(b));
    if (nb_trans==0) {
        strcpy(b->hash_root,"0");
        return;
    }
    char hash_trans[MAX_TRANS][10*SHA256_BLOCK_SIZE+1]; //tableau de chaine de caractere de chaque transaction
    int compteur_arbre = nb_trans;

    // Calcul of hash for each transactions
    for (int i = 0; i < nb_trans; i++) {
        int bufferSize = SHA256_BLOCK_SIZE;
        char hashRes[bufferSize*2 + 1]; // contiendra le hash de la transaction i en hexadécimal
        char item[200 + 140 * MAX_TRANS]; // contiendra la transaction i à hasher

        char * string = getTransactionString(b->transaction_list, i); // string de la transaction i
        strcpy(item, string); // c'est elle
        sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item (i)
        sprintf(hash_trans[i], "%s", hashRes);
    }

    while (compteur_arbre != 1) // tant qu'il ne reste pas qu'une racine {
        if (compteur_arbre % 2 != 0) { //si nombre de transaction ou hash intermédiaire impair
            for (int i = 0; i < compteur_arbre+1; i = i+2) {
                if (i == compteur_arbre) {
                    char * hash_trans_double = hash_trans[i];
                    strcat(hash_trans[i], hash_trans_double);
                } else {
                    strcat(hash_trans[i],hash_trans[i+1]);
                }
                if (i != 0) {
                    strcpy(hash_trans[i/2],hash_trans[i]);
                }
            }
        compteur_arbre = (compteur_arbre+1)/2;
    } else {  //si nombre de transaction ou hash intermédiaire pair
            for (int i = 0; i < compteur_arbre; i=i+2) {
                strcat(hash_trans[i],hash_trans[i+1]);
                if (i != 0) {
                    strcpy(hash_trans[i/2],hash_trans[i]);
                }
        }
        compteur_arbre = (compteur_arbre)/2;
    }

    // Transforms into SHA256 string de la concaténation
    char hashRes[200 + 140 * MAX_TRANS];
    char * item = malloc((200 + 140 * MAX_TRANS)*sizeof(char));
    strcpy(item, hash_trans[0]); 
    sha256ofString((BYTE *)item, hashRes); // hashRes contient maintenant le hash de l'item

    strcpy(b->hash_root, hashRes); // hash_root qui vaut la racine de l'arbre
}

Block create_block(int index, char* prev_hash, Transactions *transaction_list) {
    Block block = malloc(sizeof(struct block_s));
    if(block == NULL) {
        printf("\n*** Error : malloc block ***\n");
    }

    block->index = index;
    strcpy(block->timestamp, getTimeStamp());

    strcpy(block->prev_hash, prev_hash);

    block->transaction_list = *transaction_list;
    
    calcul_hash_root(block);
    
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
    return b->transaction_list;
}

char * getHash_root(Block b) {
    return b->hash_root;
}

char * getHash(Block b) {
    return b->hash;
}

char * getTimestamp(Block b) {
    return b->timestamp;
}

int getNonce(Block b) {
    return b->nonce;
}

void incrementNonce(Block b){
    b->nonce++;
}
