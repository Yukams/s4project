//
// Created by Valentin on 06/03/2021.
//

#ifndef PROJET_BLOCKHAIN_H
#define PROJET_BLOCKHAIN_
#include "block.h"

typedef struct blockchain_s {
    int difficulty;
    int nb_blocs;
    block_t *block_list;
} blockchain_t;

#endif //PROJET_BLOCKHAIN_H
