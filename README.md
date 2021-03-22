# s4project

_Tous les outils pour créer la blockchain :_
```
#include "blockchain.h" // ou le chemin vers le fichier

int main(void) {
  Blockchain bc = create_blockchain();
  
  Transactions tList = create_transaction_list();
  add_transaction(tList, "Momo", "Gabou", 0.02);

  add_block(bc, &tList);
  
  delete_blockchain(bc);
  delete_transaction_list(tList);
  return 0;
}
```


*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*

Le reste est visible dans les .h, mais ne devrait pas être utilisé hors debug ou vérifications quelconques.
Sur le principe on pourrait les cacher, mais on en a besoin pour vérifier que tout fonctionne comme prévu
