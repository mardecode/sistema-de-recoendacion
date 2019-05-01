#include "NodoUser.hpp"

NodoUser::NodoUser(int id,map< int, NodoItem*> * & index_items){
    this->id  = id;
    this->index_items = index_items;
}

void  NodoUser::add_item(int rating,  int  id_item){
    auto encontrado = index_items->find(id_item);
    NodoItem * new_item ;
    if(encontrado  != index_items->end()){
        new_item=encontrado->second;
    }
    else{
      cout << "ERROR item not found " << endl;
      //new_item = new NodoItem(id_item);
    }
    items[id_item] = make_pair( rating, new_item);
}