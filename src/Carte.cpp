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


Carte::Carte(int hauteur, int largeur) :
    hauteur(hauteur),
    largeur(largeur) {
    // Initialisation de la matrice d'éléments représentant la carte
    this->heure = 0;
    this->jour = 0;
    this->nbElement = 0;

    this->decor.resize(largeur, std::vector<Decor*>(hauteur)); // Initialiser la matrice decor
    this->animaux.resize(largeur, std::vector<Animal*>(hauteur)); // Initialiser la matrice animaux

    for (int y = 0; y < this->hauteur; ++y) {
        for (int x = 0; x < this->largeur; ++x) {
            this->decor[x][y] = new Decor;
            this->animaux[x][y] = new Vide;
        }
    }
}

int random(int min, int max) {
    std::random_device rd; // Permet d'initialiser le générateur aléatoire
    std::mt19937 gen(rd()); // Générateur aléatoire utilisant l'algorithme de Mersenne Twister
    std::uniform_int_distribution<> distrib(min, max); // Distribution que devront respecter les nombres générés -> uniforme de 1 à 6

    return distrib(gen); // Utilise le générateur pour produire un nombre respectant la distribution
    //il y a pas une bonne repartition aleatoire
}

void Carte::createCarte() {
    
    std::cout << "taille carte : y " << this->hauteur << " / x < " << this->largeur << std::endl;
    creerLeDecor();
    creerLesAnimaux();
}


void Carte::creerLeDecor(){
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
                        if(!enDehorDesLimites(newX, newY)){
                            this->decor[newX][newY] = new Decor({newX, newY}, 'e', Couleur::BLEU, this, false, true, true);
                        }
                    }
                }
            }else if (rand < 6 && !positionEstOccupeer(x, y)) {
                for (int dx = 0; dx <= 1; dx++) {
                    for (int dy = 0; dy <= 1; dy++) {
                        int newX = x + dx;
                        int newY = y + dy;
                        if(!enDehorDesLimites(newX, newY)){
                            this->decor[newX][newY] = new Decor({newX, newY}, '"', Couleur::VERT, this, true, false, true);
                        }
                    }
                }
            }else if(!this->decor[x][y]->estMarchable()){
                this->decor[x][y] = new Decor({x, y}, ' ', Couleur::VERT, this, false, false, true);//terre de base
            }
        }
    }

    std::cout << "Decor c'est fait " << std::endl;
}

void Carte::creerLesAnimaux(){
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
                    case 1:
                    case 2:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnimal::LAPIN, x, y, this);
                        break;
                    case 3:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnimal::RENARD, x, y, this);
                        break;
                    case 4:
                        this->animaux[x][y] = Animal::creerNouvelAnimal(TypeAnimal::POISSON, x, y, this);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    std::cout << "La carte a été créée avec succès !" << std::endl;
}

void Carte::lancer() {
    while (true) {

        //nouveau jour
        if (heure >= 10 || (heure == 0 && jour == 0)) {
            nouvelleJournee();
        }

        afficherCarte();

        nouvelleHeure();

        //attendre
        sleep(1);
    }
}
void Carte::nouvelleJournee() {

    heure = 0;
    jour++;

    //faire pousser les plantes
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            //5% de chance d'une plante apres il faut faire d'autre plante

            if (random(0, 100) < 2) {
                //todo permetre de verifier si on est une plante eau ou plante de terre
                if (decor[x][y]->estMarchable()) { // Vérifier si l'emplacement est vide
                    bool inEau = false;
                    if(decor[x][y]->estEau()){
                        inEau = true;
                    }

                    decor[x][y] = new Plante({x, y}, 'p',  Couleur::BLANC, this, 4, inEau);

                }
            }
            //a jout de l'age au elment
            if (!animaux[x][y]->estVide()) {
                animaux[x][y]->nouveauJour();
            }
            decor[x][y]->addJour();
        }
    }


    //suprimer la nouriture consomer par l'annimal dans la journée
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (!animaux[x][y]->estVide()) {
                animaux[x][y]->supFaim(1);
            }
        }
    }

    std::cout << "Une nouvelle journée commence !" << std::endl;
}
void Carte::afficherCarte() {
    afficherLigneEnHautDeLaCarte();
    nbElement = 0;
    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (animaux[x][y]->estVide()) {
                decor[x][y]->getDraw(); // Afficher le décor
            } else {
                animaux[x][y]->getDraw(); // Afficher l'animal
                nbElement++;
            }
        }
        std::cout << "|" << std::endl; // Aller à la ligne pour afficher la prochaine rangée
    }
}

void Carte::afficherLigneEnHautDeLaCarte() const{
    // affichage
    int tailleTextEnHaut = 18; // pour afficher "j:  / h:  / nbAn " 
    tailleTextEnHaut += static_cast<int>(std::log10(jour)) + 1;

    if(heure < 10){
        tailleTextEnHaut++;
    }else{
        tailleTextEnHaut+=2;
    }

    tailleTextEnHaut += static_cast<int>(std::log10(nbElement)) + 1;
    for (int i = 0; i < largeur-(tailleTextEnHaut); ++i) {
        std::cout << "-";
    }

    std::cout << " j: " << jour << " / h: " << heure << " / nbAn " << nbElement << std::endl;
}

