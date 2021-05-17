#include "coinbase.h"

/*==================================================================*/
/* STRUCTURE */
struct userUnit_s{
    int index; //User1 ... UserN + User 0 = Creator
    double wallet;
 };

struct users_s{
    int nbUsers;
    Blockchain blockChain; //Une block chain / DB
    UserUnit userList[MAX_USERS];
};

struct coinbase_s {
    double masseMoneitaire;
    UserDB userDB;
};


/*==================================================================*/
/* FUNCTIONS */

///PRIVATE UTILS///
void user_to_string(UserUnit user, char buffer[10]){
    char tag[10];
    sprintf(tag, "User%d", user->index);
    strcpy(buffer,tag);
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
        user->wallet = 0;
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
    Creator->wallet = 50;
    user_to_string(Creator,tag);
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
    user_to_string(user,tag);
    add_transaction(getTrans_list(b),"Coinbase",tag,money); // transaction à "UserN"
    user->wallet += money;
    coinbase->masseMoneitaire += money;
}

void transfer_money(Coinbase coinbase, UserUnit user1,UserUnit user2, double money, Transactions transaction_list){
    char bufferU1[10];
    char bufferU2[10];
    user_to_string(user1,bufferU1);
    user_to_string(user2,bufferU2);
    add_transaction(transaction_list,bufferU1,bufferU2,money); // transaction à "UserN"
}

/*==================================================================*/

/* PUBLIC*/

Coinbase create_coin_base(Blockchain blockchain){ //CONSTRUCTEUR
    Coinbase cb = malloc(sizeof(struct coinbase_s));
    if(cb == NULL) printf("\n*** Error : malloc UserDB ***\n");
    cb->userDB = init_user_DB(blockchain);
    cb->masseMoneitaire = 50;
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
        //printf("=> User%d reçoit 50 Bnb\n",get_user_index(get_DB_from_CB(coinbase),i));
        if(nbTransactionBlock<MAX_TRANS)
            add_money(coinbase,50,i,lastIndex);
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


void trans_aleatoire(Coinbase coinbase){
    Blockchain blockchain = get_blockchain_from_CB(coinbase);
    Transactions transaction_list;

    int nbTransactionBlock, nbTransaction, nbBlockReste;
    double value;
    UserUnit randUser1,randUser2;
    nbBlockReste = getMax_size(blockchain)-getNb_blocs(blockchain);
    nbTransaction = randMinMax(1,nbBlockReste);
    int maxNbUser = get_nb_user(get_DB_from_CB(coinbase));

    int nbrand = randMinMax(1,maxNbUser/2);

    int aleatoire = nbrand;
    int nbRandUser1, nbRandUser2;
    for(int i=0; i<nbTransaction; i++){
        transaction_list = create_transaction_list();
        nbTransactionBlock = randMinMax(1,MAX_TRANS);
        
        for(int j=0; j<nbTransactionBlock;j++){

            randUser1 = get_user_from_CB(coinbase,aleatoire);
            nbRandUser1 = aleatoire;
            nbrand = ((nbrand + nbrand)*(j+1)+1);
            aleatoire = nbrand%maxNbUser;
            if(nbRandUser1 == aleatoire){aleatoire = (aleatoire+1)%maxNbUser;}
            randUser2 = get_user_from_CB(coinbase,aleatoire);
            nbRandUser2 = aleatoire;
            nbrand = (nbrand + nbrand)*(j+2)+1;
            aleatoire = nbrand%maxNbUser;
            if(nbrand > 1000000){nbrand = randMinMax(1,maxNbUser/2);}
  
            value = randMinMax(1,MAX_MONEY_BNB_TRANS);
            if(value<=randUser1->wallet){
                transfer_money(coinbase,randUser1,randUser2,value,transaction_list);
                printf("\n----------BEFORE---------\n");
                printf("User%s%d%s: {%.2fBnb}\n",RED,nbRandUser1,NRM,randUser1->wallet);
                printf("User%s%d%s: {%.2fBnb}\n",GRN,nbRandUser2,NRM,randUser2->wallet); 
                randUser1->wallet -= value;
                randUser2->wallet += value;
                printf("-----------------------");
                printf("\n-------TRANSACTION------\n");
                printf("User%s%d%s envoie %s'%.2f'%s Bnb à User%s%d%s\n",RED,nbRandUser1,NRM,YEL,value,NRM,GRN,nbRandUser2,NRM);
                printf("-----------------------\n");
                printf("----------AFTER--------\n");
                printf("User%s%d%s: {%.2fBnb}\n",RED,nbRandUser1,NRM,randUser1->wallet);
                printf("User%s%d%s: {%.2fBnb}\n",GRN,nbRandUser2,NRM,randUser2->wallet); 
                printf("-----------------------\n");
            }
        }
        add_block(blockchain,&transaction_list);
    }
}



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
double get_user_wallet(UserDB userDB, int index){
    return userDB->userList[index]->wallet;
}
