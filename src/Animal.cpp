#include "Animal.hpp"
#include "Element.hpp"
#include "Carte.hpp"
#include "Plante.hpp"
#include <iostream>
#include "Animaux.hpp"
#include "TypeElement.hpp"
#include "DeplacementStrategy.hpp"

Animal::Animal(Position pos, char s, Couleur c, Carte* carte, 
           const ParamAnimal& parametres, AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement,
           DeplacementStrategy* strategieDeplacement, TypeAnimal typeAnimal) 
    : Element(pos, s, c, TypeElement::ANNIMAL,carte, parametres.tempExistantMoyen),
      parametres(parametres), habitudeAlimentaire(habitudeAlimentaire),
      typeDeplacement(typeDeplacement), strategieDeplacement(strategieDeplacement),  typeAnimal(typeAnimal){
        dernierReproduction=0;
    }

void Animal::seDeplacer() {
    // Implémentez le comportement de déplacement de l'animal ici
    strategieDeplacement->deplacer(this);
}

void Animal::manger(Plante* plt) {
    // Implémentez le comportement de manger de l'animal ici
    parametres.niveauFaim += plt->getNiveauNutrition();
}

void Animal::manger(Animal* animal) {
    // Implémentez le comportement de manger de l'animal ici
    float surfaceThis = parametres.tailleHauteur * parametres.tailleLargeur;
    float surfaceAutre = animal->parametres.tailleHauteur * animal->parametres.tailleLargeur;

    if (surfaceAutre > surfaceThis * 2.0f) {
        // L'autre animal est deux fois plus gros, this meurt
        ajDegat(parametres.barreDeVie); // 100% de dégâts
    }else{
        // Calculer le nombre d unites de nourriture (chaque 10 cm²c est une unite)
        int nourritureGagnee = static_cast<int>(surfaceAutre / 10.0f);

        parametres.niveauFaim += nourritureGagnee;
        supFaim(1);//car sa consomme de l'energie

        // Supprimer l'animal mangé de la carte
        if(Element::afficherLesCauseDeMort){std::cout << "manger par un autre annimal" << std::endl;}
        carte->suprimerAnimal(animal->getPosX(), animal->getPosY());
    }
}


void Animal::boire() {
    // Implémentez le comportement de boire de l'animal  qu'on vas passer car pas tres utile
}

void Animal::nouveauJour() {
    // Implémentez le comportement de boire de l'animal  qu'on vas passer car pas tres utile
    dernierReproduction++;
    supFaim(1);
}

bool Animal::peuxSeReproduire() const{
    if(getAge() < getParam().tempPourEtreAdulte || getDernierReproduction() <= 2 || getParam().niveauFaim <= 0){
        return false;
    }
    return true;
} 

bool Animal::reproduire(Animal* animal) {
    // Implémentez le comportement de reproduction de l'animal ici

    if(!peuxSeReproduire() || !animal->peuxSeReproduire()){
        //les annimaux peuvent ce reproduire quand il on faim
        return false;
    }

    // Vérifier si les deux animaux sont de la même espèce
    if (typeAnimal != animal->tAnimal()) {
        return false;
    }

    Position pos = trouverPositionAuTour();
    int newX = pos.posX;
    int newY = pos.posY;

    //si c'est possible
    if(!carte->positionEstOccupeer(newX, newY) && !carte->enDehorDesLimites(newX, newY)){
        if(carte->peuxAllerSur(newX, newY, this)){
            
            // Créer un nouvel animal de la même espèce à la nouvelle position
            Animal* nouvelAnimal = Animal::creerNouvelAnimal(tAnimal(), newX, newY, carte);

            // Ajouter le nouvel animal à la carte
            carte->addAnimal(newX, newY, nouvelAnimal);
            //std::cout << ", age, " << this->getAge() << ", tempPourAd, " << this->getParam().tempPourEtreAdulte << ", dern, " << this->getDernierReproduction() << ", nivFaim, " << this->getParam().niveauFaim << " avec :"<< std::endl;
            //std::cout << ", age, " << animal->getAge() << ", tempPourAd, " << animal->getParam().tempPourEtreAdulte << ", dern, " << animal->getDernierReproduction() << ", nivFaim, " << animal->getParam().niveauFaim << std::endl;
            resetDernierReproduction();
            animal->resetDernierReproduction();
            return true;
        }
    }
    return false;
    //verrifier que l'annimal a le droit d'y aller
}

