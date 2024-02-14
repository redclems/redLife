#include "Carte.hpp"

#include <iostream>
#include <cstdlib> 
#include <ctime>

#include <unistd.h> 
#include "Element.hpp"
#include "Decor.hpp"
#include "Plante.hpp"
#include "Animal.hpp"
#include "Animaux.hpp"


Carte::Carte(int hauteur, int largeur) : hauteur(hauteur), largeur(largeur){
    // Initialisation de la matrice d'éléments représentant la carte
    this->heure = 0;
    this->jour = 0;
    this->nbElement = 0;

    this->decor.resize(largeur, std::vector<Decor>(hauteur)); // Initialiser la matrice decor
    this->animaux.resize(largeur, std::vector<Animal>(hauteur)); // Initialiser la matrice animaux
}

int random(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

void Carte::createMap() {
    
    std::cout << "taille carte : y" << this->hauteur << " / x < " << this->largeur << std::endl;

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            //Les poind d'eau
            int rand = random(0, 100);
            if (rand < 1 && !positionOccupee(y, x)) {

                int largeur_dx = random(1, 4);
                int hauteur_dy  = random(1, 4);
                for (int dx = -largeur_dx; dx <= largeur_dx; dx++) {
                    for (int dy = -hauteur_dy; dy <= hauteur_dy; dy++) {
                        int newX = x + dx;
                        int newY = y + dy;
                        if(newX >= 0 && newY >= 0 && newX < largeur && newY < hauteur){
                            this->decor[newX][newY] = Decor({newX, newY}, 'e', CouleurAnimal::BLEU, this, false, true, true);
                        }
                    }
                }
            }
            //buisson
            else if (rand < 6 && !positionOccupee(y, x)) {
                for (int dx = 0; dx <= 1; dx++) {
                    for (int dy = 0; dy <= 1; dy++) {
                        int newX = x + dx;
                        int newY = y + dy;
                        if(newX >= 0 && newY >= 0 && newX < largeur && newY < hauteur){
                            this->decor[newX][newY] = Decor({newX, newY}, '"', CouleurAnimal::VERT, this, true, false, true);
                        }
                    }
                }
            }else if(!this->decor[x][y].estMarchable()){
                this->decor[x][y] = Decor({x, y}, ' ', CouleurAnimal::VERT, this, false, false, true);//terre de base
            }
        }
    }

    std::cout << "Decor c'est fait " << std::endl;

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            //animaux
            int animalType = random(0, 2);

            if(!this->decor[x][y].estEau()){
                animalType = random(0, 1);
            }else{ 
                animalType = 2; 
            }

            if (random(0, 100) < 1 && this->decor[x][y].estMarchable()) {
                switch (animalType) {
                    case 0:
                        this->animaux[x][y] = Lapin({x, y}, this);
                        break;
                    case 1:
                        this->animaux[x][y] = Renard({x, y}, this);
                        break;
                    case 2:
                        this->animaux[x][y] = Poisson({x, y}, this);
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
        // afficher 
        this->afficherCarte();

        //nouveau jour
        if (this->heure >= 24 || (this->heure == 0 && this->jour == 0)) {
            this->nouvelJournee();
        }

        this->nouvelHeure();

        //attendre
        sleep(1);
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
    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            if (this->animaux[x][y].estVide()) {
                this->decor[x][y].getDraw(); // Afficher le décor
            } else {
                this->animaux[x][y].getDraw(); // Afficher l'animal
            }
        }
        std::cout << "|" << std::endl; // Aller à la ligne pour afficher la prochaine rangée
    }
}

void Carte::nouvelHeure() {
    this->heure++;

    // Créer une copie de la liste d'animaux
    std::vector<std::vector<Animal>> animauxCopie = this->animaux;

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            if (!animauxCopie[x][y].estVide()) {

                this->animaux[x][y].newPos(x, y); // pour etre sur qu'il a les bonnes coordonnées
                this->animaux[x][y].seDeplacer();
            }
        }
    }
}

void Carte::nouvelJournee() {

    this->heure = 0;
    this->jour++;

    //faire pousser les plantes
    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            //5% de chance d'une plante apres il faut faire d'autre plante

            if (random(0, 100) < 3) {
                //todo permetre de verifier si on est une plante eau ou plante de terre
                if (this->decor[x][y].estMarchable()) { // Vérifier si l'emplacement est vide
                    bool inEau = false;
                    if(this->decor[x][y].estEau()){
                        inEau = true;
                    }

                    this->decor[x][y] = Plante({x, y}, 'p',  CouleurAnimal::BLANC, this, 2, inEau);

                }
            }
        }
    }
    //*/
    std::cout << "Une nouvelle journée commence !" << std::endl;
}

void Carte::suprimerAnnimal(int x, int y){
    animaux[x][y] = Animal();
}

void Carte::suprimerDecor(int x, int y){
    decor[x][y] = Decor({x, y}, ' ', CouleurAnimal::VERT, this, false, false, true);
}

bool Carte::deplacerAnnimal(int x, int y, int newX, int newY) {
    // Vérifier

    //std::cout << "x: " << x << " / y: " << y << " vers -> " << "x: " << newX << " / y: " << newY  << std::endl;
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur ||
        newX < 0 || newX >= largeur || newY < 0 || newY >= hauteur) {
        //std::cout << "en dehors des limite" << std::endl;
        return false;
    }

    if(!this->decor[newX][newY].estMarchable()){
        //std::cout << "zone protect" << std::endl;
        return false;
    }

    if (this->decor[newX][newY].estEau() && animaux[x][y].tDeplacement() != DeplacementType::NAGE) {
        //std::cout << "nage pas" << std::endl;
        return false;
    }

    if (!this->decor[newX][newY].estEau() && animaux[x][y].tDeplacement() != DeplacementType::MARCHE) {
        //std::cout << "marche pas" << std::endl;
        return false;
    } 

    //Déplacer
    animaux[newX][newY] = animaux[x][y];
    this->suprimerAnnimal(x, y);
    return true;
}

bool Carte::positionOccupee(int x, int y) {
    // Vérifier
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
        return false;
    }

    // Vérifier objet non vide
    return !animaux[x][y].estVide();
}
