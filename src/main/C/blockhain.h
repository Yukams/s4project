#ifndef PROJET_BLOCKHAIN_H
#define PROJET_BLOCKHAIN_H
#include "block.h"

typedef struct {
    int difficulty;
    int nb_blocs;
    Block *block_list;
} Blockchain;

#endif PROJET_BLOCKHAIN_H
