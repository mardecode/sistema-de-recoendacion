#pragma once

#define f first
#define s second
#define rating_type float

#include <utility>
#include <list>
#include <vector>
#include <string>
using namespace std;

typedef list<pair<int,rating_type>> nodo;
typedef vector<nodo> v_nodos_users;
typedef vector< pair< string , nodo> > v_nodos_items;


class Grafo {

public:
    ~Grafo();

    int max = 300000;

    v_nodos_users index_users;
    v_nodos_items index_items;

    int size_items = 0;
    int size_users = 0;
    
    
    Grafo() : index_users(max,nodo()) ,   index_items(max, make_pair("",nodo())) {

    }

    void addRelacion(int id_user, int id_item, rating_type  rtg );
};