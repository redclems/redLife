#ifndef PLANTE_HPP
#define PLANTE_HPP

#include "Element.hpp"

class Plante : public Element{
private:
    int niveauNutrition;
    bool pousseDansEau;

public:
    Plante(int x, int y, char s, CouleurAnimal c, Carte* carte,  int niveauNutrition, bool pousseDansEau);

    virtual void methodeVidePourFaireUneAbstracClasse() override;
};

#endif // PLANTE_HPP