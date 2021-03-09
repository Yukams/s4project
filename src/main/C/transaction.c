#include "transaction.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*==================================================================*/
/* STRUCTURE */
struct transaction_s {
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    int randint;
    long int value; // En SatoBNB
    char string[MAX_STRING_LENGTH];
};

/*==================================================================*/
/* FUNCTIONS */

/* PRIVATE */
int randInt() {
    srand(time(NULL));
    return rand()%MAX_RANDINT;
}

/* PUBLIC */
long int toSatoBnb(double value) {
    long int new_value = value * pow(10,8);
    return new_value;
}

double fromSatoBnb(long int value) {
    double new_value = value * pow(10,-8);
    return new_value;
}

Transaction create_transaction(char * source, char * destination, double value) {
    Transaction transaction = malloc(sizeof(struct transaction_s));

    strcpy(transaction->destination, destination);
    strcpy(transaction->source, source);
    transaction->value = toSatoBnb(value);

    transaction->randint = randInt();
    if(transaction->randint == 0) {transaction->randint = 1;} // Il est demandé que le nombre soit au minimum 1

    sprintf(transaction->string, "Source user%s-Destination : user%s%d%ld", transaction->source, transaction->destination, transaction->randint, transaction->value);

    return transaction;
}

/* FOR DEBUG PURPOSE */
char* getSource(Transaction transaction) {
    return transaction->source;
}

char* getDestination(Transaction transaction) {
    return transaction->destination;
}

double getBnbValue(Transaction transaction) {
    return fromSatoBnb(transaction->value);
}

long int getSatoBnbValue(Transaction transaction) {
    return transaction->value;
}

int getRandInt(Transaction transaction) {
    return transaction->randint;
}

char* getString(Transaction transaction) {
    return transaction->string;
}