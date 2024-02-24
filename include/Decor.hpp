#ifndef DECOR_HPP
#define DECOR_HPP

#include "Element.hpp"

class Decor : public Element{
private:
    bool cache = false;
    bool eau   = false;
public:
    Decor(Position pos, char s, Couleur c, Carte* carte, bool cache, bool eau, bool marchable);

    Decor(Position pos, char s, Couleur c, TypeElement ele, Carte* carte, bool cache, bool eau, bool marchable, int tempExistantMoyen);

    ~Decor() override {}; 
    Decor() = default; 

    bool estEau();
    bool estCache();

};

#endif // DECOR_HPP

