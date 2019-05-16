#include "Grafo.hpp"

Grafo::~Grafo() {
}

void Grafo::addRelacion(int id_user, int id_item, rating_type  rtg ){
    this->index_users.at(id_user).push_back( make_pair(id_item,rtg));
    this->index_items.at(id_item).s.push_back(make_pair(id_user,rtg));
}


void 