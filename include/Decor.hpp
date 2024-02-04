#ifndef DECOR_HPP
#define DECOR_HPP

#include "Element.hpp"
#include "CouleurAnimal.hpp"

class Decor : public Element{
private:
    bool cache;
    bool eau;
public:
    Decor(int x, int y, char s, CouleurAnimal c, Carte* carte, bool cache, bool eau);

    bool estEau();
    bool estCache();
};

#endif // DECOR_HPP