Position Animal::trouverPositionAuTour(){
    // Trouver une position libre autour de l'animal actuel
    int newX = getPosX();
    int newY = getPosY();

    double rayon = 1.3; // Distance de déplacement autour de l'animal
    int nombreIterationsMax = 25; // Limite d'itérations
    int nombreIterations = 0;

    // Itérer autour de l'animal actuel  TODO faire methode find zone
    double angle = 0.0;
    while ((carte->enDehorDesLimites(newX, newY) || carte->positionEstOccupeer(newX, newY)) && nombreIterations < nombreIterationsMax) {
        // Décaler vers la droite et vers le bas pour trouver une position libre
        newX = static_cast<int>(getPosX() + rayon * std::cos(angle));
        newY = static_cast<int>(getPosY() + rayon * std::sin(angle));


        // Incrémenter l'angle pour se déplacer en cercle
        angle += 2 * M_PI / (nombreIterationsMax/2);

        if(nombreIterations>nombreIterationsMax/2){
            rayon=2.3;
        }
        // Incrémenter le nombre d'itérations
        nombreIterations++;
    }
    return Position(newX, newY);
}

Animal* Animal::creerNouvelAnimal(TypeAnimal typeAnimal, int newX, int newY, Carte* carte) {
    Animal* nouvelAnimal = nullptr;
    switch (typeAnimal) {
        case TypeAnimal::RENARD:
            nouvelAnimal = new Renard({newX, newY}, carte);
            break;
        case TypeAnimal::POISSON:
            nouvelAnimal = new Poisson({newX, newY}, carte);
            break;
        case TypeAnimal::LAPIN:
            nouvelAnimal = new Lapin({newX, newY}, carte);
            break;
        default:
            return nullptr;
    }
    return nouvelAnimal;
}

void Animal::ajDegat(int niv, std::string typeDegat) {
    parametres.barreDeVie-= niv;
    if(parametres.barreDeVie<=0){
        carte->suprimerAnimal(getPosX(), getPosY());
        if(Element::afficherLesCauseDeMort){std::cout << "mort de " << typeDegat << std::endl;}
    }
}

void Animal::supFaim(int niv) {
    parametres.niveauFaim-= niv;
    if(parametres.niveauFaim<=0){
        ajDegat(1, "faim");
    }
}

void Animal::resetDernierReproduction() {
    dernierReproduction=0;
}

bool Animal::estPlusGrosQue(Animal* animal) const{
    float surfaceThis = getParam().tailleHauteur * getParam().tailleLargeur;
    float surfaceAutre = animal->getParam().tailleHauteur * animal->getParam().tailleLargeur;

    if (surfaceAutre > surfaceThis * 2.0f) {
        return false;
    }
    return true;
}

std::vector<std::vector<int>> Animal::getMatrixAround(){
    /*
    retourner une matrice d'entier de 5*5 autour de lui avec 
    0 pas possible de si déplacer, 1 case vide, 2 nourriture, 3 prédateur et 4 même type, 5 un herbivore mangeable, 6 herbivore pas mangeable
    */
    std::vector<std::vector<int>> matrix(5, std::vector<int>(5, 0)); // Initialisation de la matrice avec des zéros

    // Déterminer la position de départ pour parcourir la matrice
    int startX = getPosX() - 2;
    int startY = getPosY() - 2;

    // Parcourir les éléments autour de l'animal dans la carte
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // Vérifier si la position est valide sur la carte
            int x = startX + i;
            int y = startY + j;
            if (!carte->enDehorDesLimites(x, y)) {
                if(carte->positionEstOccupeer(x, y) && !carte->estCache(x, y)){//si il y a un annimal pas dans une zone de decor cacher
                    if(carte->estMemeTypeQue(x, y, this)){//meme type
                        matrix[i][j] = 4; 
                    }else if(carte->estUnHerbivore(x, y)){
                        if(estPlusGrosQue(carte->getAnimal(x, y))){
                            matrix[i][j] = 5;
                        }else{
                            matrix[i][j] = 6;
                        }
                    }else{//dans le cas contraire c'est un predateur potenciel
                        matrix[i][j] = 3; 
                    }
                }else if(carte->ilYaUnePlante(x, y) && (this->tAlimentaire() == AlimentationType::HERBIVORE || this->tAlimentaire() == AlimentationType::OMNIVORE)){ //pour les mangeur de plante
                    matrix[i][j] = 2;
                }else if(carte->peuxAllerSur(x, y, this)){
                    matrix[i][j] = 1; 
                }else{
                    matrix[i][j] = 0;
                }
            }
        }
    }

    return matrix;
}
