#include "coinbase.h"


int main(void){

    Blockchain bc = create_blockchain(3,10);
    Coinbase cb = create_coin_base(bc);
    int nbUsers = 15;
    
    Block b = getBlock_list(get_blockchain_from_CB(cb))[1];
    printf("\n/==========[%sBLOCK CHAIN%s]========/\n",YEL,NRM);
    printf("[%snbBlock%s] => %d\n",GRN,NRM,getNb_blocs(get_blockchain_from_CB(cb))); //Block genesis + nouveau block de transac
    printf("[%snbTrans%s] => %d\n",GRN,NRM,getNb_trans(getTrans_list(b)));



    printf("\n/==========[%sUSER ADD%s]========/\n",YEL,NRM);
    printf("[%sBEFORE%s] => %d (ONLY CREATOR)\n",RED,NRM,get_nb_user(get_DB_from_CB(cb)));
    printf("    *** Adding %d Users ***\n",nbUsers);
    for(int i = 0; i < nbUsers; i++)
        add_user_to_cb(cb);
    printf("[%sAFTER%s] => %d\n",GRN,NRM,get_nb_user(get_DB_from_CB(cb)));

    printf("\n/*==========[%sUSER INDEX%s]========/\n",YEL,NRM);
    printf("[%sUSER INDEX%s] => %d",CYN,NRM,get_user_index(get_DB_from_CB(cb),0)); //0 ==> CREATOR 

    printf("\n/*==========[%sMONEY SUPPLY%s]========/\n",YEL,NRM);
    printf("[%sBEFORE%s] => %d Bnb (ONLY CREATOR)\n",RED,NRM,get_masse_monetaire(cb));
    printf("    *** %sHelicopterMoney%s ...***\n",MAG,NRM);
    helicopter_money(cb);
    printf("[%sAFTER%s] => %d Bnb\n",GRN,NRM,get_masse_monetaire(cb));
    printf("[%snbTrans%s] => %d\n",GRN,NRM,getNb_trans(getTrans_list(b)));
    return 0;
    
}