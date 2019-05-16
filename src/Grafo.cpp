#include "Grafo.hpp"


Grafo::~Grafo() {

}

NodoItem *  Grafo::findItem (int id){
    return  this->index_items.at(id) ;
}

NodoUser * Grafo::findUser (int id){
    return  this->index_users.at(id) ;
}

NodoUser * Grafo::addUser(int id){
    auto user = findUser(id) ;
    if ( user ) 
        return user;
    else{
        user = new NodoUser(id);
        this->index_users.at(id) = user;
        this->size_users ++;
        return user;
    }
}

NodoItem * Grafo::addItem(int id){
    auto item = findItem(id) ;
    if ( item ) 
        return item;
    else{
        item = new NodoItem(id);
        this->index_items.at(id) = item;
        this->size_items ++;
        return item;
    }
}