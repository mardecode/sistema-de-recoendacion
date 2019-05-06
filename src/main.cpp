#include "Grafo.hpp"

#include <cstdio>
#include <stdlib.h> //random
#include <string>
#include <vector> 
#include <list>
#include <chrono> ///tiempo

// PISTACHE HEADERS
#include <pistache/endpoint.h>
#include <iostream>
//sudo apt-get install libssl-dev
//https://github.com/oktal/pistache
using namespace Pistache;

//RAPIDJSON HEADERS
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;
//http://rapidjson.org/index.html


typedef list<pair<float,NodoUser*> > k_vec; //k vecinos

//typedef list < tuple < user,  distancia , influencia , rating,  rating*influencia > 
typedef list < tuple < NodoUser*,  float , float , float , float   >  > k_vec_rest;
Grafo g; // Declaro globalmente grafo

struct HelloHandler : public Http::Handler {
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request& request , Http::ResponseWriter writer) override{

    if (request.resource() == "/" && request.method() == Http::Method::Get) {
        Http::serveFile(writer, "static/index.html");
    }
    else{

        if (request.resource() == "/knn" && request.method() == Http::Method::Post){
                
                //Copia Contenido a json
                int n = request.body().length();
                char json[n + 1]; 
                strcpy(json, request.body().c_str()); 
                            
                cout << "->" <<json << endl;
                Document d;
                d.Parse(json);

                assert(d.IsObject());
                cout << "Es Documento" << endl;

                int iduser = d["iduser"].GetInt();
                int distancia = d["distancia"].GetInt();
                int k = d["k"].GetInt();



                //KNN PROCEDURE
                auto start = chrono::steady_clock::now();
                auto u = g.findUser(iduser); //prueba
                k_vec k_vecinos_cercanos; //k vecinos
                // list<pair<int,float> > recomendacion;//
                map<int,pair<float,int> > recomendacion;
                
                string salida = "{";
                if(u) {
                    salida += " \"user\": [";
                    u->knn(k,distancia,k_vecinos_cercanos);
                    
                    int c_vecinos = 0 ; 
                    for(auto & vecino : k_vecinos_cercanos){
                        salida += "{ \"user\": " + to_string(vecino.second->id) + ",";
                        salida += "\"distancia\": " + to_string(vecino.first) + "}" ; 
                        if (c_vecinos < k_vecinos_cercanos.size()-1 ) salida += ",";
                        c_vecinos ++;
                    }

                    c_vecinos = 0;
                    salida += "],\"recomendacion\": ["; 
                    u->recomendacion(k_vecinos_cercanos,recomendacion);
                    for(auto & rec : recomendacion){
                        salida += "{\"idItem\":" + to_string(rec.first ) + ",";
                        salida += " \"rating\": " + to_string(rec.second.first/rec.second.second) + "}";
                        if (c_vecinos < recomendacion.size() -1 ) salida += ",";
                        c_vecinos ++;
                    }
                    salida+= "]";
                    //salida += to_string(recomendacion)

                }
                else {
                    cout << "no user" << endl;
                    salida+=" \"error\": \"No se encontro el usuario\" ";
                }

                auto fin = chrono::steady_clock::now();
                //cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;
                salida += ",\"time\":  " +  to_string(chrono::duration_cast<chrono::milliseconds>(fin-start).count()) ; 
                salida += "}";
                //END KNN procedure 

                cout << "Salida: "<< salida << endl;        
                writer.send(Http::Code::Ok, salida, MIME(Application, Json));


        }
        if (request.resource() == "/item" && request.method() == Http::Method::Post){
            //Copia Contenido a json
            int n = request.body().length();
            char json[n + 1]; 
            strcpy(json, request.body().c_str()); 
                        
            cout << "->" <<json << endl;
            Document d;
            d.Parse(json);

            assert(d.IsObject());
            cout << "Es Documento" << endl;

            int iduser = d["iduser"].GetInt();
            int distancia = d["distancia"].GetInt();
            int k = d["k"].GetInt();
            int item_b = d["item"].GetInt();

            auto start = chrono::steady_clock::now();
            auto u = g.findUser(iduser); // Encuentra User
            auto i = g.findItem(item_b); // Encuentra User
            k_vec k_vecinos_cercanos; //k vecinos

            string salida = "{";
                if(u && i) {
                    u->knn_restricto(k,distancia,i,k_vecinos_cercanos);
                    k_vec_rest kvecinosrest;
                    cout << "wayaba "<< endl;
                    float rating = u->get_influencias(k_vecinos_cercanos,i,kvecinosrest);
                    // list < tuple < user,  distancia , influencia , rating,  rating*influencia > 
                    salida += "\"rating\":" + to_string(rating) + ",";
                    salida += " \"user\": [";
                    int c_vecinos = 0 ; 
                    for(auto & vecino : kvecinosrest){
                        salida += "{ \"user\": " + to_string(get<0>(vecino)->id) + ",";
                        salida += "\"distancia\": " + to_string(get<1>(vecino)) + "," ; 
                        salida += "\"influencia\": " + to_string(get<2>(vecino)) + "," ; 
                        salida += "\"rating\": " + to_string(get<3>(vecino)) + "," ; 
                        salida += "\"ratingxinfluencia\": " + to_string(get<4>(vecino)) + "}" ; 
                        if (c_vecinos < k_vecinos_cercanos.size()-1 ) salida += ",";
                        c_vecinos ++;
                    }

                    c_vecinos = 0;
                    salida += "]";

                }
                else {
                    cout << "no user o Item" << endl;
                    salida+=" \"error\": \"No se encontro el usuario o Item\" ";
                }

                auto fin = chrono::steady_clock::now();
                //cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;
                salida += ",\"time\":  " +  to_string(chrono::duration_cast<chrono::milliseconds>(fin-start).count()) ; 
                salida += "}";
                //END KNN procedure 

                cout << "Salida: "<< salida << endl;        
                writer.send(Http::Code::Ok, salida, MIME(Application, Json));









        }
    }

  }
};


