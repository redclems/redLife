#include "DeplacementStrategy.hpp"

#include <iostream>
#include <vector>

#include "Animal.hpp"
#include "Carte.hpp"

int random(int min, int max);

DeplacementBasic::DeplacementBasic(){}

DeplacementReflechitHerbivore::DeplacementReflechitHerbivore() {}

DeplacementReflechitCarnivore::DeplacementReflechitCarnivore() {}

void DeplacementStrategy::deplacer(Animal* animal) {
    // Initialiser le générateur de nombres aléatoires

    Position newPos = calculDeplacer(animal);

    bool res = animal->getCarte()->deplacerAnimal( animal->getPosX(), animal->getPosY(), newPos.posX, newPos.posY);

    if(res){
        animal->newPos(newPos);
    }

}

Position randomPos(Animal* animal){
    int direction, NPosX, NPosY;
    Position newPos;

    direction = random(0, 4);

    NPosX = animal->getPosX();
    NPosY = animal->getPosY();

    // Déplacer l'animal dans la direction choisie
    switch (direction) {
        case 0:
            NPosY--;
            break;
        case 1:
            NPosY++;
            break;
        case 2:
            NPosX++;
            break;
        case 3:
            NPosX--;
            break;
        default:
            //pas bouger
            break;
    }

    // Retourner la nouvelle position
    return Position(NPosX, NPosY);
}

Position DeplacementBasic::calculDeplacer(Animal* animal){
    return randomPos(animal);
}



Position DeplacementReflechitCarnivore::calculDeplacer(Animal* animal) {
    return randomPos(animal);
}

Position DeplacementReflechitHerbivore::calculDeplacer(Animal* animal) {
    int currentX = animal->getPosX();
    int currentY = animal->getPosY();


    std::vector<std::vector<int>> surroundings = animal->getMatrixAround();
    std::vector<Position> predatorPositions;
    std::vector<Position> plantPositions;
    std::vector<Position> partnerPositions;

    // Parcourir les cases autour de l'animal pour détecter les prédateurs, les plantes et les partenaires
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i != 2 && j != 2) {
                if (surroundings[i][j] == 3) { // 3 représente un prédateur
                    predatorPositions.push_back(Position(currentX - 2 + i, currentY - 2 + j));
                } else if (surroundings[i][j] == 2) { // 2 représente une plante
                    plantPositions.push_back(Position(currentX - 2 + i, currentY - 2 + j));
                } else if (surroundings[i][j] == 4) { // 4 représente un partenaire potentiel
                    partnerPositions.push_back(Position(currentX - 2 + i, currentY - 2 + j));
                }
            } 
        }
    }

    std::vector<Position> safePositions;
    if (!predatorPositions.empty()) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 && j != 0) { // Ne pas inclure la position actuelle
                    bool isAdjacent = false;
                    for (const Position& predPos : predatorPositions) {
                        if (predPos.posX == currentX + i && predPos.posY == currentY + j) {
                            // La position est adjacente à un prédateur
                            isAdjacent = true;
                            break;
                        }
                    }
                    if (!isAdjacent) {
                        safePositions.push_back(Position(currentX + i, currentY + j));
                    }
                }
            }
        }
    }

    std::vector<Position> safePositionsEtPlante;//trouver les zone comment entre safe positon et plante
    
    // Parcourir les positions sûres
    for (size_t i = 0; i < safePositions.size(); ++i) {
        const Position& safePos = safePositions[i];
        // Vérifier si la position sûre est également une position de plante
        // Parcourir les positions de plantes
        for (size_t j = 0; j < plantPositions.size(); ++j) {
            if (plantPositions[j].posX == safePos.posX && plantPositions[j].posY == safePos.posY) {
                // Si oui, ajouter cette position à la liste des positions sûres et de plantes
                safePositionsEtPlante.push_back(safePos);
            }
        }
    }

    // Si des positions sûres sont disponibles, choisir une position aléatoire parmi celles-ci
    if (!safePositionsEtPlante.empty()) {
        int randomIndex = random(0, safePositionsEtPlante.size()-1);
        return safePositionsEtPlante[randomIndex];
    }
    

    // Si des positions sûres sont disponibles, choisir une position aléatoire parmi celles-ci
    if (!safePositions.empty()) {
        int randomIndex = random(0, safePositions.size()-1);
        return safePositions[randomIndex];
    }

    // Si aucun prédateur n'est détecté ou s'il n'y a pas de positions sûres, chercher à manger les plantes si l'annimal a faim
    if (!plantPositions.empty() && (animal->getParam().niveauFaim < 3 || !animal->peuxSeReproduire())) {
        int randomIndex = random(0, plantPositions.size()-1);
        return plantPositions[randomIndex];
    }

    // Si aucun prédateur n'est détecté ou s'il n'y a pas de positions sûres, chercher à manger les plantes
    if (!partnerPositions.empty() && animal->peuxSeReproduire()) {
        int randomIndex = random(0, partnerPositions.size()-1);
        return partnerPositions[randomIndex];
    }
    

    // Si aucune case vide n'est trouvée, l'animal reste immobile
    return randomPos(animal);
}




