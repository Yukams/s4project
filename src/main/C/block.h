//
// Created by Valentin on 06/03/2021.
//

#ifndef PROJET_TRANSACTION_H
#define PROJET_TRANSACTION_H
#define MAX_VALUE
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Blocs
 */

typedef struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char *timestamp; // la date au moment de la création
    char *prev_hash; // hash du block précédent dans la chaîne
    int nb_trans; // nombre de transactions
    trans_t *trans_list; // liste des transactions
    char *hash_root; // hash root de l’arbre de Merkle des transactions
    char *hash; // hash du block courant
    int nonce; //
} block_t;

// Returns block's creation time date
char * getTimeStamp();


/**
 * Transactions
 */

typedef struct trans_s {
    char *source;
    char *destination;
    int randint;
    long int value; // En SatoBNB
} trans_t;


// Initialise une transaction
trans_t init_trans(char * source, char * destination, int value);


// Converts Bnb value to SatoBnbValue (x10^8)
int toSatoBnb(int value);

#endif //PROJET_TRANSACTION_H
