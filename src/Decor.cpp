#include "Decor.hpp"
#include <iostream>


Decor::Decor(Position pos, char s, CouleurAnimal c, Carte* carte, bool cache, bool eau, bool marchable) 
    : Element(pos, s, c, TypeElement::DECOR, carte, marchable), cache(cache), eau(eau){
}

Decor::Decor(Position pos, char s, CouleurAnimal c, TypeElement ele, Carte* carte, bool cache, bool eau, bool marchable) 
    : Element(pos, s, c, ele, carte, marchable), cache(cache), eau(eau){
}

Decor::Decor() : Element(){

}


void Decor::methodeVidePourFaireUneAbstracClasse(){
    
}

bool Decor::estEau() {
    return this->eau;
}

bool Decor::estCache() {
    return this->cache;
}
