#include "Animal.hpp"
#include <iostream>

Animal::Animal(Position pos, char s, CouleurAnimal c, Carte* carte, 
           const ParamAnimal& parametres, AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement,
           DeplacementStrategy* strategieDeplacement) 
    : Element(pos, s, c, TypeElement::ANNIMAL,carte),
      parametres(parametres), habitudeAlimentaire(habitudeAlimentaire),
      typeDeplacement(typeDeplacement), strategieDeplacement(strategieDeplacement) {}

Animal::Animal() : Element(){

}

void Animal::methodeVidePourFaireUneAbstracClasse(){
    
}

void Animal::seDeplacer() {
    // Implémentez le comportement de déplacement de l'animal ici
    this->strategieDeplacement->deplacer(this);
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

DeplacementType Animal::tDeplacement() {
    return typeDeplacement;
}

int Animal::ceQuiCePasseLorsDuDeplacement() {
    // Implémentez ce qui ce passe si l'annimal arrive sur la nouvelle position
    // 0 - deplacement ok / 1 - deplacement impossible / 2 - element manger / 3 - reproduction / 4 - boire

    return 0;
}