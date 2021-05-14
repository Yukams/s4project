#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main/transaction.h"
#include "../main/block.h"
#include "../../utils/C_Packages/Sha256/sha256.h"
#include "../../utils/C_Packages/Sha256/sha256_utils.h"
#include "test.h"

int main(void) {
    /* BLOCK 1 */
    printf("* ==== BLOCK 1 ==== *\n");
    
    Transactions trans_list_1 = create_transaction_list();
    int nb_trans_1 = 4;
    add_transaction(trans_list_1, "Pierre", "Paul", 0.1);
    add_transaction(trans_list_1, "Paul", "Pierre", 1);
    add_transaction(trans_list_1, "Pierre", "Paul", 0.1);
    add_transaction(trans_list_1, "Paul", "Pierre", 1);
    int index_1 = 0;
    char prev_hash_1[SHA256_BLOCK_SIZE*2 + 1] = "0";

    Block b1 = create_block(index_1, prev_hash_1, &trans_list_1);

    /* Nombre transaction */
    int check_nb_trans_1 = getNb_trans(trans_list_1);
    if(check_nb_trans_1 != nb_trans_1) {
        printf("[%sKO%s] : Block nb_trans is incorrect ||| more => Block.nb_trans : %d != nb_trans : %d\n", RED, NRM, check_nb_trans_1, nb_trans_1);
    } else {
        printf("[%sOK%s] : Block nb_trans is correct\n", GRN, NRM);
    }

    /* Previous hash */
    char* check_prev_hash_1 = getPrev_hash(b1);
    if(strcmp(check_prev_hash_1, prev_hash_1) != 0) {
        printf("[%sKO%s] : Block prev_hash is incorrect ||| more => Block.prev_hash : %s != prev_hash : %s\n", RED, NRM, check_prev_hash_1, prev_hash_1);
    } else {
        printf("[%sOK%s] : Block prev_hash %s is correct\n", GRN, NRM, check_prev_hash_1);
    }

    /* Indice */
    int check_index_1 = getIndex(b1);
    if(check_index_1 != 0) {
        printf("[%sKO%s] : Block index is incorrect ||| more => Block.index : %d != index : %d\n", RED, NRM, check_index_1, 0);
    } else {
        printf("[%sOK%s] : Block index is correct\n", GRN, NRM);
    }

    /* Transactions */
    Transactions check_trans_list_1 = getTrans_list(b1);
    for(int i = 0; i < nb_trans_1; i++) {
        if(strcmp(getTransactionSource(check_trans_list_1, i), getTransactionSource(trans_list_1, i)) != 0 || strcmp(getTransactionDestination(check_trans_list_1, i), getTransactionDestination(trans_list_1, i)) != 0 || getTransactionRandInt(check_trans_list_1, i) != getTransactionRandInt(trans_list_1, i) || getTransactionSatoBnbValue(check_trans_list_1, i) != getTransactionSatoBnbValue(trans_list_1, i) || strcmp(getTransactionString(check_trans_list_1, i), getTransactionString(trans_list_1, i)) != 0) {
            printf("[%sKO%s] : Block trans_list is incorrect ||| more => Block.trans_list[%d] != trans_list[%d]\n", RED, NRM, i, i);
        } else {
            printf("[%sOK%s] : Block trans_list %d is correct\n", GRN, NRM, i+1);
        }
    }

    /* Nonce */
    int check_nonce_1 = getNonce(b1);
    if(check_nonce_1 != 0) {
        printf("[%sKO%s] : Block nonce is incorrect ||| more => Block.nonce : %d != nonce : %d\n", RED, NRM, check_nonce_1, 0);
    } else {
        printf("[%sOK%s] : Block nonce is correct\n", GRN, NRM);
    }

    // Hash root
    char * check_hash_root_1 = getHash_root(b1);
    if(strcmp(check_hash_root_1, getHash_root(b1)) != 0) {
        printf("[%sKO%s] : Block hash_root is incorrect ||| more => Block.hash_root : %s != hash_root : %s\n", RED, NRM, check_hash_root_1, getHash_root(b1));
    } else {
        printf("[%sOK%s] : Block hash_root %s is correct\n", GRN, NRM, check_hash_root_1);
    }

    // Hash
    char hash_1[SHA256_BLOCK_SIZE*2 + 1];
    char *hash = getHash(b1);
    strcpy(hash_1, hash);
    printf("[%sOK%s] : Block hash %s\n", GRN, NRM, hash_1);

    // BLOCK 2
    printf("\n\n* ==== BLOCK 2 ==== *\n");

    Transactions trans_list_2 = create_transaction_list();
    int nb_trans_2 = 3;
    add_transaction(trans_list_2, "Jean", "Denis", 0.5);
    add_transaction(trans_list_2, "Remi", "Louis", 2);
    add_transaction(trans_list_2, "Louis", "Denis", 0.0005);
    int index_2 = 1;
    char prev_hash_2[SHA256_BLOCK_SIZE*2 + 1];
    strcpy(prev_hash_2, hash_1);

    Block b2 = create_block(index_2, prev_hash_2, &trans_list_2);

    // Transactions
    Transactions check_trans_list_2 = getTrans_list(b2);
    for(int i = 0; i < nb_trans_2; i++) {
        if(strcmp(getTransactionSource(check_trans_list_2, i), getTransactionSource(trans_list_2, i)) != 0 || strcmp(getTransactionDestination(check_trans_list_2, i), getTransactionDestination(trans_list_2, i)) != 0 || getTransactionRandInt(check_trans_list_2, i) != getTransactionRandInt(trans_list_2, i) || getTransactionSatoBnbValue(check_trans_list_2, i) != getTransactionSatoBnbValue(trans_list_2, i) || strcmp(getTransactionString(check_trans_list_2, i), getTransactionString(trans_list_2, i)) != 0) {
            printf("[%sKO%s] : Block trans_list is incorrect ||| more => Block.trans_list[%d] != trans_list[%d]\n", RED, NRM, i, i);
        } else {
            printf("[%sOK%s] : Block trans_list %d is correct\n", GRN, NRM, i+1);
        }
    }

    // Previous hash
    char* check_prev_hash_2 = getPrev_hash(b2);
    if(strcmp(check_prev_hash_2, prev_hash_2) != 0) {
        printf("[%sKO%s] : Block prev_hash is incorrect ||| more => Block.prev_hash : %s != prev_hash : %s\n", RED, NRM, check_prev_hash_2, prev_hash_2);
    } else {
        printf("[%sOK%s] : Block prev_hash %s is correct\n", GRN, NRM, check_prev_hash_2);
    }

    // Indice
    int check_index_2 = getIndex(b2);
    if(check_index_2 != 1) {
        printf("[%sKO%s] : Block index is incorrect ||| more => Block.index : %d != index : %d\n", RED, NRM, check_index_2, 1);
    } else {
        printf("[%sOK%s] : Block index is correct\n", GRN, NRM);
    }

    // Nonce
    int check_nonce_2 = getNonce(b2);
    if(check_nonce_2 != getNonce(b2)) {
        printf("[%sKO%s] : Block nonce is incorrect ||| more => Block.nonce : %d != nonce : %d\n", RED, NRM, check_nonce_2, getNonce(b2));
    } else {
        printf("[%sOK%s] : Block nonce is correct\n", GRN, NRM);
    }

    // Hash root
    char * check_hash_root_2 = getHash_root(b2);
    if(strcmp(check_hash_root_2, getHash_root(b2)) != 0) {
        printf("[%sKO%s] : Block hash_root is incorrect ||| more => Block.hash_root : %s != hash_root : %s\n", RED, NRM, check_hash_root_2, getHash_root(b1));
    } else {
        printf("[%sOK%s] : Block hash_root %s is correct\n", GRN, NRM, check_hash_root_2);
    }

    /* Hash */
    char hash_2[SHA256_BLOCK_SIZE*2 + 1];
    char *hash2 = getHash(b2);
    strcpy(hash_2, hash2);
    printf("[%sOK%s] : Block hash %s\n", GRN, NRM, hash_2);


    delete_block(b1);
    delete_block(b2);
    return 0;
}
