#include "Grafo.hpp"

Grafo::~Grafo() {
}

void Grafo::addRelacion(int id_user, int id_item, rating_type  rtg ){

    if(this->index_items.at(id_item).s.size() == 0) this->size_items++;
    if(this->index_users.at(id_user).size() == 0 ) this->size_users++;

    this->index_users.at(id_user).push_back( make_pair(id_item,rtg));
    this->index_items.at(id_item).s.push_back(make_pair(id_user,rtg));
}


rating_type Grafo::calcDeriv(int i1, int i2 ){

    auto item1 = this->index_items.at(i1).s;
    auto item2 = this->index_items.at(i2).s;
    int cont = 0;
    rating_type sumatoria = 0;
    map<int,rating_type> map_der;
    for(auto &it:item1){ //recorriendo item1
        map_der[it.f] = it.s;       
    }

    for(auto &it:item2){ //recorriendo item 2
        auto existe = map_der.find(it.f);
        if(existe != map_der.end()){
            cont ++;
            sumatoria += existe->s - it.s;
        }
    }
    return sumatoria/cont;
}

void Grafo::calcFila(int i){
    vector<rating_type> ratings_sumas(max_items,0);
    vector<int> ratings_sumas_cont(max_items,-1);

    auto & item1  = this->index_items.at(i).s;
    for( auto &u : item1){
        auto & lista_items = this->index_users.at(u.f);
        
        for (auto &ix : lista_items){
            ratings_sumas.at(ix.f) += u.s - ix.s;
            ratings_sumas_cont.at(ix.f) ++;
        }
    }
    
    //int n_hilos = 4;
    for (int i = 0; i < ratings_sumas.size() ; i+= 1)
        ratings_sumas.at(i) /=  ratings_sumas_cont.at(i);

    
    // vector<thread> mishilos;
    // for (int i = 0; i < n_hilos; i++){
    //     int id_h = i;
    //     //cout << i << endl;
    //     mishilos.push_back( thread([&ratings_sumas, &ratings_sumas_cont , &id_h, &n_hilos] {
    //         for (int i = id_h; i < ratings_sumas.size() ; i+= n_hilos){
    //             //cout << "i " <<  i << endl;
    //             ratings_sumas.at(i) /=  ratings_sumas_cont.at(i);
    //         }
    //     }));  
    // }

    // for (int i=0; i<n_hilos; i++) mishilos.at(i).join();
    
        
    
}