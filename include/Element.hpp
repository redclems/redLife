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
    Element* elementAvant;
    bool marchable;

public:
    Element();
    Element(int x, int y, char s, CouleurAnimal c, TypeElement type, Carte* carte);
    Element(int x, int y, char s, CouleurAnimal c, TypeElement type, Carte* carte, bool marchable);

    virtual void methodeVidePourFaireUneAbstracClasse() = 0;

    void getDraw();
    bool estAnimal();
    bool estVide();
    Carte* getCarte();

    bool estMarchable();

    int getPosX();
    int getPosY();

    void newPos(int x, int y);

    void saveLeDernierElement(Element* ele); //pour faire revenir si c'etait de l'eau ou un buisson

    Element* leDernierElement();
};

class Vide : public Element {
public:
    Vide();
    Vide(int x, int y, char s, CouleurAnimal c, Carte* carte);

    virtual void methodeVidePourFaireUneAbstracClasse() override;
};


#endif // ELEMENT_HPP