void Carte::nouvelleHeure() {
    heure++;

    // Créer une copie de la liste d'animaux
    std::vector<std::vector<Animal*>> animauxCopie = animaux;

    for (int y = 0; y < hauteur; ++y) {
        for (int x = 0; x < largeur; ++x) {
            if (!animauxCopie[x][y]->estVide()) {
                animaux[x][y]->newPos(x, y); // pour etre sur qu'il a les bonnes coordonnées
                animaux[x][y]->seDeplacer();
            }
        }
    }
}

void Carte::suprimerAnimal(int x, int y){
    //mort de l'annimal
    animaux[x][y] = new Vide;
}

void Carte::addAnimal(int x, int y, Animal* animal){
    animaux[x][y] = animal;
}

void Carte::suprimerElement(int x, int y){
    //a jout de l'age au elment
    if (animaux[x][y]->estVide()) {
        suprimerDecor(x, y);
    }else{
        suprimerAnimal(x, y);
    }
}

void Carte::suprimerDecor(int x, int y, bool eau){
    if(eau){
        decor[x][y] = new Decor({x, y}, 'e', Couleur::BLEU, this, false, true, true);
    }else{
        decor[x][y] = new Decor({x, y}, ' ', Couleur::VERT, this, false, false, true);
    }
}

bool Carte::deplacerAnimal(int x, int y, int newX, int newY) {


    if (!peuxAllerSur(newX, newY, animaux[x][y])) {
        //std::cout << "en dehors des limite" << std::endl;
        return false;
    }

    auto* animalNewPos    = animaux[newX][newY];
    auto* animalActuelPos = animaux[x][y];

    //verifier que le deplacement ne depasse pas la vitesse de deplacement de l'annimal
    auto animalVitesse = animalActuelPos->getParam().vitesse+0.5;
    if ((newX - x)*(newX - x) + (newY - y)*(newY - y) > animalVitesse*animalVitesse) {
        return false;
    }

    //cas ou l'annimal mange des plantes et il y a une plante
    if(animalActuelPos->tAlimentaire() == AlimentationType::HERBIVORE || animalActuelPos->tAlimentaire() == AlimentationType::OMNIVORE){
        if(decor[newX][newY]->getType() == TypeElement::PLANTE){
            auto* plantePtr = dynamic_cast<Plante*>(this->decor[newX][newY]);
            if (plantePtr != NULL) {
                animaux[x][y]->manger(plantePtr);
                suprimerDecor(newX, newY, this->decor[newX][newY]->estEau());
            }
        }
    }

    if (!animalNewPos->estVide()) {
        if(animalNewPos->tAnimal() == animalActuelPos->tAnimal()) {
            //deux annimaux de la meme espece reproduction
            if(animaux[x][y]->reproduire(animalNewPos)){
                return false;
            }
        }else if(animalActuelPos->tAlimentaire() == AlimentationType::CARNIVORE || animalActuelPos->tAlimentaire() == AlimentationType::OMNIVORE){
                // cas où l'animal mange un autre animal d'une race différente car ils vont sur la même case
                animaux[x][y]->manger(animalNewPos);
        }else{
            //cas ou l'annimal et herbivore
            return false;
        }
    }

    //Déplacer si la position est pas occuper
    if(!positionEstOccupeer(newX, newY)){
        animaux[newX][newY] = animaux[x][y];
        animaux[x][y] = new Vide;
        return true;
    }
    //*/
    return false;
}

bool Carte::estMemeTypeQue(int x, int y, Animal* animal){
    if(animaux[x][y]->tAnimal() == animal->tAnimal()) {
        return true;
    }
    return false;
}

bool Carte::estUnHerbivore(int x, int y) const{
    return animaux[x][y]->tAlimentaire() == AlimentationType::HERBIVORE;
}


bool Carte::ilYaUnePlante(int x, int y) const{
    if(decor[x][y]->getType() == TypeElement::PLANTE){
        auto* plantePtr = dynamic_cast<Plante*>(decor[x][y]);
        if (plantePtr != NULL) {
            return true;
        }
    }
    return false;
}

bool Carte::peuxAllerSur(int newX, int newY, Animal* animal){
    if (enDehorDesLimites(newX, newY)) {
        //std::cout << "en dehors des limite" << std::endl;
        return false;
    }

    if(!decor[newX][newY]->estMarchable()){
        //std::cout << "zone protect" << std::endl;
        return false;
    }

    if (decor[newX][newY]->estEau() && animal->tDeplacement() != DeplacementType::NAGE) {
        //std::cout << "nage pas" << std::endl;
        return false;
    }

    if (!decor[newX][newY]->estEau() && animal->tDeplacement() != DeplacementType::MARCHE) {
        //std::cout << "marche pas" << std::endl;
        return false;
    }
    return true;

}

bool Carte::enDehorDesLimites(int x, int y) const{
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
        return true;
    }else{
        return false;
    }
}

bool Carte::estCache(int x, int y) const{
    // Vérifier objet non vide

    return decor[x][y]->estCache();
}


bool Carte::positionEstOccupeer(int x, int y) const{
    // Vérifier objet non vide

    return !animaux[x][y]->estVide();
}
