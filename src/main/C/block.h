#ifndef PROJET_BLOCK_H
#define PROJET_BLOCK_H
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transaction.h"
#include "../../../utils/C_Packages/Sha256/sha256.h"
#include "../../../utils/C_Packages/Sha256/sha256_utils.h"

#define MAX_TRANS 10
#define DATE_LONG 30
#define STRLONG 30

/*==================================================================*/
typedef struct block_s* Block;

/* PUBLIC */
Block create_block();
void init_block(Block block, int index, char* prev_hash, int nb_trans, Transaction *transaction);
void delete_block(Block block);

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
