#ifndef PROJET_COINBASE_H
#define PROJET_COINBASE_H
#include "blockchain.h"
#include <stdbool.h>
#include "../test/test.h"

#define MAX_USERS 100
#define USER_STR_LEN 20
#define MAX_MONEY_BNB 100
#define MAX_BLOCK_MINE_AWARD 3 //MAX BLOCKS TO MINE BEFORE GIVING AWARD
/*=======================STRUCT======================================*/

typedef struct coinbase_s* Coinbase;
typedef struct users_s* UserDB;
typedef struct userUnit_s* UserUnit;

/*==================================================================*/

/*Constructer / Functions*/
Coinbase create_coin_base(Blockchain blockchain);
void add_user_to_cb(Coinbase coinbase);

void helicopter_money(Coinbase coinbase);
Transactions phase_marche(Coinbase coinbase);
void mine(Coinbase coinbase);

void delete_coinbase(Coinbase coinbase);



/*DEBUG*/
//Coinbase/System
Blockchain get_blockchain_from_CB(Coinbase coinbase);
UserDB get_DB_from_CB(Coinbase Coinbase);
UserUnit get_user_from_CB(Coinbase coinbase, int index);
Transactions get_trans_list_from_global(Coinbase coinbase,int index);
double get_masse_monetaire(Coinbase coinbase);

//User
int get_user_wallet(UserDB userDB, int index);
int get_nb_user(UserDB userDB);
int get_user_index(UserDB userDB, int index);





#endif //PROJET_COINBASE_H
