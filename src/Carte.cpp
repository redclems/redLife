#include "Carte.hpp"

#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <random>

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

    this->decor.resize(largeur, std::vector<Decor*>(hauteur)); // Initialiser la matrice decor
    this->animaux.resize(largeur, std::vector<Animal*>(hauteur)); // Initialiser la matrice animaux

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            this->decor[x][y] = new Decor();
            this->animaux[x][y] = new Animal();
        }
    }
}

int random(int min, int max) {
    std::random_device rd; // Permet d'initialiser le générateur aléatoire
    std::mt19937 gen(rd()); // Générateur aléatoire utilisant l'algorithme de Mersenne Twister
    std::uniform_int_distribution<> distrib(min, max); // Distribution que devront respecter les nombres générés -> uniforme de 1 à 6

    return distrib(gen); // Utilise le générateur pour produire un nombre respectant la distribution
}

void Carte::createMap() {
    
    std::cout << "taille carte : y " << this->hauteur << " / x < " << this->largeur << std::endl;

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            //Les poind d'eau
            int rand = random(0, 100);
            if (rand < 1 && !positionEstOccupeer(x, y)) {
                int largeur_dx = random(1, 4);
                int hauteur_dy  = random(1, 4);
                for (int dx = -largeur_dx; dx <= largeur_dx; dx++) {
                    for (int dy = -hauteur_dy; dy <= hauteur_dy; dy++) {
                        int newX = x + dx;
                        int newY = y + dy;
                        if(!EnDehorDesLimte(newX, newY)){
                            this->decor[newX][newY] = new Decor({newX, newY}, 'e', CouleurAnimal::BLEU, this, false, true, true);
                        }
                    }
                }
            }else if (rand < 6 && !positionEstOccupeer(x, y)) {
                for (int dx = 0; dx <= 1; dx++) {
                    for (int dy = 0; dy <= 1; dy++) {
                        int newX = x + dx;
                        int newY = y + dy;
                        if(!EnDehorDesLimte(newX, newY)){
                            this->decor[newX][newY] = new Decor({newX, newY}, '"', CouleurAnimal::VERT, this, true, false, true);
                        }
                    }
                }
            }else if(!this->decor[x][y]->estMarchable()){
                this->decor[x][y] = new Decor({x, y}, ' ', CouleurAnimal::VERT, this, false, false, true);//terre de base
            }
        }
    }

    std::cout << "Decor c'est fait " << std::endl;

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            //animaux
            int animalType = random(0, 5);

            if(!this->decor[x][y]->estEau()){
                animalType = random(0, 3);
            }else{ 
                animalType = 4; 
            }

            if (random(0, 100) < 5 && this->decor[x][y]->estMarchable()) {
                switch (animalType) {
                    case 0:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnnimal::LAPIN, x, y, this);
                        break;
                    case 1:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnnimal::LAPIN, x, y, this);
                        break;
                    case 2:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnnimal::LAPIN, x, y, this);
                        break;
                    case 3:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnnimal::RENARD, x, y, this);
                        break;
                    case 4:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnnimal::POISSON, x, y, this);
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
        if (this->heure >= 10 || (this->heure == 0 && this->jour == 0)) {
            this->nouvelJournee();
        }

        // afficher 
        this->afficherCarte();

        this->nouvelHeure();

        //attendre
        sleep(1);
    }
}

void Carte::afficherCarte() {
    // affichage
    int tailleEcrireJour = 10 + 8; // pour afficher "j: / h: "  + 8 / nbAn 
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

    for (int i = 0; i < this->largeur-(tailleEcrireJour+3); ++i) {
        std::cout << "-";
    }

    std::cout << "j: " << this->jour << " / h: " << this->heure << " / nbAn " << this->nbElement << std::endl;
    nbElement = 0;
    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            if (this->animaux[x][y]->estVide()) {
                this->decor[x][y]->getDraw(); // Afficher le décor
            } else {
                this->animaux[x][y]->getDraw(); // Afficher l'animal
                this->nbElement++;
            }
        }
        std::cout << "|" << std::endl; // Aller à la ligne pour afficher la prochaine rangée
    }
}

void Carte::nouvelHeure() {
    this->heure++;

    // Créer une copie de la liste d'animaux
    std::vector<std::vector<Animal*>> animauxCopie = this->animaux;

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            if (!animauxCopie[x][y]->estVide()) {
                this->animaux[x][y]->newPos(x, y); // pour etre sur qu'il a les bonnes coordonnées
                this->animaux[x][y]->seDeplacer();
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

            if (random(0, 100) < 2) {
                //todo permetre de verifier si on est une plante eau ou plante de terre
                if (this->decor[x][y]->estMarchable()) { // Vérifier si l'emplacement est vide
                    bool inEau = false;
                    if(this->decor[x][y]->estEau()){
                        inEau = true;
                    }

                    this->decor[x][y] = new Plante({x, y}, 'p',  CouleurAnimal::BLANC, this, 4, inEau);

                }
            }
            //a jout de l'age au elment
            if (!this->animaux[x][y]->estVide()) {
                this->animaux[x][y]->newJour();
            }
            this->decor[x][y]->addJour();
        }
    }


    //suprimer la nouriture consomer
    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            if (!animaux[x][y]->estVide()) {
                this->animaux[x][y]->delFaim(1);
            }
        }
    }


    //*/
    std::cout << "Une nouvelle journée commence !" << std::endl;
}