int main(){
    int iduser, idbook, timestamp ;
    float rating;

    //138493 users
    //FILE * ifs = fopen("/home/margarcuae/Documentos/tbd/parcial1/sistema-de-recoendacion/dataset/bandas.csv","r");
     FILE * ifs = fopen("dataset/ml-latest-small/ratings.csv","r");

    //600 aprox users
    int rows = 0;

    // ─── LECTURA DEL ARCHIVO ────────────────────────────────────────────────────────
    if (ifs) {
        cout << "Archivo Abierto" << endl;
        char header[100]; 
        fscanf(ifs,"%s", header);

        // Lectura toma : 14 segs  // MEJORAR 
        while ( fscanf(ifs, "%d,%d,%f,%d", &iduser, &idbook, &rating, &timestamp) >= 4) {
            //Inserción toma 16 segs aprox 
            auto user = g.addUser(iduser);
            auto item = g.addItem(idbook);
            //Quiza se deba parallelizar , guardar to en un vector 
            // dividir el vector en 4 , y soltar 4 threads , cada uno realiza las inserciones
            user->add_item(rating,item);  
            item->add_user(rating,user);  
            rows++;
        }
        fclose(ifs);
        cout << "Se cargaron " << rows << "filas"<<endl;
    }
    else{
    cout << "ERROR no se abrio el archivo" << endl;
    }
    // ─── FIN LECTURA DEL ARCHIVO CSV ────────────────────────────────────────────────


    //Start Server
    Http::listenAndServe<HelloHandler>("*:9081");


// ───  KNN ──────────────────────────────────────────────────────────────────
// for(int i = 0;i<3;i++){
// }

    // auto start = chrono::steady_clock::now();

    // auto u = g.findUser(rand()%10000); //prueba
    // k_vec k_vecinos_cercanos; //k vecinos
    // list<pair<int ,float> > recomendacion;//
    // cout<<u<<" user random \n";
    // if(u) {
    //   u->knn(10,3,k_vecinos_cercanos);
    //   u->recomendacion(k_vecinos_cercanos,recomendacion);
    //   }
    // else cout << "no user" << endl;

    // auto fin = chrono::steady_clock::now();
    // cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;

  


  return  0;
}

// ─── RECOMENDACION ──────────────────────────────────────────────────────────────