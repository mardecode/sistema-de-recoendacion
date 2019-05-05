// using namespace std;
#pragma once

#include "NodoItem.hpp"
#include "NodoItem.hpp"
#include "math.h"

typedef list<pair<float,float> > list_ratings_xuser;
typedef map<NodoUser*, list_ratings_xuser > common_users;

typedef multimap<float , NodoUser* > users_ordenados;
typedef multimap<float , NodoUser* ,greater<float> > users_ordenados_des;

typedef list<pair<float,NodoUser*> > k_vec; //k vecinos

int hola(){
    std::cout<<"FUNCIONO \n";
    return 1;
}

void manhattan(common_users & cm_usrs, users_ordenados & usrs_ord){
    for (auto &usr : cm_usrs){
        auto p_user = usr.first;
        float dist = 0;
        cout<<"_______________"<<endl;
        cout<<"USER ID "<<p_user->id<<endl;
        for(auto &item : usr.second){
            dist += abs(item.first-item.second);
            cout<<item.first<<" - "<<item.second<<endl;
        }
        cout<<"Distancia TOTAL "<<dist<<"\n ";
        usrs_ord.insert(make_pair(dist,p_user));
    }

}

void euclidiana(common_users & cm_usrs, users_ordenados &usrs_ord){
    for(auto &usr :cm_usrs){
        auto p_usr = usr.first;
        float dist = 0;
        cout<<"_______________"<<endl;
        cout<<"USER ID "<<p_usr->id<<endl;
        for(auto &item : usr.second){
            dist += pow(item.first - item.second, 2);
        }
        cout<<"Distancia TOTAL "<<dist<<"\n ";
        usrs_ord.insert(make_pair(dist,p_usr));
    }
}

void pearson(common_users & cm_usrs, users_ordenados_des & usrs_ord){
    float xy, x, y, x2, y2;

    for(auto &usr :cm_usrs){
        auto p_usr = usr.first;
        xy = x = y = x2 = y2 = 0;
        int n = 0;
        cout<<"_______________"<<endl;
        cout<<"USER ID "<<p_usr->id<<endl;
        for(auto &item : usr.second){
            xy += item.first * item.second;
            x2 += pow(item.first,2);
            y2 += pow(item.second,2);
            x += item.first;
            y += item.second;
            n += 1;
        }
        float up = xy -((x*y)/n);
        float down = sqrt(x2 -(pow(x,2)/n) ) * sqrt(y2 -(pow(y,2)/n) );
        float resp;
        if(down == 0) resp = 0;
        else resp = up/down;    
        cout<<"Distancia TOTAL "<<resp<<"\n ";

        usrs_ord.insert(make_pair(resp,p_usr));
    }
}


void coseno_soft(common_users cm_usrs, users_ordenados_des & usrs_ord){
    float xy, x2, y2;
    for (auto &usr : cm_usrs){
        auto p_user = usr.first;
        xy = x2 = y2 = 0;
        cout<<"_______________"<<endl;
        cout<<"USER ID "<<p_user->id<<endl;
        for(auto &item : usr.second){
            xy += item.first * item.second;
            x2 += pow(item.first,2);
            y2 += pow(item.second,2);
        }
        float resp = xy/(sqrt(x2)*sqrt(y2));
                cout<<"Distancia TOTAL "<<resp<<"\n ";

        usrs_ord.insert(make_pair(resp,p_user));
    }
}

// ─── FUNCIONES ADICIONALES ──────────────────────────────────────────────────────

void k_vecinos(users_ordenados & users, int & k, k_vec &resp ){
    int i =0 ; 
    for(auto & user : users){
        if (k <= i) break;
        cout << user.second->id << endl;
        resp.push_back(make_pair(user.first,user.second));
        i++;
    }
}

void k_vecinos(users_ordenados_des & users, int & k,k_vec &resp ){
    int i =0 ; 
    for(auto & user : users){
        if (k <= i) break;
        cout << user.second->id << endl;
        resp.push_back(make_pair(user.first,user.second));
        i++;
    }
}
