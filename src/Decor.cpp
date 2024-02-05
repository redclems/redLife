#include "Decor.hpp"

Decor::Decor(int x, int y, char s, CouleurAnimal c, Carte* carte, bool cache, bool eau) 
    : Element(x, y, s, c, TypeElement::DECOR, carte), cache(cache), eau(eau) {}


void Decor::methodeVidePourFaireUneAbstracClasse(){
    
}

bool Decor::estEau() {
    return this->eau;
}

bool Decor::estCache() {
    return this->cache;
}
