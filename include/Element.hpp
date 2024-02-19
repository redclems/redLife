#ifndef ELEMENT_HPP
#define ELEMENT_HPP


class Carte;

#include <random>
#include "CouleurAnimal.hpp"
#include "TypeElement.hpp"

struct Position {
    int posX;
    int posY;
    Position(int xCoord, int yCoord) : posX(xCoord), posY(yCoord) {}
    Position():posX(0), posY(0){}
};

class Element {
private:
    Position pos;
    char symbol;
    CouleurAnimal couleur;
    TypeElement type;
    bool marchable;
    bool vide;
    int jourExistant;
    int tempExistantMoyen;

public:
    static bool afficherLesCauseDeMort;
    Carte* carte;
    Element();
    Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte);
    Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte, int tempExistantMoyen);
    Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte, bool marchable);
    Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte, bool marchable, int tempExistantMoyen);

    virtual void methodeVidePourFaireUneAbstracClasse() = 0;

    void addJour();
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

    int getAge();
};



#endif // ELEMENT_HPP
