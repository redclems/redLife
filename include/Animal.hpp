#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "AlimentationType.hpp"
#include "DeplacementType.hpp"
#include "DeplacementStrategy.hpp"

class Animal {
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
    Animal(float vitesse, int niveauFaim, int niveauSoif, int barreDeVie, float poids,
           float tailleHauteur, float tailleLargeur, int gourmandise, int envieReproduction,
           int espritAventure, AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement,
           DeplacementStrategy* strategieDeplacement);
    virtual ~Animal() {}

    void seDeplacer();
    void manger();
    void boire();
    void reproduire();
    void chasser();
};

#endif // ANIMAL_HPP
