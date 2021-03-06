//
// Created by Valentin on 06/03/2021.
//
#include "block.h"

#ifndef PROJET_BLOCKHAIN_H
#define PROJET_BLOCKHAIN_H

typedef struct blockchain_s {
    int difficulty;
    int nb_blocs;
    block_t block_list[];
} blockchain_t;

#endif //PROJET_BLOCKHAIN_H
