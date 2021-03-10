#ifndef PROJET_BLOCK_H
#define PROJET_BLOCK_H
#define MAX_TRANS 10
#define DATE_LONG 30
#define STRLONG 30

/*==================================================================*/
typedef struct block_s* Block;

/* PUBLIC */
Block create_block(int index, char* prev_hash, int nb_trans, Transaction *trans_list);

/* FOR DEBUG PURPOSE */
int getIndex(Block b);
char * getPrev_hash(Block b);
int getNb_trans(Block b);
Transaction * getTrans_list(Block b);
char * getHash_root(Block b);
char * getHash(Block b);
int getNonce(Block b);

/*==================================================================*/


#endif //PROJET_BLOCK_H
