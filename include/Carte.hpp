#ifndef CARTE_HPP
#define CARTE_HPP

#include <vector>
#include "Decor.hpp"
#include "Animal.hpp"

class Carte {
private:
    int nbElement;

    int hauteur;
    int largeur;
    int heure;
    int jour;
    std::vector<std::vector<Decor>> decor; // Matrice pour les éléments décoratifs
    std::vector<std::vector<Animal>> animaux; // Matrice pour les animaux utilisant la bibliothèque Sud


public:
    Carte(int hauteur, int largeur);

    void afficherCarte();
    void createMap();
    void run();
    void nouvelJournee();
    void nouvelHeure();
    bool deplacerAnnimal(int x, int y, int newX, int newY);
    bool positionOccupee(int x, int y);

    void suprimerAnnimal(int x, int y);
    void suprimerDecor(int x, int y);
};

#endif // CARTE_HPP
