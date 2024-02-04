#ifndef CARTE_HPP
#define CARTE_HPP

#include "Element.hpp"

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
    ~Carte();

    void afficherCarte();
    void createMap();
    void run();
    void nouvelJournee();
    void nouvelHeure();
    void deplacerObjet(int x, int y, int newX, int newY);
    bool positionOccupee(int x, int y);
};

#endif // CARTE_HPP
