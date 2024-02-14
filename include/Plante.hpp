#ifndef PLANTE_HPP
#define PLANTE_HPP

#include "Decor.hpp"

class Plante : public Decor{
private:
    int niveauNutrition;
    bool pousseDansEau;

public:
    Plante(Position pos, char s, CouleurAnimal c, Carte* carte,  int niveauNutrition, bool pousseDansEau);

    virtual void methodeVidePourFaireUneAbstracClasse() override;
};

#endif // PLANTE_HPP