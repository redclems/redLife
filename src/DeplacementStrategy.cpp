#include "DeplacementStrategy.hpp"

#include <cstdlib>
#include <ctime>

DeplacementBasic::DeplacementBasic(){
    
}

void DeplacementBasic::deplacer(Animal& annimal) {
    // Initialiser le générateur de nombres aléatoires

    // Générer un nombre aléatoire entre 0 et 3 pour déterminer la direction
    int direction = rand() % 5;

    int NPosX = annimal.getPosX();
    int NPosY = annimal.getPosY();;

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



    annimal.newPos(NPosX, NPosY);
    annimal.getCarte()->deplacerObjet( annimal.getPosX(), annimal.getPosY(), NPosX, NPosY);
}
