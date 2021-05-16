#include "coinbase.h"
/*===============================[BLOCKCHAIN]=====================================*/
void display_blockchain(Blockchain bc, Coinbase cb){
    Block b;
    printf("\n/\\==========[%sBLOCKCHAIN (MAX %d)%s]==========/\\\n\n",YEL,getMax_size(bc),NRM);
    printf("\n/\\---------------------------------(Blocks)------------------------------/\\\n");
    printf("************************************************************************\n");
    for(int i = 0; i<getNb_blocs(get_blockchain_from_CB(cb)); i++){
        b = getBlock_list(get_blockchain_from_CB(cb))[i];
        printf("    [%sHash Block     %s%d%s] => %s\n",GRN,RED,getIndex(b),NRM,getHash(b));
        printf("    [%sPrevHash Block %s%d%s] => %s\n",RED,GRN,getIndex(b),NRM,getPrev_hash(b));
        printf("    [%snbTrans Block  %s%d%s] => %d\n",GRN,YEL,getIndex(b),NRM,getNb_trans(getTrans_list(b)));
        printf("************************************************************************\n");
    }
    printf("\\/------------------------------------------------------------------------\\/\n\n\n");
}
/*===============================[USERS]=====================================*/
void display_users(Coinbase cb, int nbUsers){
    printf("\n/\\===============[%sUSERS%s]===============/\\\n",YEL,NRM);
    printf("\n(User Add)\n");
    printf("    [%snbUser %sBEFORE%s] => %d (ONLY CREATOR)\n",CYN,RED,NRM,get_nb_user(get_DB_from_CB(cb)));
    printf("        ***... Adding %d Users ...***\n",nbUsers);
}
void display_users_index(Coinbase cb, int nbUsers){
    printf("(User Index)\n");
    for(int i = 0;i<nbUsers;i++){
        printf("    [%sUSER %s%d%s] INDEX => '%d'\n",CYN,MAG,i,NRM,get_user_index(get_DB_from_CB(cb),i)); //0 ==> CREATOR ==> UserN
    }
    
    printf("\n    [%sTOTAL USER%s] NBUSERS => '%d'\n",CYN,NRM,get_nb_user(get_DB_from_CB(cb))); //0 ==> CREATOR ==> UserN
    printf("\\/------------------------------------------------------------------------\\/\n");
}

/*===============================[MONEY MANAGEMENT]=====================================*/
void display_coinbase_helicopter(Coinbase cb){
    printf("\n/\\==========[%sMONEY SUPPLY%s]==========/\\\n\n",YEL,NRM);
    printf("    [%sTOTAL BEFORE %sHELICO%s] => %.2f Bnb\n",RED,MAG,NRM,get_masse_monetaire(cb));
    printf("\n+*+*+*+*+... %sHelicopterMoney%s ...+*+*+*+*+\n\n",MAG,NRM);
}
void display_coinbase_marche(Coinbase cb){
    printf("\n/\\==========[%sMONEY SUPPLY%s]==========/\\\n\n",YEL,NRM);
    printf("    [%sTOTAL BEFORE %sMARCHÉ%s] => %.2f Bnb\n",RED,MAG,NRM,get_masse_monetaire(cb));
    printf("\n+*+*+*+*+... %sMarché%s ...+*+*+*+*+\n\n",MAG,NRM);
}
void display_all_users_wallets(Coinbase cb){
    int nb_users = get_nb_user(get_DB_from_CB(cb));
    for(int i = 0; i< nb_users; i++)
        printf("User%s%d%s: {%.2f %sBnb%s}\n",GRN,i,NRM,get_user_wallet(get_DB_from_CB(cb),i),YEL,NRM);
}
