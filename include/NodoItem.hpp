#pragma once

#include <iostream>
#include <map>
#include <set>
#include "math.h"
#include <utility> 

#include "NodoUser.hpp"
using  namespace std;

class NodoUser;


class  NodoItem {
    public:
      int id;
      map<NodoUser *,float >  users;

      NodoItem(int);
      void add_user(int rating,  NodoUser* &  id_user);
      //~NodoItem();
}
;
