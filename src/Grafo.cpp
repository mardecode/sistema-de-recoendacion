#include "Grafo.hpp"

Grafo::Grafo() {

}

Grafo::~Grafo() {

}

NodoItem *  Grafo::findItem (int id){
    auto it = this->index_items.find(id);
    if (it!= index_items.end() )
        return it->second;
    else
        return 0;
}

NodoUser * Grafo::findUser (int id){
    auto it = this->index_users.find(id);
    if (it!= index_users.end() ) 
        return it->second;
    else{
        return 0;
    }
}

NodoUser * Grafo::addUser(int id){
    auto user = findUser(id) ;
    if ( user ) 
        return user;
    else{
        user = new NodoUser(id);
        this->index_users[id] = user;
        return user;
    }
}

NodoItem * Grafo::addItem(int id){
    auto item = findItem(id) ;
    if ( item ) 
        return item;
    else{
        item = new NodoItem(id);
        this->index_items[id] = item;
        return item;
    }
}