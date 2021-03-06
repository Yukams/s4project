//
// Created by Valentin on 06/03/2021.
//

#ifndef PROJET_TRANSACTION_H
#define PROJET_TRANSACTION_H

typedef struct block_s {
    int index; // numéro du block dans la chaîne (le génésis est numéroté zéro)
    char timestamp[]; // chaîne de caractères = la date au moment de la création
    char prev_hash[]; // hash du block précédent dans la chaîne
    int nb_trans; // nombre de transactions
    int trans_list[]; // liste des transactions
    char hash_root[]; // hash root de l’arbre de Merkle des transactions
    char hash[]; // hash du block courant
    int nonce; //
} block_t;

#endif //PROJET_TRANSACTION_H
