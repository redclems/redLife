#include "Carte.hpp"

#include <iostream>
#include <random> 
#include <ctime>

#include <unistd.h> 
#include "Decor.hpp"
#include "Plante.hpp"

Carte::Carte(int hauteur, int largeur) : hauteur(hauteur), largeur(largeur){
    // Initialisation de la matrice d'éléments représentant la carte
    this->heure = 0;
    this->jour = 0;
    this->nbElement = 0;
    this->elements = new Element*[hauteur];
    for (int i = 0; i < hauteur; ++i) {
        this->elements[i] = new Element[largeur];
    }
}

int random(int min, int max) {
    std::srand(std::time(nullptr));
    return min + std::rand() % (max - min + 1);
}

void Carte::createMap() {
    
    //nbPoint d'eau au hasard entre 3 et 
    int min = int((this->hauteur*this->largeur)/(10*10));
    int max = min*2; 

    int nbPointEau = random(min, max);

    for(int i = 0; i < nbPointEau; i++){
        int x = random(0, this->largeur);
        int y = random(0, this->hauteur);

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                int newX = x + dx;
                int newY = y + dy;
                if(newX >= 0 && newY >= 0 && newX<largeur && newY<hauteur){
                    this->elements[newY][newX] = Decor(newX, newY, 'e', CouleurAnimal::BLEU, this, false, true);
                }
            }
        }
    }


    //les buisson
    int nbBuisson = random(min*2, max*2);

    for(int i = 0; i < nbBuisson; i++){
        int x = random(0, this->largeur);
        int y = random(0, this->hauteur);

        for (int dx = 0; dx <= 1; dx++) {
            for (int dy = 0; dy <= 1; dy++) {
                int newX = x + dx;
                int newY = y + dy;
                if(newX >= 0 && newY >= 0 && newX<largeur && newY<hauteur){
                    this->elements[newY][newX] = Decor(newX, newY, '"', CouleurAnimal::VERT, this, true, false);
                }
            }
        }
    }


    std::cout << "La carte a été créée avec succès !" << std::endl;
}

void Carte::run() {
    while (true) {

        this->nouvelHeure();

        //nouveau jour
        if (this->heure >= 24) {
            this->nouvelJournee();
        }

        // afficher 
        this->afficherCarte();

        //attendre
        sleep(2);
    }
}

void Carte::afficherCarte() {
    // affichage
    for (int i = 0; i < hauteur; ++i) {
        for (int j = 0; j < largeur; ++j) {
            elements[i][j].getDraw();
        }
        std::cout << std::endl; // Aller à la ligne pour afficher la prochaine rangée
    }
}

void Carte::nouvelHeure() {
    this->heure++;

    // Déplacer les annimaux
    for (int i = 0; i < this->hauteur; ++i) {
        for (int j = 0; j < this->largeur; ++j) {
            if (this->elements[i][j].estAnimal()) {
                Animal* animal = dynamic_cast<Animal*>(&this->elements[i][j]);
                if (animal) {
                    animal->seDeplacer();
                }
            }
        }
    }
}

void Carte::nouvelJournee() {
    this->heure = 0;
    this->jour++;

    //faire pousser les plantes
    for (int i = 0; i < this->hauteur; ++i) {
        for (int j = 0; j < this->largeur; ++j) {
            //5% de chance d'une plante apres il faut faire d'autre plante
            if (random(0, 100) < 5 && !positionOccupee(j, i)) {
                this->elements[i][j] = Plante(i, j, 'p', 2, 0.5, false);
            }
        }
    }
    std::cout << "Une nouvelle journée commence !" << std::endl;
}

void Carte::deplacerObjet(int x, int y, int newX, int newY) {
    // Vérifier
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur ||
        newX < 0 || newX >= largeur || newY < 0 || newY >= hauteur) {
        std::cout << "Coordonnées invalides !" << std::endl;
        return;
    }

    //Déplacer
    elements[newY][newX] = elements[y][x];
    elements[y][x] = Element(); // Réinitialiser
}

bool Carte::positionOccupee(int x, int y) {
    // Vérifier
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur ||
        newX < 0 || newX >= largeur || newY < 0 || newY >= hauteur) {
        return false;
    }

    // Vérifier objet non vide
    return !elements[y][x].estVide();
}
