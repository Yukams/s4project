#ifndef PROJET_TRANSACTION_H
#define PROJET_TRANSACTION_H

#define MAX_TRANS 10

/*==================================================================*/
typedef struct block_s* Block;

// Returns block's creation time date
char * getTimeStamp();

Block create_block(int index, char* prev_hash, int nb_trans, Transaction trans_list);

/*==================================================================*/

#endif //PROJET_TRANSACTION_H
