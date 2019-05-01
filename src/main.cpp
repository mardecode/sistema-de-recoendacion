#include "Grafo.hpp"
#include <stdlib.h> //ran
#include <string>

#include <vector> 
#include <cstdio>
#include <list>


int main(){

int iduser, idbook, timestamp ;
float rating;


FILE * ifs = fopen("/home/luisbch/Documentos/sistema-de-recoendacion/bin/ml-20m/ratings.csv","r");
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



  return  0;
}