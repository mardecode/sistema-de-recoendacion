#include "NodoItem.hpp"

NodoItem::NodoItem(int  id){
   this->id =  id;
}

void  NodoItem::add_user(float rating,NodoUser* & new_user){
    
    this->users[new_user] = rating;
}



