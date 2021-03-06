#include "transaction.h"


/*==================================================================*/
/* STRUCTURE */

typedef struct transactionUnit_s {
        char source[MAX_NAME_LENGTH];
        char destination[MAX_NAME_LENGTH];
        int randint;
        long int value; // En BNB
        char string[MAX_STRING_LENGTH];
} *TransactionUnit ;

struct transactions_s {
    int nb_trans;
    TransactionUnit trans_list[MAX_TRANS];
};


/*==================================================================*/
/* FUNCTIONS */

/* PRIVATE */

// MISC PART
int randInt() {
    srand(time(NULL));
    return rand()%MAX_RANDINT;
}

// TRANSACTION UNIT PART
void delete_transaction(TransactionUnit transaction) {
    free(transaction);
}

TransactionUnit create_transaction() {
    TransactionUnit transaction = malloc(sizeof(struct transactionUnit_s));
    if(transaction == NULL){
        printf("\n*** Error : malloc transaction ***\n");
    }
    return transaction;
}

void init_transaction_genesis(TransactionUnit transaction) {
    sprintf(transaction->string, "Genesis");
}

void init_transaction(TransactionUnit transaction, char * source, char * destination, double value) {
    strcpy(transaction->destination, destination);
    strcpy(transaction->source, source);
    transaction->value = toSatoBnb(value);

    transaction->randint = randInt();
    if(transaction->randint == 0) {transaction->randint = 1;} // Il est demandé que le nombre soit au minimum 1

    sprintf(transaction->string, "Source user%s-Destination : user%s%d%ld", transaction->source, transaction->destination, transaction->randint, transaction->value);
}

/* PUBLIC */
// TRANSACTION LIST PART
void add_transaction_genesis(Transactions transaction_list) {
    TransactionUnit transaction = create_transaction();
    init_transaction_genesis(transaction);
    transaction_list->trans_list[transaction_list->nb_trans] = transaction;
    transaction_list->nb_trans += 1;
}

void delete_transaction_list(Transactions transaction_list) {
    for(int i = 0; i < transaction_list->nb_trans; i++) {
        delete_transaction(transaction_list->trans_list[i]);
    }
    free(transaction_list);
}

Transactions create_transaction_list() {
    Transactions transaction_list = malloc(sizeof(struct transactions_s));
    if(transaction_list == NULL) {
        printf("\n*** Error : malloc transaction ***\n");
    }
    transaction_list->nb_trans = 0;
    

    return transaction_list;
}

void add_transaction(Transactions transaction_list, char * source, char * destination, double value) {
    TransactionUnit transaction = create_transaction();
    init_transaction(transaction, source, destination, value);
    transaction_list->trans_list[transaction_list->nb_trans] = transaction;
    transaction_list->nb_trans += 1;
}

// MISC PART
int getNb_trans(Transactions transaction_list) {
    return transaction_list->nb_trans;
}

char * getTrans_listStrings(Transactions transaction_list, int indice) {
    return transaction_list->trans_list[indice]->string;
}

long int toSatoBnb(double value) {
    long int new_value = value * pow(10,8);
    return new_value;
}

double fromSatoBnb(long int value) {
    double new_value = value * pow(10,-8);
    return new_value;
}

/*==================================================================*/
/* FOR DEBUG */

// TRANSACTION UNIT PART
char* getSource(TransactionUnit transaction) {
    return transaction->source;
}

char* getDestination(TransactionUnit transaction) {
    return transaction->destination;
}

double getBnbValue(TransactionUnit transaction) {
    return fromSatoBnb(transaction->value);
}

long int getSatoBnbValue(TransactionUnit transaction) {
    return transaction->value;
}

int getRandInt(TransactionUnit transaction) {
    return transaction->randint;
}

char* getString(TransactionUnit transaction) {
    return transaction->string;
}

// TRANSACTION LIST PART
char* getTransactionSource(Transactions transaction_list, int indice) {
    return getSource(transaction_list->trans_list[indice]);
}

char* getTransactionDestination(Transactions transaction_list, int indice) {
    return getDestination(transaction_list->trans_list[indice]);
}

double getTransactionBnbValue(Transactions transaction_list, int indice) {
    return getBnbValue(transaction_list->trans_list[indice]);
}

long int getTransactionSatoBnbValue(Transactions transaction_list, int indice) {
    return getSatoBnbValue(transaction_list->trans_list[indice]);
}

int getTransactionRandInt(Transactions transaction_list, int indice) {
    return getRandInt(transaction_list->trans_list[indice]);
}

char* getTransactionString(Transactions transaction_list, int indice) {
    return getString(transaction_list->trans_list[indice]);
}

