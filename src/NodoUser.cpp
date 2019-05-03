#include "NodoUser.hpp"
#include "distancias.hpp"

typedef list<pair<float,float> > list_ratings_xuser;

NodoUser::NodoUser(int id){
    this->id  = id;
}

void  NodoUser::add_item(float rating,  NodoItem *  &new_item){
    this->items[new_item] = rating;
}

// ─── KNN ────────────────────────────────────────────────────────────────────────
void NodoUser::knn(int k,int dist){
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

// ─── ESCOGIENDO LA DISTANCIA ────────────────────────────────────────────────────
    if(dist  == 1){
        multimap<float , NodoUser* > usersOrdenados;
        manhattan(common_users,usersOrdenados);
        k_vecinos(usersOrdenados,k);
    }
    else if(dist ==2){
        multimap<float , NodoUser* > usersOrdenados;
        euclidiana(common_users,usersOrdenados);
        k_vecinos(usersOrdenados,k);
    }
    else if(dist ==3){
        multimap<float , NodoUser*,greater <float> > usersOrdenados;
        pearson(common_users,usersOrdenados);
        k_vecinos(usersOrdenados,k);
    }
    else if(dist ==4){
        multimap<float , NodoUser*,greater <float> > usersOrdenados;
        coseno_soft(common_users,usersOrdenados);
    }
 
}

// ─── RECOMENDACION ──────────────────────────────────────────────────────────────
void recomendacion(){
    
}