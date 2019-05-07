#pragma once
#include <iostream>
#include <map>
#include <set>
#include "math.h"
#include <utility> 
#include <list> 

#include "NodoItem.hpp"


using  namespace std;


class NodoItem;
class NodoUser;

// typedef list< pair<float,NodoUser* > > k_vec; //k vecinos
//typedef list < tuple < user,  distancia , influencia , rating,  rating*influencia > 
typedef list < tuple < NodoUser*,  float , float , float , float   >  > k_vec_rest;
class  NodoUser{
  public:
    int id ;
     //puntero a nodo item, float rating
    map<NodoItem * ,float>   items; //Relaciones

  
    NodoUser(int id);
    void add_item(float rating,  NodoItem * &);
    void knn(int,int,list< pair<float,NodoUser* > > &);
    void recomendacion(list< pair<float,NodoUser* > > &, map<NodoItem*,pair<float,int> > &,float &umbral);

    void knn_restricto(int k, int dist, NodoItem  * & , list< pair<float,NodoUser* > > & );
    float get_influencias(list< pair<float,NodoUser* > > & k_vecinos_cercanos,NodoItem * , k_vec_rest & );

};