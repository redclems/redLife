#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "Carte.hpp"
#include "CouleurAnimal.hpp"
#include "TypeElement.hpp"

class Element {
private:
    int posX;
    int posY;
    char symbol;
    CouleurAnimal couleur;
    TypeElement type;
    Carte* carte;

public:
    Element();
    Element(int x, int y, char s, CouleurAnimal c, TypeElement type, Carte* carte);

    void getDraw();
    bool estAnimal();
    bool estVide();
    Carte* getCarte();

    int getPosX();
    int getPosY();

    void newPos(int x, int y);

    Element& operator=(const Element& ele) {
        this->posX = ele.getPosX();
        this->posY = ele.getPosY();
        this->symbol = ele.getSymbol();
        this->couleur = ele.getCouleur();
        this->type = ele.getType();
        this->carte = ele.getCarte();

        return *this;
    }
};

#endif // ELEMENT_HPP
