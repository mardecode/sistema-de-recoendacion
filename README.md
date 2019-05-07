# Sistema de Recomendación
Sistema de recomendación algoritmo KNN basado en grafos.
Curso : Tópicos en Base de Datos

### Integrantes:
- Lacuaña Apaza Margarita
- Bernal Chahuayo Luis Antonio

## Detalles de Implementación:
La estructura usada es un grafo, de la forma:
```c++
class Grafo {
public:
    Grafo();
    map<int,NodoUser*>   index_users;
    map<int,NodoItem*>   index_items;
```
Así cada nodo es indexado usando su *id*.

![Estructura Grafo](/images/grafo.png)

Además cada NodoUser y NodoItem tiene la forma:
```c++
class  NodoUser{
  public:
    int id ;
    //puntero a nodo item, float rating
    map<NodoItem * ,float>   items; //Relaciones 
    NodoUser(int id);
```
y el NodoItem:
```c++
class  NodoItem {
    public:
      int id;
      string nombre;
      map<NodoUser *,float >  users;
      NodoItem(int);
```
### KNN
Por lo tanto realizar un KNN quedaría de la siguiente forma:
```c++
typedef list<pair<float,NodoUser*> > k_vec; //k vecinos 
void NodoUser::knn(int k,int dist, k_vec &k_vecinos_cercanos){
  map<NodoUser*, list_ratings_xuser > common_users; 
    for (auto & item : this->items ){ //Recorremos todos los items del usuario (this)
        float rating1 = item.second;
        for (auto & user: item.first->users){ //Recorremos todos los usuarios que han visto el item
            float rating2 = user.second;
            auto it = common_users.find(user.first);
            if(it!=common_users.end()){ // Y los añadimos a la lista de vecinos comunes ( Common_users )
                it->second.push_back(make_pair(rating1,rating2));
            }
            else{
                list_ratings_xuser temp;
                temp.push_back(make_pair(rating1,rating2));
                common_users[user.first] = temp;
            }
        }
    }
```

Una vez obtenidos los usarios en común que cumplen: "(usuarioPorElQueSePregunta)-[rating1]->(Movie x)<-[rating2]-(Usuario)" (Syntaxis Cypher-Neo4j ) se pueden hallar las distancias:

```c++
multimap<float , NodoUser* > usersOrdenados; //Ordena los vecinos de acuerdo a la menor distancia
manhattan(common_users,usersOrdenados);
k_vecinos(usersOrdenados,k,k_vecinos_cercanos);
```

## Lenguaje
- C++17

## Librerías Utilizadas
- [Pistache C++](http://pistache.io/): Librería para crear y recibir conexiones HTTP.
- [Rapidjson](http://rapidjson.org): Librería para parsear JSONs.

## Compilación
```
make
```

## Ejecutar 
```
make run
```

Abrir en el navegador: "http://localhost:8091"


## Formato CSV
```
idItem,idUser,rating,timestamp
343,3434,3.4,23232
343,3434,3.4,23232
```
