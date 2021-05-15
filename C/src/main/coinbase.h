#ifndef PROJET_COINBASE_H
#define PROJET_COINBASE_H
#include "blockchain.h"
#include <stdbool.h>
#include "../test/test.h"

#define MAX_USERS 100
#define USER_STR_LEN 20

typedef struct coinbase_s* Coinbase;
typedef struct users_s* UserDB;
typedef struct userUnit_s* UserUnit;
/*==================================================================*/


void user_to_string(char * tag, UserUnit user);

UserUnit create_user();
UserDB create_user_DB();
void add_user_to_DB(UserDB userDB);
UserDB init_user_DB(Blockchain bc);
Coinbase create_coin_base(Blockchain blockchain);
void add_money(Coinbase coinbase, long int money, int indexUserDB, int indexBlock);
void helicopter_money(Coinbase coinbase);
void delete_user(UserUnit user);
void delete_user_DB(UserDB userDB);
void delete_coinbase(Coinbase coinbase);
void add_user_to_cb(Coinbase coinbase);
int randIntMax(int maxValue);

Blockchain get_blockchain_from_CB(Coinbase coinbase);
UserDB get_DB_from_CB(Coinbase Coinbase);
UserUnit get_user_from_CB(Coinbase coinbase, int index);
int get_masse_monetaire(Coinbase coinbase);
int get_nb_user(UserDB userDB);
int get_user_index(UserDB userDB, int index);


#endif //PROJET_COINBASE_H
