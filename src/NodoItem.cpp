#include "NodoItem.hpp"

NodoItem::NodoItem(int  id,map<int,NodoUser *> * & index_users){
   this->id =  id;
   this->index_users = index_users;
}

void  NodoItem::add_user(int rating,  int  id_user){
    auto encontrado = index_users->find(id_user);
    NodoUser * new_user ;
    if(encontrado  != index_users->end()){
        new_user=encontrado->second;
    }
    else{
      cout << "ERROR user not found " << endl;;
      //new_user = new NodoUser(id_user,this->index_users);
    }
    users[id_user] = make_pair( rating, new_user);
  }


