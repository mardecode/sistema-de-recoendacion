#include "Grafo.hpp"

Grafo::Grafo() {

}

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
        return item;
    }
}