#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main/transaction.h"
#include "test.h"

int main(void) {
    Transactions transaction_list = create_transaction_list();
    char source[MAX_NAME_LENGTH] = "Pierre";
    char destination[MAX_NAME_LENGTH] = "Paul";
    double value = 0.1;
    long int valueSatoBnb = 10000000; // 10 000 000
    char string[MAX_STRING_LENGTH];
    add_transaction(transaction_list, source, destination, value);

    int randInt = getTransactionRandInt(transaction_list, 0); // Can't get it otherwise
    sprintf(string, "Source user%s-Destination : user%s%d%ld", source, destination, randInt, valueSatoBnb);

    /* Source */
    char* check_source = getTransactionSource(transaction_list, 0);
    if(strcmp(check_source, source) != 0) {
        printf("[%sKO%s] : Transaction source is incorrect ||| more => Transaction.source : %s != source : %s\n", RED, NRM, check_source, source);
    } else {
        printf("[%sOK%s] : Transaction source is correct\n", GRN, NRM);
    }

    /* Destination */
    char* check_destination = getTransactionDestination(transaction_list, 0);
    if(strcmp(check_destination, destination) != 0) {
        printf("[%sKO%s] : Transaction destination is incorrect ||| more => Transaction.destination : %s != destination : %s\n", RED, NRM, check_destination, destination);
    } else {
        printf("[%sOK%s] : Transaction destination is correct\n", GRN, NRM);
    }


    /* Value Bnb */
    double check_bnb_value = getTransactionBnbValue(transaction_list, 0);
    if(check_bnb_value != value) {
        printf("[%sKO%s] : Transaction BNB value is incorrect ||| more => Transaction.value : %f != value : %f\n", RED, NRM, check_bnb_value, value);
    } else {
        printf("[%sOK%s] : Transaction BNB value is correct\n", GRN, NRM);
    }


    /* Value SatoBnb */
    long int check_satobnb_value = getTransactionSatoBnbValue(transaction_list, 0);
    if(check_satobnb_value != valueSatoBnb) {
        printf("[%sKO%s] : Transaction SatoBNB value is incorrect ||| more => Transaction.value : %ld != value : %ld\n", RED, NRM, check_satobnb_value, toSatoBnb(value));
    } else {
        printf("[%sOK%s] : Transaction SatoBNB value is correct\n", GRN, NRM);
    }


    /* Random int */
    int check_randint = getTransactionRandInt(transaction_list, 0);
    if(check_randint < 1 || check_randint > MAX_RANDINT) {
        printf("[%sKO%s] : Transaction randint is incorrect ||| more => Transaction.randint : %d (should be >= 1 and <= %d)\n", RED, NRM, check_randint, MAX_RANDINT);
    } else {
        printf("[%sOK%s] : Transaction randint is correct\n", GRN, NRM);
    }


    /* String */
    char* check_string = getTransactionString(transaction_list, 0);
    if(strcmp(check_string, string) != 0) {
        printf("[%sKO%s] : Transaction string is incorrect ||| more => Transaction.string : %s ||| string : %s\n", RED, NRM, check_string, string);
    } else {
        printf("[%sOK%s] : Transaction string is correct\n", GRN, NRM);
    }

    add_transaction(transaction_list, "Paul", "Pierre", 2);

    delete_transaction_list(transaction_list);

    return 0;
}
