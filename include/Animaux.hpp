#ifndef ANIMAUX_HPP
#define ANIMAUX_HPP

#include "Animal.hpp"

class Renard : public Animal {
public:
    Renard(int x, int y, Carte* carte, Element* elementAvant);

    void methodeVidePourFaireUneAbstracClasse() override;
};

class Poisson : public Animal {
public:
    Poisson(int x, int y, Carte* carte, Element* elementAvant);

    void methodeVidePourFaireUneAbstracClasse() override;
};

class Lapin : public Animal {
public:
    Lapin(int x, int y, Carte* carte, Element* elementAvant);

    void methodeVidePourFaireUneAbstracClasse() override;
};


#endif // ANIMAUX_HPP
