#ifndef PROJET_BLOCKCHAIN_H
#define PROJET_BLOCKCHAIN_H
#include "block.h"

/*==================================================================*/

typedef struct blockchain_s* Blockchain;

Blockchain create_blockchain(int difficulty, int max_size);
void delete_blockchain(Blockchain blockchain);
void add_block(Blockchain blockchain, Transactions *transaction_list);

// FOR DEBUG
int getDifficulty(Blockchain blockchain);
int getNb_blocs(Blockchain blockchain);
int getMax_size(Blockchain blockchain);
Block *getBlock_list(Blockchain blockchain);

#endif //PROJET_BLOCKCHAIN_H
