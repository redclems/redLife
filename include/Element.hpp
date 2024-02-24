#ifndef ELEMENT_HPP
#define ELEMENT_HPP

class Carte;

#include "Couleur.hpp"
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
    Couleur couleur;
    TypeElement type;
    bool marchable;
    bool vide;
    int jourExistant;
    int tempExistantMoyen;

public:
    static bool afficherLesCauseDeMort;
    Carte* carte;
    Element();
    Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte);
    Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte, int tempExistantMoyen);
    Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte, bool marchable);
    Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte, bool marchable, int tempExistantMoyen);

    virtual ~Element() = 0;

    void addJour();
    void getDraw() const;

    bool estAnimal() const;
    bool estVide() const;
    bool estMarchable() const {return marchable;};
    int getPosX() const {return pos.posX;};
    int getPosY() const {return pos.posY;};
    int getAge() const {return jourExistant;};
    Carte* getCarte() const {return carte;};
    TypeElement getType() const {return type;};

    void newPos(int x, int y);
    void newPos(Position pos);

    void editIcon(char s);

};

inline Element::~Element() {}



#endif // ELEMENT_HPP
