#include "DeplacementStrategy.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Carte.hpp"


DeplacementBasic::DeplacementBasic(){
    
}

void DeplacementStrategy::deplacer(Animal* annimal) {
    // Initialiser le générateur de nombres aléatoires

    Position newPos = calculDeplacer(annimal);

    bool res = annimal->getCarte()->deplacerAnnimal( annimal->getPosX(), annimal->getPosY(), newPos.posX, newPos.posY);

    if(res){
        annimal->newPos(newPos);
    }

}


Position DeplacementBasic::calculDeplacer(Animal* annimal){
    int direction, NPosX, NPosY;
    Position newPos;

    // Générer un nombre aléatoire entre 0 et 3 pour déterminer la direction
    direction = rand() % 4;
    //direction = 2;

    NPosX = annimal->getPosX();
    NPosY = annimal->getPosY();

    // Déplacer l'animal dans la direction choisie
    switch (direction) {
        case 0:
            // nord
            NPosY--;
            break;
        case 1:
            // sud
            NPosY++;
            break;
        case 2:
            // est
            NPosX++;
            break;
        case 3:
            // ouest
            NPosX--;
            break;
        default:
            //pas bouger
            break;
    }

    newPos.posX = NPosX;
    newPos.posY = NPosY;

    // Retourner la nouvelle position
    return newPos;
}
