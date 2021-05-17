#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../test/test.h"
#include "display.h"

int randMinMaxUsers(int min, int max){
    srand(time(NULL));
    return (rand() % (max+1 - min)) + min; 
}

void help(){
    printf("\n%s-*-*-*-* %s[%sHELP%s]%s *-*-*-*-%s\n",WHT,NRM,RED,NRM,WHT, NRM);
    printf("=>'%s-h%s': Affiche le message d'aide courant\n",CYN, NRM);
    printf("=>'%s-d%s': Choix de la difficulté %s(argument obligatoire)%s\n",MAG, NRM, GRN, NRM);
    printf("=>'%s-b%s': Choix du nombre de blocs à générer %s(argument obligatoire)%s\n",MAG, NRM, GRN, NRM);
    printf("=>'%s-t%s': Choix du nombre de transactions %s(argument obligatoire)%s\n",MAG, NRM, GRN, NRM);
    printf("====(%sNon implémenté %s)====\n",YEL, NRM);
    printf("    =>'%s-c%s': Cheater %s(numéro du bloc)%s [transaction à supprimer]%s\n",MAG, NRM, GRN, YEL, NRM);
}

bool isHelp(int argc, char **argv){
    int compteur = 0;
    for(int i = 1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0)
            compteur++;
    }
    if(compteur == 0) return false;
    return true;
}


int main(int argc, char *argv[]){
    int opttion_val = 0;
    int nbBlocks = 0,  difficulty = 0;
    for(int i = 0; i<argc;i++){
        if(strcmp(argv[i], "-h") == 0) {
            help(); 
            return 0;
        }
    }

    if(argc < 5 || argc > 8){
        fprintf(stderr,"\n => usage: ./%s -d (difficulty) -b (nbBlocs) [-c (numBlocModifier) [numTrans]]\n",argv[0]); // -c PAS IMPLEMENTER
        fprintf(stderr,"\n => \"./%s %s-h%s\" Pour afficher l'aide.\n",argv[0],CYN,NRM);
        exit(EXIT_FAILURE);
    }
    

    while((opttion_val = getopt(argc, argv,"d:hb:c:")) != -1){ // -c PAS IMPLEMENTER
        switch (opttion_val)
        {
        case 'h':
            help();
            break;
        case 'd':
            if (!isHelp(argc, argv))
                difficulty = atoi(optarg);
            break;
        case 'b':
            if (!isHelp(argc, argv))
                nbBlocks = atoi(optarg);
            break;
        case 'c': //PAS IMPLEMENTER
            if (!isHelp(argc, argv))
                printf("\n'-c' Non implémenté :(\n");
            exit(EXIT_FAILURE);
        case '?':
            fprintf(stderr,"Erreur option/argument.\n");
            exit(EXIT_FAILURE);
        default:
            fprintf(stderr,"\n[%sErreur%s] usage: %s -d (difficulty) -b (nbBlocs) [-c (numBlocModifier) [numTrans]]\n",RED,NRM,argv[0]);
            fprintf(stderr,"\n%s -h pour afficher l'aide.\n",argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    
    if(nbBlocks != 0 && difficulty !=0 ){
        
        Blockchain bc = create_blockchain(difficulty,nbBlocks);
        Coinbase cb = create_coin_base(bc);
        int nbUsers = randMinMaxUsers(2,MAX_USERS);

        
        for(int i = 0;i<nbUsers;i++)
            add_user_to_cb(cb);
        
        display_blockchain(bc, cb);
        display_users(cb, nbUsers);
        printf("    [%snbUsers %sAFTER%s] => %d (WITH CREATOR)\n",CYN,GRN,NRM,get_nb_user(get_DB_from_CB(cb)));
        display_users_index(cb, nbUsers);

        display_coinbase_helicopter(cb);
        helicopter_money(cb);
        printf("    [%sTOTAL AFTER %sHELICOPTER%s] => %.2f Bnb\n",GRN,MAG,NRM,get_masse_monetaire(cb));

        printf("\n+*+*+*+*+... %sRandomTransactions%s ...+*+*+*+*+\n\n",MAG,NRM);
        trans_aleatoire(cb);
        //display_coinbase_marche(cb);
        //printf("    [%sTOTAL AFTER %sMARCHE%s] => %.2f Bnb\n",GRN,MAG,NRM,get_masse_monetaire(cb));
        display_blockchain(bc, cb);
        delete_blockchain(bc);
        delete_coinbase(cb);
    }
    else{
        fprintf(stderr,"[%sErreur%s] Arguments Incorrecte.\n",RED,NRM);
        fprintf(stderr,"usage: %s -d (difficulty) -b (nbBlocs) [-c (numBlocModifier) [numTrans]]\n",argv[0]);
        fprintf(stderr,"\n%s -h pour afficher l'aide.\n",argv[0]);
        exit(EXIT_FAILURE);
    }
        
    return 0;
}