#ifndef ELEMENT_HPP
#define ELEMENT_HPP


class Carte;

#include "CouleurAnimal.hpp"
#include "TypeElement.hpp"

struct Position {
    int posX;
    int posY;
};

class Element {
private:
    Position pos;
    char symbol;
    CouleurAnimal couleur;
    TypeElement type;
    Carte* carte;
    bool marchable;
    bool vide;

public:
    Element();
    Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte);
    Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte, bool marchable);

    virtual void methodeVidePourFaireUneAbstracClasse() = 0;

    void getDraw();
    bool estAnimal();
    bool estVide();
    Carte* getCarte();

    bool estMarchable();

    int getPosX();
    int getPosY();

    void newPos(int x, int y);
    void newPos(Position pos);

    void editIcon(char s);

    TypeElement getType();
};



#endif // ELEMENT_HPP
