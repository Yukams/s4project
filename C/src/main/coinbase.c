#include "coinbase.h"
/*==================================================================*/
/* STRUCTURE */
struct userUnit_s{
    int index; //User1 ... UserN + User 0 = Creator
 };

struct users_s{
    int nbUsers;
    Blockchain blockChain; //Une block chain / DB
    UserUnit userList[MAX_USERS];
};

struct coinbase_s {
    long int masseMoneitaire;
    bool isPhaseInflation;
    UserDB userDB;
};

/*==================================================================*/
/* FUNCTIONS */

/* PRIVATE */

void user_to_string(char * tag, UserUnit user){
    sprintf(tag, "User%d", user->index);
}

UserUnit get_user_from_CB(Coinbase coinbase, int index){
    return coinbase->userDB->userList[index];
}
UserDB get_DB_from_CB(Coinbase Coinbase){
    return Coinbase->userDB;
}
int get_nb_user(UserDB userDB){
    return userDB->nbUsers;
}

int get_masse_monetaire(Coinbase coinbase){
    return coinbase->masseMoneitaire;
}

Blockchain get_blockchain_from_CB(Coinbase coinbase){
    return coinbase->userDB->blockChain;
}

int get_user_index(UserDB userDB, int index){
    return userDB->userList[index]->index;
}

///////////////////////////////////////////////////


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
        if(userDB->nbUsers < MAX_USERS){
            userDB->nbUsers++; // 100/100
            user->index = (userDB->nbUsers) - 1; //L'ID du user = NbUsersCourant - 1 (car User0 = Creator => userDB[0])
            userDB->userList[(user->index)] = user; // ajout de l'utilisateur à son ID (car UserN = userDB[N])
        }
    }
    else printf("\n*** Error : nbUsersMax atteint ***\n");
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

Coinbase create_coin_base(Blockchain blockchain){ //constructeur
    Coinbase cb = malloc(sizeof(struct coinbase_s));
    if(cb == NULL) printf("\n*** Error : malloc UserDB ***\n");
    cb->userDB = init_user_DB(blockchain);
    cb->isPhaseInflation = true; //Phase d'inflation active par défaut (création monétaire ex-nihilo)
    cb->masseMoneitaire = 50;
    return cb;
}


void add_money(Coinbase coinbase, long int money, int indexUserDB, int indexBlock){ //Add money FROM coinbase TO user (TX in BlockMiné[indexBlock]) //PRIVATE
    Block b = getBlock_list(coinbase->userDB->blockChain)[indexBlock]; //Block miné
    UserUnit user = get_user_from_CB(coinbase,indexUserDB);
    char tag[10];
    user_to_string(tag, user);
    add_transaction(getTrans_list(b),"Coinbase",tag,money); // transaction à "UserN"
    
    coinbase->masseMoneitaire += money;
}

void add_user_to_cb(Coinbase coinbase){
    add_user_to_DB(coinbase->userDB);
}

void helicopter_money(Coinbase coinbase){
    Blockchain bc = coinbase->userDB->blockChain;
    Block b;
    Transactions transaction_list;
    int lastIndex,nbTransactionBlock; //Dernier block ajouté => Index du bloc auquel on ajouteras de la monais


    for(int i = 1; i<coinbase->userDB->nbUsers; i++){ //parcours tt les users, excepté userList[0]
        lastIndex = getNb_blocs(bc)-1;
        b = getBlock_list(bc)[lastIndex];
        transaction_list = getTrans_list(b);
        nbTransactionBlock = getNb_trans(transaction_list);
        
        if(nbTransactionBlock<MAX_TRANS)
            add_money(coinbase,50,i,lastIndex);//incrémente la masse monétaire
        else {
            if(lastIndex != getMax_size(bc)){
                transaction_list = create_transaction_list();
                add_block(bc,&transaction_list);
            }
            else {printf("\n*** Error : Max BlockChain size ***\n");}
        }
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
int randIntMax(int maxValue){ //PUBLIC
    srand(time(NULL));
    return rand()%maxValue;
}

