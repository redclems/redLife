#ifndef ANIMAUX_HPP
#define ANIMAUX_HPP

#include "Animal.hpp"


class Renard : public Animal {
public:
    Renard(Position pos, Carte* carte);

    void methodeVidePourFaireUneAbstracClasse() override;
};

class Poisson : public Animal {
public:
    Poisson(Position pos, Carte* carte);

    void methodeVidePourFaireUneAbstracClasse() override;
};

class Lapin : public Animal {
public:
    Lapin(Position pos, Carte* carte);

    void methodeVidePourFaireUneAbstracClasse() override;
};

class Schbalung : public Animal {
public:
    Schbalung(Position pos, Carte* carte);

    void methodeVidePourFaireUneAbstracClasse() override;
};

#endif // ANIMAUX_HPP
