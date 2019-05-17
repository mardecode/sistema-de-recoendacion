#pragma once

#define f first
#define s second
#define rating_type float
#include <iostream>
#include <utility>
#include <list>
#include <set>
#include <vector>
#include <string>
#include <map> 
#include <thread>
using namespace std;

typedef list<pair<int,rating_type>> nodo;
typedef vector<nodo> v_nodos_users;
typedef vector< pair< string , nodo> > v_nodos_items;


class Grafo {

public:
    ~Grafo();

    int max_users = 4;
    int max_items = 3;

    v_nodos_users index_users;
    v_nodos_items index_items;

    int size_items = 0;
    int size_users = 0;
    
    
    Grafo() : index_users(max_users,nodo()) ,   index_items(max_items, make_pair("",nodo())) {

    }

    void addRelacion(int id_user, int id_item, rating_type  rtg );

    rating_type calcDeriv(int i1 ,int i2 );

    void calcFila_slope(int i, vector<rating_type> & ratings_sumas , vector<int> & ratings_sumas_cont );
    rating_type predecir_slope(int u,int i);

};