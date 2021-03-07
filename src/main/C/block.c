//
// Created by Valentin on 06/03/2021.
//

#include "block.h"

trans_t init_trans(char * source, char * destination, int value) {
    trans_t trans;

    trans.randint = srand(time(NULL)) % MAX_VALUE;
    trans.destination = strcpy(destination);
    trans.source = strcpy(source);
    trans.value = toSatoBnb(value);

    return trans;
}

long int toSatoBnb(int value) {
    long int new_value = value * pow(10,8);
    return new_value;
}

char * getTimeStamp() {
    time_t ltime;
    time(&ltime);
    return ctime(&ltime);
}