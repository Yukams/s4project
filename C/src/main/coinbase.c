#include "coinbase.h"
/*==================================================================*/
/* STRUCTURE */
struct userUnit_s{
    int index; //User1 ... UserN + User 0 = Creator
    int wallet;
 };

struct users_s{
    int nbUsers;
    Blockchain blockChain; //Une block chain / DB
    UserUnit userList[MAX_USERS];
};

struct coinbase_s {
    double masseMoneitaire;
    bool isPhaseInflation;
    UserDB userDB;
    TransactionsGlob super_list;
};


/*==================================================================*/
/* FUNCTIONS */

///PRIVATE UTILS///
void user_to_string(char * tag, UserUnit user){
    sprintf(tag, "User%d", user->index);
}

int randIntMax(int maxValue){
    srand(time(NULL));
    return rand()%maxValue;     //[0,maxValue[
}

int randIntMaxInclu(int maxValue){
    srand(time(NULL));
    return (rand()%maxValue)+1;     //[1,maxValue]
}
int randMinMax(int min, int max){
    srand(time(NULL));
    return (rand() % (max+1 - min)) + min; 
}
/*==================================================================*/
/* PRIVATE USER*/

UserUnit create_user(){
    UserUnit user = malloc(sizeof(struct userUnit_s));
    if(user == NULL) printf("\n*** Error : malloc UserUnit ***\n");
    return user;
}

UserDB create_user_DB(){
    UserDB userDB = malloc(sizeof(struct users_s));
    if(userDB == NULL) printf("\n*** Error : malloc UserDB ***\n");
    userDB->nbUsers = 0;
    return userDB;
}


void add_user_to_DB(UserDB userDB){
    if(userDB->nbUsers < MAX_USERS){// 99/100
        UserUnit user = create_user(); 
        userDB->nbUsers++; // 100/100
        user->index = (userDB->nbUsers) - 1; //L'ID du user = NbUsersCourant - 1 (car User0 = Creator => userDB[0])
        userDB->userList[(user->index)] = user; // ajout de l'utilisateur à son ID (car UserN = userDB[N])
    }
    else printf("\n*** Error : nbUsersMax / maxBlocChain atteint***\n");
}

UserDB init_user_DB(Blockchain bc){ // Initialisation de la BC par creator => génère le genesis
    UserUnit Creator = create_user();//creation du user Creator
    UserDB userDB = create_user_DB();
    Transactions tl = create_transaction_list();

    char tag[10];
    Creator->index = 0; //Creator = Indice 0 (userList[0] aussi)

    user_to_string(tag, Creator);
    add_transaction(tl,"Coinbase",tag,50);//Ajout de la transaction Genesis à la list de TX
    add_block(bc,&tl);// Creation d'un nouveau block (indice 1)

    userDB->userList[0] = Creator;
    userDB->nbUsers += 1;

    userDB->blockChain = bc;
    
    return userDB;
}


/* PRIVATE MONEY MANAGEMENT*/
void add_money(Coinbase coinbase, double money, int indexUserDB, int indexBlock){ //Add money FROM coinbase TO user (TX in BlockMiné[indexBlock])
    Block b = getBlock_list(coinbase->userDB->blockChain)[indexBlock]; //Block miné
    UserUnit user = get_user_from_CB(coinbase,indexUserDB);
    char tag[10];
    user_to_string(tag, user);
    //printf("/**//*/**/MASSE MON = %ld \n", coinbase->masseMoneitaire);
    add_transaction(getTrans_list(b),"Coinbase",tag,money); // transaction à "UserN"
    //printf("****Coinbase envoie 50 Bnb à %s\n",getTransactionDestination(getTrans_list(b),1));
    
    coinbase->masseMoneitaire += money;
}

void transfer_money(Coinbase coinbase, UserUnit user1,UserUnit user2, double money, Transactions transaction_list){
    char bufferU1[10];
    char bufferU2[10];
    user_to_string(bufferU1, user1);
    user_to_string(bufferU2, user2);
    add_transaction(transaction_list,bufferU1,bufferU2,money); // transaction à "UserN"
    
    coinbase->masseMoneitaire += money;
}

/*==================================================================*/

/* PUBLIC*/

Coinbase create_coin_base(Blockchain blockchain){ //CONSTRUCTEUR
    Coinbase cb = malloc(sizeof(struct coinbase_s));
    if(cb == NULL) printf("\n*** Error : malloc UserDB ***\n");
    cb->userDB = init_user_DB(blockchain);
    cb->isPhaseInflation = true; 
    cb->masseMoneitaire = 50;
    cb->super_list = create_transaction_global(getMax_size(blockchain));
    return cb;
}

