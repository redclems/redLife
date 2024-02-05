#ifndef CARTE_HPP
#define CARTE_HPP

//declaration avancée de Element
class Element;

class Carte {
private:
    int nbElement;

    int hauteur;
    int largeur;
    int heure;
    int jour;
    Element** elements; 

public:
    Carte(int hauteur, int largeur);

    void afficherCarte();
    void createMap();
    void run();
    void nouvelJournee();
    void nouvelHeure();
    void deplacerObjet(int x, int y, int newX, int newY);
    bool positionOccupee(int x, int y);
};

#include "Element.hpp"

#endif // CARTE_HPP
