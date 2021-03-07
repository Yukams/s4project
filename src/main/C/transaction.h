#ifndef PROJET_TRANSACTION_H
#define PROJET_TRANSACTION_H

#define MAX_RANDINT 100
#define MAX_STRING 100

/*==================================================================*/
typedef struct transaction_s *Transaction;

/* PUBLIC */
Transaction create_transaction(char * source, char * destination, double value);

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
