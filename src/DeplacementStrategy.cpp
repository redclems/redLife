#include "DeplacementStrategy.hpp"

#include <cstdlib>
#include <ctime>


class DeplacementBasic : public DeplacementStrategy {
public:
    void deplacer(Animal& annimal) override {
        // Initialiser le générateur de nombres aléatoires
        srand(time(nullptr));

        // Générer un nombre aléatoire entre 0 et 3 pour déterminer la direction
        int direction = rand() % 4;

        NPosX = annimal.getPosX();
        NPosY = annimal.getPosY();;

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
                break;
        }

        annimal.newPos(NPosX, NPosY);
        annimal.getCarte()->deplacerObjet( annimal.getPosX(), annimal.getPosY(), NPosX, NPosY);
    }
};