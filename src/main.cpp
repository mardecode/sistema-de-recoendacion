#include "Grafo.hpp"

#include <cstdio>

#include <stdlib.h> //random
#include <string>
#include <vector> 
#include <list>
#include <chrono> ///tiempo

int main(){

int iduser, idbook, timestamp ;
float rating;

//138493 users
FILE * ifs = fopen("/home/margarcuae/Documentos/tbd/parcial1/sistema-de-recoendacion/dataset/ratings.csv","r");
//FILE * ifs = fopen("/home/luisbch/Documentos/sistema-de-recoendacion/bin/ml-latest-small/ratings.csv","r");

//600 aprox users
int rows = 0;
Grafo g;

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


// ───  KNN ──────────────────────────────────────────────────────────────────
// for(int i = 0;i<3;i++){
// }

    auto start = chrono::steady_clock::now();

    auto u = g.findUser(rand()%10000); //prueba
    cout<<u<<" user random \n";
    if(u) u->knn(10,1);
    else cout << "no user" << endl;

    auto fin = chrono::steady_clock::now();
    cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;

//*******************
    start = chrono::steady_clock::now();

    // auto u = g.findUser(rand()%10000); //prueba
    cout<<u<<" user random \n";
    if(u) u->knn(10,3);
    else cout << "no user" << endl;

    fin = chrono::steady_clock::now();
    cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;


  return  0;
}

// ─── RECOMENDACION ──────────────────────────────────────────────────────────────
