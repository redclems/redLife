#include "Decor.hpp"

Decor::Decor(int x, int y, char s, CouleurAnimal c, Carte* carte, bool cache, bool eau, bool marchable) 
    : Element(x, y, s, c, TypeElement::DECOR, carte, marchable), cache(cache), eau(eau){
}



void Decor::methodeVidePourFaireUneAbstracClasse(){
    
}

bool Decor::estEau() {
    return this->eau;
}

bool Decor::estCache() {
    return this->cache;
}
