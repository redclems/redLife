#include "Animaux.hpp"
#include <iostream>

void Renard::methodeVidePourFaireUneAbstracClasse(){
    
}

void Poisson::methodeVidePourFaireUneAbstracClasse(){
    
}

void Lapin::methodeVidePourFaireUneAbstracClasse(){
    
}


Poisson::Poisson(int x, int y, Carte* carte, Element* elementAvant)
    : Animal(x, y, '>', CouleurAnimal::ROSE, carte, 1, 5, 5, 2, 1,
        20, 7, 50, 50,
        10, AlimentationType::HERBIVORE, DeplacementType::NAGE,
        new DeplacementBasic()) {
    }

Renard::Renard  (int x, int y, Carte* carte, Element* elementAvant) 
    : Animal(x, y, 'R', CouleurAnimal::ROUGE, carte, 2, 5, 5, 5, 10,
        40, 20, 30, 50,
        30, AlimentationType::CARNIVORE, DeplacementType::MARCHE,
        new DeplacementBasic()) {
    }

Lapin::Lapin    (int x, int y, Carte* carte, Element* elementAvant)
    : Animal(x, y, 'L', CouleurAnimal::JAUNE, carte, 1, 5, 5, 3, 4,
        30, 10, 50, 50,
        10, AlimentationType::HERBIVORE, DeplacementType::MARCHE,
        new DeplacementBasic()){
    }
