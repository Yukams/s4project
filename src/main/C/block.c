#include "block.h"
#include "transaction.h"
#include <time.h>

/*==================================================================*/
/* STRUCTURE */

struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char *timestamp; // la date au moment de la création
    char *prev_hash; // hash du block précédent dans la chaîne
    int nb_trans; // nombre de transactions
    Transaction *trans_list; // liste des transactions
    char *hash_root; // hash root de l’arbre de Merkle des transactions
    char *hash; // hash du block courant
    int nonce; //
};

/*==================================================================*/
/* FONCTIONS */

char * getTimeStamp() {
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}