void Carte::suprimerAnnimal(int x, int y){
    //mort de l'annimal
    animaux[x][y] = new Animal;
}

void Carte::addAnnimal(int x, int y, Animal* animal){
    animaux[x][y] = animal;
}

Animal* Carte::getAnnimal(int x, int y){
    return animaux[x][y];
}

void Carte::suprimerElement(int x, int y){
    //a jout de l'age au elment
    if (this->animaux[x][y]->estVide()) {
        this->suprimerDecor(x, y);
    }else{
        this->suprimerAnnimal(x, y);
    }
}

void Carte::suprimerDecor(int x, int y){
    suprimerDecor(x, y, false);
}

void Carte::suprimerDecor(int x, int y, bool eau){
    if(eau){
        decor[x][y] = new Decor({x, y}, 'e', CouleurAnimal::BLEU, this, false, true, true);
    }else{
        decor[x][y] = new Decor({x, y}, ' ', CouleurAnimal::VERT, this, false, false, true);
    }
}

bool Carte::deplacerAnnimal(int x, int y, int newX, int newY) {
    // Vérifier

    
    if (!peuxAllerSur(newX, newY, animaux[x][y])) {
        //std::cout << "en dehors des limite" << std::endl;
        return false;
    }

    //verifier que le deplacement ne depasse pas la vitesse de deplacement de l'annimal
    if (sqrt(pow(newX - x, 2) + pow(newY - y, 2)) > animaux[x][y]->getParam().vitesse+0.5) {
        return false;
    }

    //cas ou l'annimal mange des plantes et il y a une plante
    if(animaux[x][y]->tAlimentaire() == AlimentationType::HERBIVORE || animaux[x][y]->tAlimentaire() == AlimentationType::OMNIVORE){
        if(this->decor[newX][newY]->getType() == TypeElement::PLANTE){
            Plante* plantePtr = dynamic_cast<Plante*>(this->decor[newX][newY]);
            if (plantePtr != NULL) {
                animaux[x][y]->manger(plantePtr);
                suprimerDecor(newX, newY, this->decor[newX][newY]->estEau());
            }
        }
    }

    if (!this->animaux[newX][newY]->estVide()) {
        if(this->animaux[newX][newY]->tAnnimal() == animaux[x][y]->tAnnimal()) {
            //deux annimaux de la meme espece reproduction
            if(animaux[x][y]->reproduire(this->animaux[newX][newY])){
                return false;
            }
        }else if(animaux[x][y]->tAlimentaire() == AlimentationType::CARNIVORE || animaux[x][y]->tAlimentaire() == AlimentationType::OMNIVORE){
                // cas où l'animal mange un autre animal d'une race différente car ils vont sur la même case
                animaux[x][y]->manger(this->animaux[newX][newY]);
        }else{
            //cas ou l'annimal et herbivore
            return false;
        }
    }

    //Déplacer si la position est pas occuper
    if(!positionEstOccupeer(newX, newY)){
        animaux[newX][newY] = animaux[x][y];
        animaux[x][y] = new Animal;
        return true;
    }
    return false;
}

bool Carte::estMemeTypeQue(int x, int y, Animal* animal){
    if(this->animaux[x][y]->tAnnimal() == animal->tAnnimal()) {
        return true;
    }
    return false;
}

bool Carte::estUnHerbivore(int x, int y){
    return animaux[x][y]->tAlimentaire() == AlimentationType::HERBIVORE;
}


bool Carte::ilYaUnePlante(int x, int y){
    if(this->decor[x][y]->getType() == TypeElement::PLANTE){
        Plante* plantePtr = dynamic_cast<Plante*>(this->decor[x][y]);
        if (plantePtr != NULL) {
            return true;
        }
    }
    return false;
}

bool Carte::peuxAllerSur(int newX, int newY, Animal* animal){
    if (EnDehorDesLimte(newX, newY)) {
        //std::cout << "en dehors des limite" << std::endl;
        return false;
    }

    if(!this->decor[newX][newY]->estMarchable()){
        //std::cout << "zone protect" << std::endl;
        return false;
    }

    if (this->decor[newX][newY]->estEau() && animal->tDeplacement() != DeplacementType::NAGE) {
        //std::cout << "nage pas" << std::endl;
        return false;
    }

    if (!this->decor[newX][newY]->estEau() && animal->tDeplacement() != DeplacementType::MARCHE) {
        //std::cout << "marche pas" << std::endl;
        return false;
    }
    return true;

}

bool Carte::EnDehorDesLimte(int x, int y){
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
        return true;
    }else{
        return false;
    }
}




bool Carte::positionEstOccupeer(int x, int y) {
    // Vérifier objet non vide

    return !animaux[x][y]->estVide();
}
