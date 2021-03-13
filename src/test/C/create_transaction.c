#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../main/C/transaction.h"
#include "test.h"

int main(void) {
    Transaction transaction = create_transaction();
    char source[MAX_NAME_LENGTH] = "Pierre";
    char destination[MAX_NAME_LENGTH] = "Paul";
    double value = 0.1;
    long int valueSatoBnb = 10000000; // 10 000 000
    char string[MAX_STRING_LENGTH];
    init_transaction(transaction, source, destination, value);

    int randInt = getRandInt(transaction); // Can't get it otherwise
    sprintf(string, "Source user%s-Destination : user%s%d%ld", source, destination, randInt, valueSatoBnb);

    /* Source */
    char* check_source = getSource(transaction);
    if(strcmp(check_source, source) != 0) {
        printf("[%sKO%s] : Transaction source is incorrect ||| more => Transaction.source : %s != source : %s\n", RED, NRM, check_source, source);
    } else {
        printf("[%sOK%s] : Transaction source is correct\n", GRN, NRM);
    }

    /* Destination */
    char* check_destination = getDestination(transaction);
    if(strcmp(check_destination, destination) != 0) {
        printf("[%sKO%s] : Transaction destination is incorrect ||| more => Transaction.destination : %s != destination : %s\n", RED, NRM, check_destination, destination);
    } else {
        printf("[%sOK%s] : Transaction destination is correct\n", GRN, NRM);
    }


    /* Value Bnb */
    double check_bnb_value = getBnbValue(transaction);
    if(check_bnb_value != value) {
        printf("[%sKO%s] : Transaction BNB value is incorrect ||| more => Transaction.value : %f != value : %f\n", RED, NRM, check_bnb_value, value);
    } else {
        printf("[%sOK%s] : Transaction BNB value is correct\n", GRN, NRM);
    }


    /* Value SatoBnb */
    long int check_satobnb_value = getSatoBnbValue(transaction);
    if(check_satobnb_value != valueSatoBnb) {
        printf("[%sKO%s] : Transaction SatoBNB value is incorrect ||| more => Transaction.value : %ld != value : %ld\n", RED, NRM, check_satobnb_value, toSatoBnb(value));
    } else {
        printf("[%sOK%s] : Transaction SatoBNB value is correct\n", GRN, NRM);
    }


    /* Random int */
    int check_randint = getRandInt(transaction);
    if(check_randint < 1 || check_randint > MAX_RANDINT) {
        printf("[%sKO%s] : Transaction randint is incorrect ||| more => Transaction.randint : %d (should be >= 1 and <= %d)\n", RED, NRM, check_randint, MAX_RANDINT);
    } else {
        printf("[%sOK%s] : Transaction randint is correct\n", GRN, NRM);
    }


    /* String */
    char* check_string = getString(transaction);
    if(strcmp(check_string, string) != 0) {
        printf("[%sKO%s] : Transaction string is incorrect ||| more => Transaction.string : %s ||| string : %s\n", RED, NRM, check_string, string);
    } else {
        printf("[%sOK%s] : Transaction string is correct\n", GRN, NRM);
    }

    return 0;
}
