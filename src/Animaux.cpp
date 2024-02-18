#include "Animaux.hpp"
#include <iostream>

void Renard::methodeVidePourFaireUneAbstracClasse(){
    
}

void Poisson::methodeVidePourFaireUneAbstracClasse(){
    
}

void Lapin::methodeVidePourFaireUneAbstracClasse(){
    
}

void Schbalung::methodeVidePourFaireUneAbstracClasse(){
    
}

Poisson::Poisson(Position pos, Carte* carte)
    : Animal(pos, '>', CouleurAnimal::ROSE, carte, 
        { 1, 5, 5, 10, 5, 4, 7, 50, 50, 10, 5, 15},
        AlimentationType::HERBIVORE, DeplacementType::NAGE,
        new DeplacementBasic(), TypeAnnimal::POISSON) {
    }

Renard::Renard  (Position pos, Carte* carte) 
    : Animal(pos, 'R', CouleurAnimal::ROUGE, carte,
        { 2, 5, 5, 30, 30, 20, 40, 30, 50, 30, 15, 30},
        AlimentationType::CARNIVORE, DeplacementType::MARCHE,
        new DeplacementBasic(), TypeAnnimal::RENARD) {
    }

Lapin::Lapin    (Position pos, Carte* carte)
    : Animal(pos, 'L', CouleurAnimal::JAUNE, carte,
        { 1, 5, 5, 20, 20, 10, 20, 50, 50, 10, 8, 20},
        AlimentationType::HERBIVORE, DeplacementType::MARCHE,
        new DeplacementBasic(), TypeAnnimal::LAPIN){
    }

Schbalung::Schbalung (Position pos, Carte* carte)
    : Animal(pos, '^', CouleurAnimal::JAUNE, carte,
        { 2, 10, 10, 40, 100, 120, 70, 50, 50, 10, 20, 50},
        AlimentationType::HERBIVORE, DeplacementType::MARCHE,
        new DeplacementBasic(), TypeAnnimal::SCHBALUNG){
    }
