#pragma once
#include <iostream>
#include <map>
#include <set>
#include "math.h"
#include <utility> 
#include "NodoItem.hpp"

using  namespace std;

class NodoItem;
class NodoUser;
typedef pair<int, NodoItem*>  dato_item;
typedef pair<int, NodoUser*>  dato_user;

class  NodoUser{
  public:
     int id ;
     map<int,dato_item>   items;
     map< int, NodoItem*> *  index_items;
  
  NodoUser(int id,map< int, NodoItem*> * & index_items );
  void add_item(int rating,  int  id_item);

};