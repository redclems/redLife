#include "Animaux.hpp"
#include <iostream>

void Renard::methodeVidePourFaireUneAbstracClasse(){
    
}

void Poisson::methodeVidePourFaireUneAbstracClasse(){
    
}

void Lapin::methodeVidePourFaireUneAbstracClasse(){
    
}


Poisson::Poisson(Position pos, Carte* carte)
    : Animal(pos, '>', CouleurAnimal::ROSE, carte, 
        { 1, 5, 5, 10, 5, 4, 7, 50, 50, 10 },
        AlimentationType::HERBIVORE, DeplacementType::NAGE,
        new DeplacementBasic()) {
    }

Renard::Renard  (Position pos, Carte* carte) 
    : Animal(pos, 'R', CouleurAnimal::ROUGE, carte,
        { 2, 5, 5, 100, 30, 20, 40, 30, 50, 30},
        AlimentationType::CARNIVORE, DeplacementType::MARCHE,
        new DeplacementBasic()) {
    }

Lapin::Lapin    (Position pos, Carte* carte)
    : Animal(pos, 'L', CouleurAnimal::JAUNE, carte,
        { 1, 5, 5, 20, 20, 10, 20, 50, 50, 10},
        AlimentationType::HERBIVORE, DeplacementType::MARCHE,
        new DeplacementBasic()){
    }
