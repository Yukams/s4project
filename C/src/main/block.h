#ifndef PROJET_BLOCK_H
#define PROJET_BLOCK_H

#define MAX_TRANS 10
#define DATE_LONG 30
#define STRLONG 30

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "transaction.h"
#include "../../utils/C_Packages/Sha256/sha256.h"
#include "../../utils/C_Packages/Sha256/sha256_utils.h"


/*==================================================================*/
typedef struct block_s* Block;

/* PUBLIC */
Block create_block(int index, char* prev_hash, Transactions *transaction_list);
void delete_block(Block block);

/* FOR DEBUG PURPOSE TRANSACTION */
int getIndex(Block b);
char * getPrev_hash(Block b);
Transactions getTrans_list(Block b);
char * getHash_root(Block b);
char * getHash(Block b);
char * getTimestamp(Block b);
int getNonce(Block b);
void incrementNonce(Block b);

/*==================================================================*/


#endif //PROJET_BLOCK_H
