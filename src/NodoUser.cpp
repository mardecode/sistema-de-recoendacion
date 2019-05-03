#include "NodoUser.hpp"

typedef list<pair<float,float> > list_ratings_xuser;

NodoUser::NodoUser(int id){
    this->id  = id;
}

void  NodoUser::add_item(float rating,  NodoItem *  &new_item){
    this->items[new_item] = rating;
}


void NodoUser::knn(int k){
  map<NodoUser*, list_ratings_xuser > common_users; 
  
  for (auto & item : this->items ){

      float rating1 = item.second;

      for (auto & user: item.first->users){
          int rating2 = user.second;
         
          //Solo anade las pelicuas en comun, ejm
          //0x55896fb35010:  (3,3)    
          // 0x55896fb36ba0:  (5,4)    (5,5)    
          //0x55896fb39b30:  (5,4)    (5,3)    (5,4)    (4,5)    (5,4)    
          // 0x55896fb3cf40:  (5,5)  

          auto it = common_users.find(user.first);
          if(it!=common_users.end()){
              it->second.push_back(make_pair(rating1,rating2));
          }
          else{
              list_ratings_xuser temp;
              temp.push_back(make_pair(rating1,rating2));
              common_users[user.first] = temp;
          }
      }
  }
    //Remove, Yo mismo
    auto it=common_users.find(this);
    common_users.erase (it);

    //FIN , OUT -> common_user :    Nodo* -> lista {  (r1,r2), (r1,r2), (r1,r2) , (r1,r2)  }

  

    //Distancia Manhattam
    multimap<float , NodoUser* > usersOrdenados;
    for(auto & user : common_users ) {
        auto userP = user.first;

        float distancia = 0  ;
        for (auto & item : user.second){
            distancia += abs(item.first - item.second);
        }

        usersOrdenados.insert(make_pair(distancia,userP));
    }


    //res, knn
    int i =0 ; 
    for(auto & user : usersOrdenados){
        cout << user.second->id << endl;
        if (i>= k) break;
        i++;
    }

}