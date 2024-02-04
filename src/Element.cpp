#include "Element.hpp"
#include <iostream>


Element::Element() : posX(0), posY(0), symbol(' '), couleur(CouleurAnimal::BLANC), type(TypeElement::VIDE) {}

Element::Element(int x, int y, char s, CouleurAnimal c, TypeElement type, Carte* carte) : posX(x), posY(y), symbol(s), couleur(c), type(type) {}

void Element::getDraw() {
    // Définir la couleur en fonction de celle souhaitée
    switch (couleur) {
        case CouleurAnimal::ROUGE:
            std::cout << "\033[1;31m" << symbol << "\033[0m"; // Rouge
            break;
        case CouleurAnimal::VERT:
            std::cout << "\033[1;32m" << symbol << "\033[0m"; // Vert
            break;
        case CouleurAnimal::JAUNE:
            std::cout << "\033[1;33m" << symbol << "\033[0m"; // Jaune
            break;
        case CouleurAnimal::BLEU:
            std::cout << "\033[1;34m" << symbol << "\033[0m"; // Bleu
            break;
        case CouleurAnimal::ROSE:
            std::cout << "\033[1;35m" << symbol << "\033[0m"; // Rose
            break;
        case CouleurAnimal::CYAN:
            std::cout << "\033[1;36m" << symbol << "\033[0m"; // Cyan
            break;
        case CouleurAnimal::BLANC:
            std::cout << "\033[1;37m" << symbol << "\033[0m"; // Blanc
            break;
        default:
            std::cout << "\033[1;37m" << symbol << "\033[0m"; // Blanc par défaut
            break;
    }
}

bool Element::estAnimal() {
    // Vérifie si l'élément est de type animal
    return type == TypeElement::ANIMAL;
}

bool Element::estVide() {
    // Vérifie si l'élément est de type vide
    return type == TypeElement::VIDE;
}

Carte* Element::getCarte(){
    return this->carte;
}

int Animal::getPosX(){
    return this->posX;
}

int Animal::getPosY(){
    return this->posY;
}

void Animal::newPos(int x, int y){
    this->posX = x;
    this->posY = y;
}