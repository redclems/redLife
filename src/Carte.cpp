#include "Carte.hpp"

#include <iostream>
#include <cstdlib> 
#include <ctime>

#include <unistd.h> 
#include "Decor.hpp"
#include "Plante.hpp"
#include "Animal.hpp"
#include "Animaux.hpp"

Carte::Carte(int hauteur, int largeur) : hauteur(hauteur), largeur(largeur){
    // Initialisation de la matrice d'éléments représentant la carte
    this->heure = 0;
    this->jour = 0;
    this->nbElement = 0;
    this->elements = new Element*[hauteur];
    for (int i = 0; i < hauteur; ++i) {
        this->elements[i] = new Vide[largeur];
    }
}

int random(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

void Carte::createMap() {
    
    std::cout << "taille carte : y" << this->hauteur << " / x < " << this->largeur << std::endl;

    for (int i = 0; i < this->hauteur; ++i) {
        for (int j = 0; j < this->largeur; ++j) {
            //Les poind d'eau
            int rand = random(0, 100);
            if (rand < 1 && !positionOccupee(j, i)) {

                int laregeurdx = random(1, 4);
                int hauteurdy  = random(1, 4);
                for (int dx = -laregeurdx; dx <= laregeurdx; dx++) {
                    for (int dy = -hauteurdy; dy <= hauteurdy; dy++) {
                        int newX = i + dx;
                        int newY = j + dy;
                        if(newX >= 0 && newY >= 0 && newX<hauteur && newY<largeur){
                            this->elements[newX][newY] = Decor(newX, newY, 'e', CouleurAnimal::BLEU, this, false, true, true);
                        }
                    }
                }
            }
            //buisson
            else if (rand < 6 && !positionOccupee(j, i)) {
                for (int dx = 0; dx <= 1; dx++) {
                    for (int dy = 0; dy <= 1; dy++) {
                        int newX = i + dx;
                        int newY = j + dy;
                        if(newX >= 0 && newY >= 0 && newX<hauteur && newY<largeur){
                            this->elements[newX][newY] = Decor(newX, newY, '"', CouleurAnimal::VERT, this, true, false, true);
                        }
                    }
                }
            }else if(!this->elements[i][j].estMarchable()){
                this->elements[i][j] = Decor(i, j, ' ', CouleurAnimal::VERT, this, false, false, true);
            }
        }
    }

    std::cout << "plante c'est fait " << std::endl;

    for (int i = 0; i < this->hauteur; ++i) {
        for (int j = 0; j < this->largeur; ++j) {
            //annimaux
            if (random(0, 100) < 8 && this->elements[i][j].estMarchable()) {
                int animalType = random(0, 2);
                /*
                Decor* decor = dynamic_cast<Decor*>(&this->elements[i][j]);

                if(decor->estEau()){
                    animalType = random(0, 1);
                }else{
                    animalType = 2; 
                }
                */
                switch (animalType) {
                    case 0:
                        this->elements[i][j] = Lapin(i, j, this, &this->elements[i][j]);
                        break;
                    case 1:
                        this->elements[i][j] = Renard(i, j, this, &this->elements[i][j]);
                        break;
                    case 2:
                        this->elements[i][j] = Poisson(i, j, this, &this->elements[i][j]);
                        break;
                    default:
                        break;
                }
            }
        }
    }


    std::cout << "La carte a été créée avec succès !" << std::endl;
}

void Carte::run() {
    while (true) {
        //nouveau jour
        if (this->heure >= 24 || (this->heure == 0 && this->jour == 0)) {
            this->nouvelJournee();
        }

        this->nouvelHeure();

        // afficher 
        this->afficherCarte();

        //attendre
        sleep(2);
    }
}

void Carte::afficherCarte() {
    // affichage
    int tailleEcrireJour = 10; // pour afficher "j: / h: " 
    int tempJour = this->jour;
    while (tempJour / 10 != 0) {
        tempJour /= 10;
        tailleEcrireJour++;
    }
    if(this->heure < 10){
        tailleEcrireJour++;
    }else{
        tailleEcrireJour+=2;
    }

    for (int i = 0; i < this->largeur-tailleEcrireJour; ++i) {
        std::cout << "-";
    }

    std::cout << "j: " << this->jour << " / h: " << this->heure << std::endl;
    for (int i = 0; i < this->hauteur; ++i) {
        for (int j = 0; j < this->largeur; ++j) {
            elements[i][j].getDraw();
        }

        std::cout << "|" << std::endl; // Aller à la ligne pour afficher la prochaine rangée
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
            if (random(0, 100) < 3) {
                //todo permetre de verifier si on est une plante eau ou plante de terre
                if (this->elements[i][j].estMarchable()) { // Vérifier si l'emplacement est vide
                    bool inEau = false;
                    /*
                    Decor* decor = dynamic_cast<Decor*>(&this->elements[i][j]);
                    if(decor->estEau()){
                        inEau = true;
                    }
                    */

                    this->elements[i][j] = Plante(i, j, 'p',  CouleurAnimal::BLANC, this, 2, inEau);
                }
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
    elements[y][x] = Vide(); // Réinitialiser
}

bool Carte::positionOccupee(int x, int y) {
    // Vérifier
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
        return false;
    }

    // Vérifier objet non vide
    return !elements[y][x].estVide();
}
