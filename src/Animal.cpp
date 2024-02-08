#include "Animal.hpp"
#include <iostream>

Animal::Animal(int x, int y, char s, CouleurAnimal c, Carte* carte, float vitesse, int niveauFaim, int niveauSoif, int barreDeVie, float poids,
           float tailleHauteur, float tailleLargeur, int gourmandise, int envieReproduction,
           int espritAventure, AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement,
           DeplacementStrategy* strategieDeplacement) 
    : Element(x, y, s, c, TypeElement::ANNIMAL,carte), vitesse(vitesse), niveauFaim(niveauFaim), niveauSoif(niveauSoif), barreDeVie(barreDeVie),
      poids(poids), tailleHauteur(tailleHauteur), tailleLargeur(tailleLargeur), gourmandise(gourmandise),
      envieReproduction(envieReproduction), espritAventure(espritAventure), habitudeAlimentaire(habitudeAlimentaire),
      typeDeplacement(typeDeplacement), strategieDeplacement(strategieDeplacement) {}

void Animal::methodeVidePourFaireUneAbstracClasse(){
    
}

void Animal::seDeplacer() {
    // Implémentez le comportement de déplacement de l'animal ici
    std::cout << "Un annimal ce deplacve rrhhh" << std::endl;
    this->strategieDeplacement->deplacer(*this);
}

void Animal::manger() {
    // Implémentez le comportement de manger de l'animal ici
}

void Animal::boire() {
    // Implémentez le comportement de boire de l'animal ici
}

void Animal::reproduire() {
    // Implémentez le comportement de reproduction de l'animal ici
}

void Animal::chasser() {
    // Implémentez le comportement de chasser de l'animal ici
}

int Animal::ceQuiCePasseLorsDuDeplacement() {
    // Implémentez ce qui ce passe si l'annimal arrive sur la nouvelle position
    // 0 - deplacement ok / 1 - deplacement impossible / 2 - element manger / 3 - reproduction / 4 - boire

    return 0;
}