void add_user_to_cb(Coinbase coinbase){
    add_user_to_DB(coinbase->userDB);
}

/*PHASE HELICOPTER MONEY*/
void helicopter_money(Coinbase coinbase){
    Blockchain bc = get_blockchain_from_CB(coinbase);
    Block b;
    Transactions transaction_list;
    int lastIndex,nbTransactionBlock; //Dernier block ajouté => Index du bloc auquel on ajouteras de la monais


    for(int i = 1; i<coinbase->userDB->nbUsers; i++){ //parcours tt les users, excepté userList[0]
        lastIndex = getNb_blocs(bc)-1;
        b = getBlock_list(bc)[lastIndex];
        transaction_list = getTrans_list(b);
        nbTransactionBlock = getNb_trans(transaction_list);
        /* printf("=> TOTAL MM : %d\n",get_masse_monetaire(coinbase));
        printf("=> User%d reçoit 50 Bnb\n",get_user_index(get_DB_from_CB(coinbase),i)); */
        if(nbTransactionBlock<MAX_TRANS)
            add_money(coinbase,50,i,lastIndex);//incrémente la masse monétaire
        else {
            if(lastIndex+1 == getMax_size(bc) && nbTransactionBlock == MAX_TRANS){
                printf("*** Error : Taille Max BlockChain atteinte ***\n");
                return;
            }
            else {
                transaction_list = create_transaction_list();
                add_block(bc,&transaction_list);
                add_money(coinbase,50,i,lastIndex+1);
                }
        }
    }
}

void set_super_list(Coinbase coinbase){
    Blockchain bc = get_blockchain_from_CB(coinbase);
    Block b;
    Transactions transaction_list;
    for(int i = 0; i<getNb_blocs(bc);i++){
        b = getBlock_list(bc)[i];
        transaction_list = getTrans_list(b);
        add_transaction_global(coinbase->super_list,transaction_list);
    }
}

void phase_marche(Coinbase coinbase){
    Blockchain blockchain = get_blockchain_from_CB(coinbase);
    Transactions transaction_list;
    //Block b;

    int randTX1,randTX2, nbTransactionBlock, nbTransaction, nbBlockReste;
    double value;
    UserUnit randUser1,randUser2;
    nbBlockReste = getMax_size(blockchain)-getNb_blocs(blockchain);
    nbTransaction = randMinMax(1,nbBlockReste); // entre une transaction minimum et Nombre de block restant / 2
    for(int i=0; i<nbTransaction; i++){
        transaction_list = create_transaction_list();
        nbTransactionBlock =  randMinMax(1,MAX_TRANS);                                                         //RECHANGER EN MAX_TRANS
        
        for(int j=0; j<nbTransactionBlock;j++){
            randTX1 = randIntMax(get_nb_user(get_DB_from_CB(coinbase)));
            randTX2 = randIntMax(get_nb_user(get_DB_from_CB(coinbase)));

            randUser1 = get_user_from_CB(coinbase,randTX1);
            randUser2 = get_user_from_CB(coinbase,randTX2);
        
            value = randIntMax(MAX_MONEY_BNB);
            transfer_money(coinbase,randUser1,randUser2,value,transaction_list);
        }

        add_block(blockchain,&transaction_list);
        
    }
    //set_super_list(coinbase);
}

void copie_transaction_list(Transactions transList1, Transactions transList2,int indexTrans){
    char *source = getTransactionSource(transList1,indexTrans);
    char *destination = getTransactionDestination(transList1,indexTrans);
    double value = getTransactionBnbValue(transList1,indexTrans);
    /*==============COPIE DES DATA RECUP A LA LISTE DE TRANSACTION CIBLE==============*/
    add_transaction(transList2,source,destination,value);
}

Transactions get_tl_from_super(Transactions *super_liste, int index){
    return super_liste[index];
}

