#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../main/C/transaction.h"
#include "../../main/C/block.h"
#include "../../../utils/C_Packages/Sha256/sha256.h"
#include "../../../utils/C_Packages/Sha256/sha256_utils.h"
#include "test.h"

int main(void) {
    Transaction trans_list[MAX_TRANS];
    int nb_trans = 2;
    trans_list[0] = create_transaction("Pierre", "Paul", 0.1);
    trans_list[1] = create_transaction("Paul", "Pierre", 1);
    int index = 0;
    char prev_hash[SHA256_BLOCK_SIZE*2 + 1] = "0";

    Block b = create_block(index, prev_hash, nb_trans, trans_list);

    /* Nombre transaction */
    int check_nb_trans = getNb_trans(b);
    if(check_nb_trans != nb_trans) {
        printf("[%sKO%s] : Block nb_trans is incorrect ||| more => Block.nb_trans : %d != nb_trans : %d\n", RED, NRM, check_nb_trans, nb_trans);
    } else {
        printf("[%sOK%s] : Block nb_trans is correct\n", GRN, NRM);
    }

    /* Previous hash */
    char* check_prev_hash = getPrev_hash(b);
    if(strcmp(check_prev_hash, prev_hash) != 0) {
        printf("[%sKO%s] : Block prev_hash is incorrect ||| more => Block.prev_hash : %s != prev_hash : %s\n", RED, NRM, check_prev_hash, prev_hash);
    } else {
        printf("[%sOK%s] : Block prev_hash is correct\n", GRN, NRM);
    }

    /* Indice */
    int check_index = getIndex(b);
    if(check_index != index) {
        printf("[%sKO%s] : Block index is incorrect ||| more => Block.index : %d != index : %d\n", RED, NRM, check_index, index);
    } else {
        printf("[%sOK%s] : Block index is correct\n", GRN, NRM);
    }

    free(b);
    return 0;
}
