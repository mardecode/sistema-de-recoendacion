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

Grafo g; // Declaro glbalmente grafo

struct HelloHandler : public Http::Handler {
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request& request , Http::ResponseWriter writer) override{

    if (request.resource() == "/" && request.method() == Http::Method::Get) {
        Http::serveFile(writer, "static/index.html");
    }
    else{

        if (request.resource() == "/knn" && request.method() == Http::Method::Post){
            //writer.send(Http::Code::Ok, "Hello, World!");
                //cout << "->"<< request.body() <<endl;

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
                list<pair<int,float> > recomendacion;//
                
                string salida = "{";
                if(u) {
                    salida += " 'user': [";
                    u->knn(k,distancia,k_vecinos_cercanos);
                    
                    int c_vecinos = 0 ; 
                    for(auto & vecino : k_vecinos_cercanos){
                        salida += "{ 'user': " + to_string(vecino.second->id) + ",";
                        salida += "'distancia': " + to_string(vecino.first) + "}" ; 
                        if (c_vecinos < k_vecinos_cercanos.size()-1 ) salida += ",";
                        c_vecinos ++;
                    }

                    c_vecinos = 0;
                    salida += "],'recomendacion': ["; 
                    u->recomendacion(k_vecinos_cercanos,recomendacion);
                    for(auto & rec : recomendacion){
                        salida += "{'idItem':" + to_string(rec.first ) + ",";
                        salida += " 'rating': " + to_string(rec.second) + "}";
                        if (c_vecinos < recomendacion.size() -1 ) salida += ",";
                    }
                    salida+= "]";
                    //salida += to_string(recomendacion)

                }
                else {
                    cout << "no user" << endl;
                    salida+=" 'error': 'No se encontro el usuario' ";
                }

                salida += "}";
                auto fin = chrono::steady_clock::now();
                cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;
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
    FILE * ifs = fopen("/home/margarcuae/Documentos/tbd/parcial1/sistema-de-recoendacion/dataset/ratings.csv","r");
    // FILE * ifs = fopen("/home/luisbch/Documentos/sistema-de-recoendacion/bin/ml-latest-small/ratings.csv","r");

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
    Http::listenAndServe<HelloHandler>("*:9080");


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