void mine_function(Coinbase coinbase){
    /*Blockchain blockchain = get_blockchain_from_CB(coinbase);
    int indexFIFO = 0,tailleSuperListe,randTotalTransactionPrise,totalTransactionListBlock;
    //tailleSuperListe = getMax_size(blockchain);
    Transactions *super_liste = phase_marche(coinbase);
    Transactions transactions_list;

    randTotalTransactionPrise = randMinMax(1,MAX_TRANS);
    //===============User Mineur==============/
    UserUnit miner;
    int randUser = randIntMax(get_nb_user(get_DB_from_CB(coinbase)));
    miner = get_user_from_CB(coinbase,randUser);
    int blockMined = 0; //cb de block miné
    for(int i = 0; i<randTotalTransactionPrise; i++){ //4 a miner
        transactions_list = create_transaction_list();
        totalTransactionListBlock = getNb_trans(super_liste[i]); //2transaction dans la [TL1]
        for(int j = 0; j<totalTransactionListBlock; j++)
            copie_transaction_list(super_liste[i],transactions_list,indexFIFO);
        add_block(blockchain,&transactions_list);
    }
    */
   
    int i = 1;

    
   
}
/*create Global;    add_tl_global;     remove Global;    get_tl_global*/
/*
void mine(Coinbase coinbase){
    int NbTransToMine = randIntMaxInclu(MAX_TRANS);
    Blockchain bc = get_blockchain_from_CB(coinbase);
    double award = 50;
    int checkIndexMined[MAX_BLOCK_MINE_AWARD];
    //===============User Mineur===============
        UserUnit miner;
        int randUser = randIntMax(get_nb_user(get_DB_from_CB(coinbase)));
        miner = get_user_from_CB(coinbase,randUser);
        int blockMined = 0; //cb de block miné
        bool canMine = true;

    for(int j = 0; j < NbTransToMine; j++){
        Transactions tl_dest = create_transaction_list();
        
        while(blockMined < MAX_BLOCK_MINE_AWARD){
            //===============Choix du Block Random===============
            Block b;
            int lastIndex = getNb_blocs(bc)-1; //si 9b => 0,8
            int randBlockIndex = randIntMaxInclu(lastIndex); //exclu genesis => [b1]=>[dernier_b_added]
            b = getBlock_list(bc)[randBlockIndex];

            //===============Choix de la Transaction Random===============
            Transactions transaction_list = getTrans_list(b);//liste de trans du block
            
            int maxTransBlock = getNb_trans(transaction_list); //nb de trans max du block (1->x); x = 1,10
            int indexTransRand = randIntMax(maxTransBlock-1);//transaction random de la liste de transaction du block (0->x) x = 0,9
            for(int k = 0; k<MAX_BLOCK_MINE_AWARD;k++){
                if(indexTransRand == checkIndexMined[k])
                    canMine = false;
            }
            if(canMine){
                //===============Recup Info Trans===============
                char *source = getTransactionSource(transaction_list,indexTransRand);
                char *destination = getTransactionDestination(transaction_list,indexTransRand);
                double value = getTransactionBnbValue(transaction_list,indexTransRand);
                //===============Copie Info Trans===============
                add_transaction(tl_dest,source,destination,value);
                checkIndexMined[blockMined] = indexTransRand;
                blockMined++;
            }
        }
        add_block(bc,&tl_dest);
        blockMined = 0;
        miner->wallet+=award;
        coinbase->masseMoneitaire+=award;
        award = award / 2;
    }
    //printf("%s mined %d!\n");

}*/

void delete_user(UserUnit user){
    free(user);
}
void delete_user_DB(UserDB userDB){
    for(int i = 0; i<userDB->nbUsers;i++){
        delete_user(userDB->userList[i]);
    }
    free(userDB);
}
void delete_coinbase(Coinbase coinbase){
    free(coinbase);
}
/*====================DEBUG============================*/
/*Coinbase / System*/

UserUnit get_user_from_CB(Coinbase coinbase, int index){
    return coinbase->userDB->userList[index];
}
UserDB get_DB_from_CB(Coinbase Coinbase){
    return Coinbase->userDB;
}
Blockchain get_blockchain_from_CB(Coinbase coinbase){
    return coinbase->userDB->blockChain;
}
double get_masse_monetaire(Coinbase coinbase){
    return coinbase->masseMoneitaire;
}



/*USER DB*/
int get_user_index(UserDB userDB, int index){
    return userDB->userList[index]->index;
}
int get_nb_user(UserDB userDB){
    return userDB->nbUsers;
}
int get_user_wallet(UserDB userDB, int index){
    return userDB->userList[index]->wallet;
}





/* AUTRE : 
    int nb_transaction_restant(Coinbase coinbase, Transactions transaction_list, Blockchain blockchain, int LastIndex){

    int nbTransCurrentBlock = getNb_trans(transaction_list); //nombre de transaction du block courrant
    int nbMaxTrans = MAX_TRANS*(getMax_size(blockchain)-1); //Nombre de transaction total possible
    int nbTransPast = ((LastIndex-1)*10)+nbTransCurrentBlock; //Nombre de transaction passé

    int nbTransaction = randIntMaxInclu(nbMaxTrans-nbTransPast); //[2,max restant]
    return nbTransaction;

} */