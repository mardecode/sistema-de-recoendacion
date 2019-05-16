#pragma once

#include <map>
#include <vector>
#include "NodoItem.hpp"
#include "NodoUser.hpp"

class Grafo {

public:
    ~Grafo();

    int max = 300000;

    vector<NodoUser *> index_users;
    vector<NodoItem *> index_items;

    int size_items = 0;
    int size_users = 0;
    
    Grafo() : index_users(max,0) ,   index_items(max,0) {
    }

    //map<int,NodoUser *> index_users;
    //map<int, NodoItem*>   index_items;


    NodoUser * findUser(int);
    NodoItem * findItem(int);

    NodoUser * addUser(int);
    NodoItem * addItem(int);


};