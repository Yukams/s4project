#include "coinbase.h"


int main(void){

    Blockchain bc = create_blockchain(3,10);
    
    Coinbase cb = create_coin_base(bc);
    int nbUsers = 20;
    /*===============================[BLOCKCHAIN]=====================================*/

    Block b = getBlock_list(get_blockchain_from_CB(cb))[1];
    printf("\n/\\==========[%sBLOCKCHAIN%s]==========/\\\n",YEL,NRM);
    printf("    [%snbBlock%s] => %d\n",GRN,NRM,getNb_blocs(get_blockchain_from_CB(cb))); //Block genesis + nouveau block de transac
    printf("    [%snbTrans%s] => %d\n",GRN,NRM,getNb_trans(getTrans_list(b)));
    printf("    [%snbBlockMax%s] => %d\n",GRN,NRM,getMax_size(bc));


    /*===============================[USERS]=====================================*/
    //ADD USERS TO DB
    printf("\n/\\==========[%sUSERS%s]==========/\\\n",YEL,NRM);
    printf("\n => ADDING USERS TO DB\n");
    printf("    [%sBEFORE%s] => %d (ONLY CREATOR)\n",RED,NRM,get_nb_user(get_DB_from_CB(cb)));
    printf("        ***... Adding %d Users ...***\n",nbUsers);
    for(int i = 0; i < nbUsers; i++)
        add_user_to_cb(cb);
    printf("    [%sAFTER%s] => %d (With creator)\n",GRN,NRM,get_nb_user(get_DB_from_CB(cb)));

    //USER INDEX

    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("\n => USER INDEX\n");
    printf("    [%sUSER %s%d%s] INDEX => '%d'\n",CYN,MAG,nbUsers,NRM,get_user_index(get_DB_from_CB(cb),nbUsers)); //0 ==> CREATOR ==> UserN
    printf("    [%sUSER%s] NBUSERS => '%d'\n",CYN,NRM,get_nb_user(get_DB_from_CB(cb))); //0 ==> CREATOR ==> UserN
    /*===============================[MONEY MANAGEMENT]=====================================*/

    printf("\n/\\==========[%sMONEY SUPPLY%s]==========/\\\n",YEL,NRM);
    printf("    [%sTOTAL BEFORE %sHELICO%s] => %.2f Bnb (ONLY CREATOR)\n",RED,MAG,NRM,get_masse_monetaire(cb));

    //HELICO
    printf("\n+*+*+*+*+... %sHelicopterMoney%s ...+*+*+*+*+\n\n",MAG,NRM);
    helicopter_money(cb);
    printf("    [%sTOTAL AFTER %sHELICO%s] => %.2f Bnb\n",GRN,MAG,NRM,get_masse_monetaire(cb));
    printf("\n/\\----------------(BLOCKCHAIN)----------------/\\\n");
    for(int i = 0; i<getNb_blocs(get_blockchain_from_CB(cb)); i++){
        b = getBlock_list(get_blockchain_from_CB(cb))[i];
        printf("    [%snbTrans Block %s%d%s] => %d\n",GRN,RED,getIndex(b),NRM,getNb_trans(getTrans_list(b)));
    }
    printf("/\\---------------------------------------------/\\\n");
    //TRANSAC RANDOM
    printf("\n+*+*+*+*+... %sMarche%s ...+*+*+*+*+\n\n",MAG,NRM);
    phase_marche(cb);
    printf("    [%sTOTAL AFTER %sMARCHE%s] => %.2f Bnb\n",GRN,MAG,NRM,get_masse_monetaire(cb));
    printf("\n/\\----------------(BLOCKCHAIN)----------------/\\\n");
    for(int i = 0; i<getNb_blocs(get_blockchain_from_CB(cb)); i++){
        b = getBlock_list(get_blockchain_from_CB(cb))[i];
        printf("    [%snbTrans Block %s%d%s] => %d\n",GRN,RED,getIndex(b),NRM,getNb_trans(getTrans_list(b)));
    }
    printf("/\\---------------------------------------------/\\\n");
    
    //Mining
    //printf("\nNB TRANSAC TOTAL = %d\n",getNbTransTotal(bc));
    mine_function(cb);
    printf("    [%sTOTAL AFTER %sMINING%s] => %.2f Bnb\n",GRN,MAG,NRM,get_masse_monetaire(cb));
    printf("\n/\\----------------(BLOCKCHAIN)----------------/\\\n");
    for(int i = 0; i<getNb_blocs(get_blockchain_from_CB(cb)); i++){
        b = getBlock_list(get_blockchain_from_CB(cb))[i];
        printf("    [%sHash Block %s%d%s] => %s\n",GRN,RED,getIndex(b),NRM,getHash(b));
    }
    printf("/\\---------------------------------------------/\\\n");


    delete_coinbase(cb);
    delete_blockchain(bc);
    
    return 0;
    
}