#pragma once

#include <iostream>
#include <map>
#include <set>
#include "math.h"
#include <utility> 

#include "NodoUser.hpp"
using  namespace std;

class NodoItem;
class NodoUser;

typedef pair<int, NodoUser*>  dato_user;

class  NodoItem {
    public:
      int id;
      map<int,dato_user >  users;
      map<int,NodoUser *> * index_users;
      NodoItem(int,map<int,NodoUser *> * & index_users);
      //~NodoItem();
      void add_user(int rating,  int  id_user);
}
;
