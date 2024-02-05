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

    virtual void methodeVidePourFaireUneAbstracClasse() = 0;

    void getDraw();
    bool estAnimal();
    bool estVide();
    Carte* getCarte();

    int getPosX();
    int getPosY();

    void newPos(int x, int y);
};

class Vide : public Element {
public:
    Vide();
    Vide(int x, int y, char s, CouleurAnimal c, Carte* carte);

    virtual void methodeVidePourFaireUneAbstracClasse() override;
};


#endif // ELEMENT_HPP
