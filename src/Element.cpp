#include "Element.hpp"
#include <iostream>


Element::Element() :    pos({0, 0}), symbol(' '), couleur(CouleurAnimal::BLANC), type(TypeElement::VIDE) {
    //this->elementAvant = new Vide();
    this->marchable = false;
    this->vide = true;
}

Element::Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte) : pos(pos), symbol(s), couleur(c), type(type), carte(carte){
    //this->elementAvant = new Vide();
    this->marchable = false;
}

Element::Element(Position pos, char s, CouleurAnimal c, TypeElement type, Carte* carte, bool marchable) : pos(pos), symbol(s), couleur(c), type(type), carte(carte){
    //this->elementAvant = new Vide();
    this->marchable = marchable;
}

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
    return type == TypeElement::ANNIMAL;
}


bool Element:: estMarchable() {
    // Vérifie si l'élément est de type animal
    return this->marchable;
}

bool Element::estVide() {
    // Vérifie si l'élément est de type vide
    return this->type == TypeElement::VIDE;
}

Carte* Element::getCarte(){
    return this->carte;
}

int Element::getPosX(){
    return this->pos.posX;
}

int Element::getPosY(){
    return this->pos.posY;
}

void Element::newPos(int x, int y){
    this->pos.posX = x;
    this->pos.posY = y;
}

void Element::newPos(Position pos){
    this->pos = pos;
}

TypeElement Element::getType(){
    return this->type;
}

void Element::editIcon(char s){
    this->symbol = s;
}