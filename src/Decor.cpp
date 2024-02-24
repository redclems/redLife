#include "Decor.hpp"
#include <iostream>


Decor::Decor(Position pos, char s, Couleur c, Carte* carte, bool cache, bool eau, bool marchable) 
    : Element(pos, s, c, TypeElement::DECOR, carte, marchable), cache(cache), eau(eau){
}

Decor::Decor(Position pos, char s, Couleur c, TypeElement ele, Carte* carte, bool cache, bool eau, bool marchable, int tempExistantMoyen) 
    : Element(pos, s, c, ele, carte, marchable, tempExistantMoyen), cache(cache), eau(eau){
}

bool Decor::estEau() {
    return this->eau;
}

bool Decor::estCache() {
    return this->cache;
}
