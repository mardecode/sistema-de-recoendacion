#include "NodoItem.hpp"

NodoItem::NodoItem(int  id){
   this->id =  id;
}

void  NodoItem::add_user(int rating,NodoUser* & new_user){
    
    this->users[new_user] = rating;
}



