#ifndef DECOR_HPP
#define DECOR_HPP

#include "Element.hpp"

class Decor : public Element{
private:
    bool cache;
    bool eau;
public:
    Decor(Position pos, char s, CouleurAnimal c, Carte* carte, bool cache, bool eau, bool marchable);

    Decor(Position pos, char s, CouleurAnimal c, TypeElement ele, Carte* carte, bool cache, bool eau, bool marchable);

    virtual ~Decor() = default; 
    Decor(); 

    bool estEau();
    bool estCache();
    virtual void methodeVidePourFaireUneAbstracClasse() override;
};

#endif // DECOR_HPP

