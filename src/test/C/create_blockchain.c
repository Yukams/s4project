#include "../../main/C/blockchain.h"
#include "test.h"

int main(void) {
    Blockchain bc = create_blockchain();
    init_blockchain(bc);

    /* BLOCKCHAIN INITIALISATION VERIFICATION */
    printf("* ==== INITIALISATION BLOCKCHAIN ==== *\n");

    int check_difficulty_1 = getDifficulty(bc);
    if(check_difficulty_1 != 4) {
        printf("[%sKO%s] : Blockchain difficulty is incorrect ||| more => Blockchain.difficulty : %d != difficulty : %d\n", RED, NRM, check_difficulty_1, 4);
    } else {
        printf("[%sOK%s] : Blockchain difficulty is correct\n", GRN, NRM);
    }

    int check_nb_blocs_1 = getNb_blocs(bc);
    if(check_nb_blocs_1 != 1) {
        printf("[%sKO%s] : Blockchain nb_blocs is incorrect ||| more => Blockchain.nb_blocs : %d != nb_blocs : %d\n", RED, NRM, check_nb_blocs_1, 1);
    } else {
        printf("[%sOK%s] : Blockchain nb_blocs is correct\n", GRN, NRM);
    }

    // Verification du bloc
    Block *block_list = getBlock_list(bc);
    Block b1 = block_list[0];

    /* Nombre transaction */
    int check_nb_trans_1 = getNb_trans(b1);
    if(check_nb_trans_1 != 0) {
        printf("[%sKO%s] : Block nb_trans is incorrect ||| more => Block.nb_trans : %d != nb_trans : %d\n", RED, NRM, check_nb_trans_1, 0);
    } else {
        printf("[%sOK%s] : Block nb_trans is correct\n", GRN, NRM);
    }

    /* Previous hash */
    char* check_prev_hash_1 = getPrev_hash(b1);
    if(strcmp(check_prev_hash_1, "0") != 0) {
        printf("[%sKO%s] : Block prev_hash is incorrect ||| more => Block.prev_hash : %s != prev_hash : %s\n", RED, NRM, check_prev_hash_1, "0");
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

    /* Nonce */
    int check_nonce_1 = getNonce(b1);
    if(check_nonce_1 != 0) {
        printf("[%sKO%s] : Block nonce is incorrect ||| more => Block.nonce : %d != nonce : %d\n", RED, NRM, check_nonce_1, 0);
    } else {
        printf("[%sOK%s] : Block nonce is correct\n", GRN, NRM);
    }

    /* Hash */
    char hash_1[SHA256_BLOCK_SIZE*2 + 1];
    char *hash = getHash(b1);
    strcpy(hash_1, hash);
    printf("[%sOK%s] : Block hash %s\n", GRN, NRM, hash_1);


    // Ajout d'un block dans la blockchain
    printf("\n\n* ==== AJOUT D'UN BLOCK ==== *\n");

    Transaction trans_list_2[MAX_TRANS];
    int nb_trans_2 = 3;
    trans_list_2[0] = create_transaction("Jean", "Denis", 0.5);
    trans_list_2[1] = create_transaction("Remi", "Louis", 2);
    trans_list_2[2] = create_transaction("Louis", "Denis", 0.0005);
    int index_2 = 1;
    char prev_hash_2[SHA256_BLOCK_SIZE*2 + 1] = "0";
    strcpy(prev_hash_2, hash_1);

    Block b2 = create_block();
    init_block(b2, index_2, prev_hash_2, nb_trans_2, trans_list_2);

    add_block(bc, b2);

    int check_difficulty_2 = getDifficulty(bc);
    if(check_difficulty_2 != 4) {
        printf("[%sKO%s] : Blockchain difficulty is incorrect ||| more => Blockchain.difficulty : %d != difficulty : %d\n", RED, NRM, check_difficulty_2, 4);
    } else {
        printf("[%sOK%s] : Blockchain difficulty is correct\n", GRN, NRM);
    }

    int check_nb_blocs_2 = getNb_blocs(bc);
    if(check_nb_blocs_2 != 2) {
        printf("[%sKO%s] : Blockchain nb_blocs is incorrect ||| more => Blockchain.nb_blocs : %d != nb_blocs : %d\n", RED, NRM, check_nb_blocs_2, 1);
    } else {
        printf("[%sOK%s] : Blockchain nb_blocs is correct\n", GRN, NRM);
    }

    //Transactions
    Transaction *check_trans_list_2 = getTrans_list(b2);
    for(int i = 0; i < nb_trans_2; i++) {
        if(strcmp(getSource(check_trans_list_2[i]), getSource(trans_list_2[i])) != 0 || strcmp(getDestination(check_trans_list_2[i]), getDestination(trans_list_2[i])) != 0 || getRandInt(check_trans_list_2[i]) != getRandInt(trans_list_2[i]) || getSatoBnbValue(check_trans_list_2[i]) != getSatoBnbValue(trans_list_2[i]) || strcmp(getString(check_trans_list_2[i]), getString(trans_list_2[i])) != 0) {
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

    // Hash
    printf("[%sOK%s] : Block hash %s\n", GRN, NRM, getHash(b2));

    delete_blockchain(bc);

    return 0;
}