#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Element.hpp"
#include "AlimentationType.hpp"
#include "DeplacementType.hpp"
#include "DeplacementStrategy.hpp"

class Animal : public Element{
private:
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
    AlimentationType habitudeAlimentaire;
    DeplacementType typeDeplacement;
    DeplacementStrategy* strategieDeplacement;

public:
    Animal(int x, int y, char s, CouleurAnimal c, Carte* carte, float vitesse, int niveauFaim, int niveauSoif, int barreDeVie, float poids,
           float tailleHauteur, float tailleLargeur, int gourmandise, int envieReproduction,
           int espritAventure, AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement,
           DeplacementStrategy* strategieDeplacement);

    void seDeplacer();
    void manger();
    void boire();
    void reproduire();
    void chasser();
    virtual void methodeVidePourFaireUneAbstracClasse() override;
};

#endif // ANIMAL_HPP
