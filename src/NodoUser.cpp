#include "NodoUser.hpp"

NodoUser::NodoUser(int id,map< int, NodoItem*> * & index_items){
    this->id  = id;
    this->index_items = index_items;
}

void  NodoUser::add_item(int rating,  int  id_item){
    auto encontrado = index_items->find(id_item);
    NodoItem * new_item ;
    if(encontrado  != index_items->end()){
        new_item=encontrado->second;
    }
    else{
      cout << "ERROR item not found " << endl;
      //new_item = new NodoItem(id_item);
    }
    items[id_item] = make_pair( rating, new_item);
}

void NodoUser::knn(){
  map<NodoUser*,list<pair<int,int> > > common_users;
  vector<int> ratings;

  //this->items (map):   idItem -> pair(rating,NodoItem*) 

  for (auto & item : this->items ){
      //item.first = key id
      //item.second = rating,nodoitem*
      int rating1 = item.second.first ;
      for (auto & user: item.second.second->users){
          int rating2 = user.second.first ;
         
          //Solo anade las pelicuas en comun, ejm
          //0x55896fb35010:  (3,3)    
          // 0x55896fb36ba0:  (5,4)    (5,5)    
          //0x55896fb39b30:  (5,4)    (5,3)    (5,4)    (4,5)    (5,4)    
          // 0x55896fb3cf40:  (5,5)  
          auto it = common_users.find(user.second.second);
          if(it!=common_users.end()){
              it->second.push_back(make_pair(rating1,rating2));
          }
          else{
              list<pair<int,int>> temp;
              temp.push_back(make_pair(rating1,rating2));
              common_users[user.second.second] = temp;
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
    for(auto & user : usersOrdenados){
        cout << user.second->id << endl;
    }

}