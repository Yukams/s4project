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

/* PUBLIC */
long int toSatoBnb(double value);
double fromSatoBnb(long int value);
void delete_transaction_list(Transactions transaction_list);
Transactions create_transaction_list();
void add_transaction(Transactions transaction_list, char * source, char * destination, double value);
int getNb_trans(Transactions transaction_list);
char * getTrans_listStrings(Transactions transaction_list, int indice);

/* FOR DEBUG PURPOSE */
char* getTransactionSource(Transactions transaction_list, int indice);
char* getTransactionDestination(Transactions transaction_list, int indice);
double getTransactionBnbValue(Transactions transaction_list, int indice);
long int getTransactionSatoBnbValue(Transactions transaction_list, int indice);
int getTransactionRandInt(Transactions transaction_list, int indice);
char* getTransactionString(Transactions transaction_list, int indice);

/*==================================================================*/

#endif //PROJET_TRANSACTION_H