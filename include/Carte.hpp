#ifndef CARTE_HPP
#define CARTE_HPP

#include "Element.hpp"

class Carte {
private:
    int hauteur;
    int largeur;
    int heure;
    int jour;
    Element* elements;

public:
    Carte(int hauteur, int largeur);

    void createMap();
    void run();
    void nouvelJournee();
};

#endif // CARTE_HPP
