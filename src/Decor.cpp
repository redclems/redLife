#include "Decor.hpp"

Decor::Decor(int x, int y, char s, CouleurAnimal c, Carte* carte, bool cache, bool eau) 
    : Element(x, y, s, TypeElement::DECOR, c, carte), cache(cache), eau(eau) {}

bool Decor::estEau() {
    return this->eau;
}

bool Decor::estCache() {
    return this->cache;
}
