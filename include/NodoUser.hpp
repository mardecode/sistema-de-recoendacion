#pragma once
#include <iostream>
#include <map>
#include <set>
#include "math.h"
#include <utility> 
#include <vector>
#include <list> 

#include "NodoItem.hpp"


using  namespace std;


class NodoItem;


// typedef list< pair<float,NodoUser* > > k_vec; //k vecinos
class  NodoUser{
  public:
    int id ;
     //puntero a nodo item, float rating
    map<NodoItem * ,float>   items; //Relaciones

  
    NodoUser(int id);
    void add_item(float rating,  NodoItem * &);
    void knn(int,int,list< pair<float,NodoUser* > > &);
    void recomendacion(list< pair<float,NodoUser* > > &, list<pair<int ,float> > &);


};