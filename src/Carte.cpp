#include "Carte.hpp"
#include <iostream>

Carte::Carte(int hauteur, int largeur) : hauteur(hauteur), largeur(largeur) {
    elements = new Element*[(hauteur+largeur)*2];
}

void Carte::createMap() {
    // Code pour initialiser la carte, placer les éléments, les animaux, les plantes, etc.
    // Cela dépendra de la logique spécifique de votre jeu ou simulation.
    std::cout << "La carte a été créée avec succès !" << std::endl;
}

void Carte::run() {
    // Code pour exécuter la carte, mettre à jour les éléments, gérer les événements, etc.
    // Cela dépendra de la logique spécifique de votre jeu ou simulation.
    std::cout << "La carte est en cours d'exécution..." << std::endl;
}

void Carte::nouvelleJournee() {
    // Code pour passer à une nouvelle journée dans la simulation
    // Cela dépendra de la logique spécifique de votre jeu ou simulation.
    std::cout << "Une nouvelle journée commence sur la carte." << std::endl;
}
