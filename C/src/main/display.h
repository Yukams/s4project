#ifndef PROJET_DISPLAY_H
#define PROJET_DISPLAY_H
#include "coinbase.h"

/* [BLOCKCHAIN] */
void display_blockchain(Blockchain bc, Coinbase cb);
/* [USERS] */
void display_users(Coinbase cb, int nbUsers);
void display_users_index(Coinbase cb, int nbUsers);

/* [MONEY MANAGEMENT] */
void display_coinbase_helicopter(Coinbase cb);
void display_all_users_wallets(Coinbase cb);

#endif