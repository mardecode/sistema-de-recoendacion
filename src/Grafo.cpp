#include "Grafo.hpp"

Grafo::~Grafo() {
}


void Grafo::addRelacion(int id_user, int id_item, rating_type  rtg ){

    if(this->index_items.at(id_item).s.size() == 0) this->size_items++;
    if(this->index_users.at(id_user).size() == 0 ) this->size_users++;

    this->index_users.at(id_user).push_back( make_pair(id_item,rtg));
    this->index_items.at(id_item).s.push_back(make_pair(id_user,rtg));

    this->usrs_average.at(id_user).f += rtg;
    this->usrs_average.at(id_user).s ++;

    this->usrs_squares.at(id_user) += rtg*rtg;
}

void Grafo::knn(int u1, multimap<rating_type,int>&knn){
    auto & user1 = this->index_users.at(u1) ;
    vector<list<pair<rating_type,rating_type>>> common_users(this->max_users,list<pair<rating_type,rating_type>>());

    //Hallar usuarios en comun
    for(auto &item : user1){
        auto & l_users = this->index_items.at(item.f).s;
        for ( auto & user_c : l_users){
            //usuarios[ user_c.int   ]  ->  () , () , () ... 
            common_users.at(user_c.f).push_back(make_pair( item.s , user_c.second));
        }
    }
    //Calcular coseno contra ellos
    for (int i = 0; i < this->max_users; i++){
        if( !common_users.at(i).empty() && i!=u1 ){
            knn.insert(make_pair(this->euclidiana(u1, i,common_users) ,i));
        }
    }

}


rating_type Grafo::coseno(int u1, int u2,vector<list<pair<rating_type,rating_type>>> & common_users){
    //cout << "calculando cos"<<u1<<" "<<u2<< endl;
    
    auto list_distancias = common_users.at(u2);

    rating_type xx = this->usrs_squares.at(u1);
    rating_type yy = this->usrs_squares.at(u2);

    rating_type xy = 0;
    for(auto & distancia : list_distancias){
        xy+= distancia.f * distancia.s;
    }

    return xy/(sqrt(xx)*sqrt(yy));

}

rating_type Grafo::euclidiana(int u1, int u2, vector<list<pair<rating_type,rating_type>>> & common_users){
    auto list_distancias = common_users.at(u2);

    rating_type xy = 0;
    for(auto & distancia : list_distancias){
        xy+= (distancia.f - distancia.s) * (distancia.f - distancia.s);
    }

    return sqrt(xy);
}

// ____________ SLOPE ONE _____
void Grafo::calcFila_slope(int i, vector<rating_type> & ratings_sumas , vector<int> & ratings_sumas_cont ){
    //vector<rating_type> ratings_sumas(max_items,0);
    //vector<int> ratings_sumas_cont(max_items,-1);

    auto & lista_users  = this->index_items.at(i).s;
    for( auto &u : lista_users){
        auto & lista_items = this->index_users.at(u.f);
        
        //if (i != u.first){
        //cout << "id_item:"<< i <<">>>" <<" id_user:"<< u.first <<  endl ;
        for (auto &ix : lista_items){
            if( ix.f != i){
                //cout << "ix.f ( item ): "<< ix.f << "   u.s c: " << u.s << " ix.s " << ix.s << endl;
                ratings_sumas.at(ix.f) += ix.s - u.s     ;
                ratings_sumas_cont.at(ix.f) ++;
            }
        }
        //}
    }
    for (int i = 0; i < ratings_sumas.size() ; i+= 1)
        ratings_sumas.at(i) /=  ratings_sumas_cont.at(i);    
}


rating_type Grafo::predecir_slope(int u,int i){
    vector<rating_type> ratings_sumas(max_items,0);
    vector<int> ratings_sumas_cont(max_items,0);

    this->calcFila_slope(i, ratings_sumas, ratings_sumas_cont);
    
    // cout << endl;
    // for( auto r :  ratings_sumas) cout  << r << "   " ; 
    // cout << endl; 
    // for( auto r :  ratings_sumas_cont) cout  << r << "   " ; 
    // cout << endl; 

    auto user = this->index_users.at(u);

    rating_type numerador = 0;
    for(auto & item_visto : user ){
        // cout << "dev " <<ratings_sumas.at(item_visto.f) << "  ";
        // cout << "u " << item_visto.s << " ";
        // cout << "c " <<  ratings_sumas_cont.at(item_visto.f) << endl;
        numerador+= (ratings_sumas.at(item_visto.f)  + item_visto.s)*ratings_sumas_cont.at(item_visto.f);
    }

    
    int denominador = 0;
    for(auto & ci : ratings_sumas_cont ){
        if ( ci > 0)
            denominador += ci ; 
        // else if ( ci == 0)
        //     cout << "Cero" << endl;
    }
    //cout << "num " << numerador << endl;
    //cout << "den " << denominador << endl;
    return numerador/denominador;
}



// ─── COSENO AJUSTADO ────────────────────────────────────────────────────────────
void Grafo::cosenoAjustado( int id_item, vector<rating_type> & up){
    // vector<rating_type> up (this->max_items,0);
    vector<rating_type> down_a(this->max_items,0);
    vector<rating_type> down_b(this->max_items,0);

    auto & item_usrs = this->index_items.at(id_item).s;

    for (auto & user: item_usrs){
        auto & list_items = this->index_users.at(user.f);
        auto average = this->usrs_average.at(user.f);
        auto avr_real = average.f/average.s;
        for(auto & item: list_items){
            if(item.f != id_item){
                
                up.at(item.f) += (user.s - avr_real) * (item.s-avr_real);
                down_a.at(item.f) += (user.s - avr_real)*(user.s - avr_real);
                down_b.at(item.f) += (item.s - avr_real)*(item.s - avr_real);
            }
        }

    }

    for(int i = 0 ;i<this->max_items;i++){
    up.at(i) = up.at(i) /(sqrt(down_a.at(i))*sqrt(down_b.at(i)));
    // cout<<"Final *****" << up.at(i)<<endl;
    }

}

void Grafo::recomendacionCoseno(int id_user,int id_item){
// vector<rating_type> up (this->max_items,0);
    

    // for (int i=0; i<n_hilos; i++) mishilos.at(i).join();
    
}


