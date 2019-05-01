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
class NodoUser;

//ratin,Nodo*Item
typedef pair<int, NodoItem*>  dato_item;


class  NodoUser{
  public:
     int id ;
     map<int,dato_item>   items;
     map< int, NodoItem*> *  index_items;
  
  NodoUser(int id,map< int, NodoItem*> * & index_items );
  void add_item(int rating,  int  id_item);

  void knn();

};