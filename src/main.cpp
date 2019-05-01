#include "Grafo.hpp"
#include <stdlib.h> //ran
#include <string>

#include <vector> 
#include <cstdio>
#include <list>
#include <chrono>

int main(){

int iduser, idbook, timestamp ;
float rating;


//138493 users
FILE * ifs = fopen("/home/luisbch/Documentos/sistema-de-recoendacion/bin/ml-20m/ratings.csv","r");

//600 aprox users
//FILE * ifs = fopen("/home/luisbch/Documentos/sistema-de-recoendacion/bin/ml-latest-small/ratings.csv","r");
int rows = 0;
Grafo g;
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
        user->add_item(rating,idbook);
        item->add_user(rating,iduser);
        rows++;
    }
    fclose(ifs);
    cout << "Se cargaron " << rows << "filas"<<endl;
}
else{
  cout << "ERROR no se abrio el archivo" << endl;
}



    auto start = chrono::steady_clock::now();
    auto u = g.findUser(rand()%10000);
    if(u) u->knn();
    else cout << "no user" << endl;

    auto fin = chrono::steady_clock::now();
    cout <<"KNN: " <<chrono::duration_cast<chrono::milliseconds>(fin-start).count()<<endl;
  
  

  return  0;
}