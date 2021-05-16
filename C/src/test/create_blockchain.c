#include "../main/blockchain.h"
#include "test.h"

int main(void) {
    int difficulty = 3;
    int max_blocks = 2;

    Blockchain bc = create_blockchain(difficulty, max_blocks);

    /* BLOCKCHAIN INITIALISATION VERIFICATION */
    printf("* ==== INITIALISATION BLOCKCHAIN ==== *\n");

    int check_difficulty_1 = getDifficulty(bc);
    if(check_difficulty_1 != difficulty) {
        printf("[%sKO%s] : Blockchain difficulty is incorrect ||| more => Blockchain.difficulty : %d != difficulty : %d\n", RED, NRM, check_difficulty_1, difficulty);
    } else {
        printf("[%sOK%s] : Blockchain difficulty is correct %d\n", GRN, NRM, check_difficulty_1);
    }

    int check_nb_blocs_1 = getNb_blocs(bc);
    if(check_nb_blocs_1 != 1) {
        printf("[%sKO%s] : Blockchain nb_blocs is incorrect ||| more => Blockchain.nb_blocs : %d != nb_blocs : %d\n", RED, NRM, check_nb_blocs_1, 1);
    } else {
        printf("[%sOK%s] : Blockchain nb_blocs is correct %d\n", GRN, NRM, check_nb_blocs_1);
    }

    // Verification du bloc génésis
    Block *block_list = getBlock_list(bc);
    Block b1 = block_list[0];

    // Nombre transaction
    int check_nb_trans_1 = getNb_trans(getTrans_list(b1));
    if(check_nb_trans_1 != 1) {
        printf("[%sKO%s] : Blockchain nb_trans is incorrect ||| more => Blockchain.nb_trans : %d != nb_trans : %d\n", RED, NRM, check_nb_trans_1, 1);
    } else {
        printf("[%sOK%s] : Blockchain nb_trans is correct %d\n", GRN, NRM, check_nb_trans_1);
    }

    // Previous hash
    char* check_prev_hash_1 = getPrev_hash(b1);
    if(strcmp(check_prev_hash_1, "0") != 0) {
        printf("[%sKO%s] : Block prev_hash is incorrect ||| more => Block.prev_hash : %s != prev_hash : %s\n", RED, NRM, check_prev_hash_1, "0");
    } else {
        printf("[%sOK%s] : Block prev_hash %s is correct\n", GRN, NRM, check_prev_hash_1);
    }

    // Indice
    int check_index_1 = getIndex(b1);
    if(check_index_1 != 0) {
        printf("[%sKO%s] : Block index is incorrect ||| more => Block.index : %d != index : %d\n", RED, NRM, check_index_1, 0);
    } else {
        printf("[%sOK%s] : Block index is correct %d\n", GRN, NRM, check_index_1);
    }

    // Nonce
    int check_nonce_1 = getNonce(b1);
    if(check_nonce_1 != 0) {
        printf("[%sKO%s] : Block nonce is incorrect ||| more => Block.nonce : %d != nonce : %d\n", RED, NRM, check_nonce_1, 0);
    } else {
        printf("[%sOK%s] : Block nonce is correct %d\n", GRN, NRM, check_nonce_1);
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

    // Ajout d'un block dans la blockchain
    printf("\n\n* ==== AJOUT D'UN BLOCK ==== *\n");

    Transactions trans_list_2 = create_transaction_list();
    add_transaction(trans_list_2, "Jean", "Denis", 0.5);
    add_transaction(trans_list_2,"Remi", "Louis", 2);
    add_transaction(trans_list_2,"Louis", "Denis", 0.0005);
    char prev_hash_2[SHA256_BLOCK_SIZE*2 + 1] = "0";
    strcpy(prev_hash_2, hash_1);

    add_block(bc, &trans_list_2);
    Block b2 = block_list[1];

    // Difficulté (blockchain)
    int check_difficulty_2 = getDifficulty(bc);
    if(check_difficulty_2 != difficulty) {
        printf("[%sKO%s] : Blockchain difficulty is incorrect ||| more => Blockchain.difficulty : %d != difficulty : %d\n", RED, NRM, check_difficulty_2, difficulty);
    } else {
        printf("[%sOK%s] : Blockchain difficulty is correct %d\n", GRN, NRM, check_difficulty_2);
    }

    // Nombre de blocs (blockchain)
    int check_nb_blocs_2 = getNb_blocs(bc);
    if(check_nb_blocs_2 != 2) {
        printf("[%sKO%s] : Blockchain nb_blocs is incorrect ||| more => Blockchain.nb_blocs : %d != nb_blocs : %d\n", RED, NRM, check_nb_blocs_2, 1);
    } else {
        printf("[%sOK%s] : Blockchain nb_blocs is correct %d\n", GRN, NRM, check_nb_blocs_2);
    }

    // Nombre transactions
    int check_nb_trans_2 = getNb_trans(getTrans_list(b2));
    if(check_nb_trans_2 != 3) {
        printf("[%sKO%s] : Blockchain nb_trans is incorrect ||| more => Blockchain.nb_trans : %d != nb_trans : %d\n", RED, NRM, check_nb_trans_2, 3);
    } else {
        printf("[%sOK%s] : Blockchain nb_trans is correct %d\n", GRN, NRM, check_nb_trans_2);
    }

    // Transactions
    Transactions check_trans_list_2 = getTrans_list(b2);
    for(int i = 0; i < 3; i++) {
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
        printf("[%sOK%s] : Block index is correct %d\n", GRN, NRM, check_index_2);
    }

    // Hash root
    char * check_hash_root_2 = getHash_root(b2);
    if(strcmp(check_hash_root_2, getHash_root(b2)) != 0) {
        printf("[%sKO%s] : Block hash_root is incorrect ||| more => Block.hash_root : %s != hash_root : %s\n", RED, NRM, check_hash_root_2, getHash_root(b1));
    } else {
        printf("[%sOK%s] : Block hash_root %s is correct\n", GRN, NRM, check_hash_root_2);
    }

    // Hash
    int nonce_2 = getNonce(b2);
    char hash_2[SHA256_BLOCK_SIZE*2 + 1];
    char *hash2 = getHash(b2);
    strcpy(hash_2, hash2);
    
    if(strncmp(hash2, "0000000000", difficulty)!=0){
        printf("[%sKO%s] : Block hash is incorrect ||| more => Block.hash : %s do not begin with %d \"0\"\n", RED, NRM, hash2, difficulty);
    } else {
        printf("[%sOK%s] : Block hash %s is correct\n", GRN, NRM,hash2);
        printf("[%sOK%s] : Block nonce is now : %d\n", GRN, NRM, nonce_2);
    }

    delete_blockchain(bc);

    return 0;
}
