#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Element.hpp"
#include "AlimentationType.hpp"
#include "DeplacementType.hpp"
#include "DeplacementStrategy.hpp"


struct ParamAnimal {
    float vitesse;
    int niveauFaim;
    int niveauSoif;
    int barreDeVie;
    float poids;
    float tailleHauteur;
    float tailleLargeur;
    int gourmandise;
    int envieReproduction;
    int espritAventure;
};


class Animal : public Element{
private:
    ParamAnimal parametres;
    AlimentationType habitudeAlimentaire;
    DeplacementType typeDeplacement;
    DeplacementStrategy* strategieDeplacement;

public:

    virtual ~Animal() = default; 
    Animal(); 

    Animal(Position pos, char s, CouleurAnimal c, Carte* carte,const ParamAnimal& parametres,
        AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement, DeplacementStrategy* strategieDeplacement);

    void seDeplacer();
    void manger();
    void boire();
    void reproduire();
    void chasser();
    int ceQuiCePasseLorsDuDeplacement();
    DeplacementType tDeplacement();
    virtual void methodeVidePourFaireUneAbstracClasse() override;
};

#endif // ANIMAL_HPP
