#pragma once

#include <map>
#include "NodoItem.hpp"
#include "NodoUser.hpp"

class Grafo {

public:
    Grafo();
    ~Grafo();

    map<int,NodoUser *> index_users;
    map<int, NodoItem*>   index_items;


    NodoUser * findUser(int);
    NodoItem * findItem(int);

    NodoUser * addUser(int);
    NodoItem * addItem(int);


};