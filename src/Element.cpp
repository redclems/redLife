#include "Element.hpp"
#include "Carte.hpp"

#include <iostream>

bool Element::afficherLesCauseDeMort = false;

Element::Element() :    pos({0, 0}), symbol(' '), couleur(Couleur::BLANC), type(TypeElement::VIDE) {
    this->marchable = false;
    this->vide = true;
    this->jourExistant = 0;
    this->tempExistantMoyen = -1;
}

Element::Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte) 
    : pos(pos), symbol(s), couleur(c), type(type), carte(carte){
    //this->elementAvant = new Vide();
    this->marchable = false;
    this->jourExistant = 0;
    this->tempExistantMoyen = -1;
}

Element::Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte, bool marchable) 
    : pos(pos), symbol(s), couleur(c), type(type), carte(carte), marchable(marchable) {

    this->jourExistant = 0;
    this->tempExistantMoyen = -1;
}

Element::Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte, int tempExistantMoyen)
    : pos(pos), symbol(s), couleur(c), type(type), carte(carte), tempExistantMoyen(tempExistantMoyen) {
    this->jourExistant = 0;
}

Element::Element(Position pos, char s, Couleur c, TypeElement type, Carte* carte, bool marchable, int tempExistantMoyen) 
    : pos(pos), symbol(s), couleur(c), type(type), carte(carte), marchable(marchable), tempExistantMoyen(tempExistantMoyen){
    this->jourExistant = 0;
}


int random(int min, int max);

void Element::addJour(){
    if(tempExistantMoyen<0 || this->jourExistant <= tempExistantMoyen || (this->jourExistant > tempExistantMoyen && random(0, 100) < 90)){
        jourExistant++;
    }else{
        getCarte()->suprimerElement(getPosX(), getPosY());
        if(Element::afficherLesCauseDeMort){
                switch (getType()) {
                    case TypeElement::ANNIMAL:
                        std::cout << "Mort de vieillesse d'un animal" << std::endl;
                        break;
                    default:
                        break;
                }
        }
    }
}

void Element::getDraw() const{
    // Définir la couleur en fonction de celle souhaitée
    switch (couleur) {
        case Couleur::ROUGE:
            std::cout << "\033[1;31m" << symbol << "\033[0m"; // Rouge
            break;
        case Couleur::VERT:
            std::cout << "\033[1;32m" << symbol << "\033[0m"; // Vert
            break;
        case Couleur::JAUNE:
            std::cout << "\033[1;33m" << symbol << "\033[0m"; // Jaune
            break;
        case Couleur::BLEU:
            std::cout << "\033[1;34m" << symbol << "\033[0m"; // Bleu
            break;
        case Couleur::ROSE:
            std::cout << "\033[1;35m" << symbol << "\033[0m"; // Rose
            break;
        case Couleur::CYAN:
            std::cout << "\033[1;36m" << symbol << "\033[0m"; // Cyan
            break;
        case Couleur::BLANC:
            std::cout << "\033[1;37m" << symbol << "\033[0m"; // Blanc
            break;
        default:
            std::cout << "\033[1;37m" << symbol << "\033[0m"; // Blanc par défaut
            break;
    }
}

bool Element::estAnimal() const{
    // Vérifie si l'élément est de type animal
    return type == TypeElement::ANNIMAL;
}

bool Element::estVide() const{
    // Vérifie si l'élément est de type vide
    return type == TypeElement::VIDE;
}

void Element::newPos(int x, int y){
    this->pos.posX = x;
    this->pos.posY = y;
}

void Element::newPos(Position pos){
    this->pos = pos;
}

void Element::editIcon(char s){
    this->symbol = s;
}