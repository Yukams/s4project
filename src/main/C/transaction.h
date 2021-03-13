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

/*==================================================================*/
typedef struct transaction_s* Transaction;

/* PUBLIC */
Transaction create_transaction();

void init_transaction(Transaction transaction, char * source, char * destination, double value);

long int toSatoBnb(double value);

double fromSatoBnb(long int value);

/* FOR DEBUG PURPOSE */
char* getSource(Transaction transaction);

char* getDestination(Transaction transaction);

double getBnbValue(Transaction transaction);

long int getSatoBnbValue(Transaction transaction);

int getRandInt(Transaction transaction);

char* getString(Transaction transaction);

/*==================================================================*/

#endif //PROJET_TRANSACTION_H
