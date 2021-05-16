#ifndef PROJET_TRANSACTION_H
#define PROJET_TRANSACTION_H
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define MAX_RANDINT 99
#define MAX_NAME_LENGTH 16
#define MAX_STRING_LENGTH 91
#define MAX_TRANS 10

/*==================================================================*/
typedef struct transactions_s* Transactions;
typedef struct transactions_list_global_s* TransactionsGlob;

// MISC PART
long int toSatoBnb(double value);
double fromSatoBnb(long int value);
int getNb_trans(Transactions transaction_list);
char * getTrans_listStrings(Transactions transaction_list, int indice);
// TRANSACTION LIST PART
void delete_transaction_list(Transactions transaction_list);
Transactions create_transaction_list();
// TRANSACTION UNIT PART
void add_transaction_genesis(Transactions transactions_list);
void add_transaction(Transactions transaction_list, char * source, char * destination, double value);
// GLOBAL LIST PART
Transactions get_tl_from_global(TransactionsGlob super_liste, int index);
void add_transaction_global(TransactionsGlob super_liste, Transactions transactions_list);
void remove_global(TransactionsGlob super_liste);
void incr_index_fifo_tl(TransactionsGlob super_liste);
void incr_index_fifo_trans(TransactionsGlob super_liste);
void reset_index_fifo_trans(TransactionsGlob super_liste); //reset à 0
int get_index_fifo_trans(TransactionsGlob super_liste);
int get_index_fifo_tl(TransactionsGlob super_liste);
TransactionsGlob create_transaction_global(int taille);

// FOR DEBUG
char* getTransactionSource(Transactions transaction_list, int indice);
char* getTransactionDestination(Transactions transaction_list, int indice);
double getTransactionBnbValue(Transactions transaction_list, int indice);
long int getTransactionSatoBnbValue(Transactions transaction_list, int indice);
int getTransactionRandInt(Transactions transaction_list, int indice);
char* getTransactionString(Transactions transaction_list, int indice);

/*==================================================================*/

#endif //PROJET_TRANSACTION_H
