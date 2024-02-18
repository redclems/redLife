#include "Animal.hpp"
#include "Carte.hpp"
#include <iostream>
#include "Animaux.hpp"

Animal::Animal(Position pos, char s, CouleurAnimal c, Carte* carte, 
           const ParamAnimal& parametres, AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement,
           DeplacementStrategy* strategieDeplacement, TypeAnnimal typeAnnimal) 
    : Element(pos, s, c, TypeElement::ANNIMAL,carte, parametres.tempExistantMoyen),
      parametres(parametres), habitudeAlimentaire(habitudeAlimentaire),
      typeDeplacement(typeDeplacement), strategieDeplacement(strategieDeplacement),  typeAnnimal(typeAnnimal){
        dernierReproduction=0;
    }

Animal::Animal() : Element(){
}

void Animal::methodeVidePourFaireUneAbstracClasse(){
}

void Animal::seDeplacer() {
    // Implémentez le comportement de déplacement de l'animal ici
    this->strategieDeplacement->deplacer(this);
}

void Animal::manger(Plante* plt) {
    // Implémentez le comportement de manger de l'animal ici
    parametres.niveauFaim += plt->getNiveauNutrition();
}

void Animal::manger(Animal* annimal) {
    // Implémentez le comportement de manger de l'animal ici
    float surfaceThis = parametres.tailleHauteur * parametres.tailleLargeur;
    float surfaceAutre = annimal->parametres.tailleHauteur * annimal->parametres.tailleLargeur;

    if (surfaceAutre > surfaceThis * 2.0f) {
        // L'autre animal est deux fois plus gros, this meurt
        this->addDegat(parametres.barreDeVie); // 100% de dégâts
    }else{
        // Calculer le nombre d unites de nourriture (chaque 10 cm²c est une unite)
        int nourritureGagnee = static_cast<int>(surfaceAutre / 10.0f);

        parametres.niveauFaim += nourritureGagnee;
        delFaim(1);//car sa consomme de l'energie

        // Supprimer l'animal mangé de la carte
        if(Element::afficherLesCauseDeMort){std::cout << "manger par un autre annimal" << std::endl;}
        this->carte->suprimerAnnimal(annimal->getPosX(), annimal->getPosY());
    }
}


void Animal::boire() {
    // Implémentez le comportement de boire de l'animal  qu'on vas passer car pas tres utile
}

void Animal::newJour() {
    // Implémentez le comportement de boire de l'animal  qu'on vas passer car pas tres utile
    dernierReproduction++;
    addJour();
}

bool Animal::reproduire(Animal* animal) {
    // Implémentez le comportement de reproduction de l'animal ici

    //voir si les annimaux peuvent ce reproduire
    if(this->getAge() < this->getParam().tempPourEtreAdulte || animal->getAge() < animal->getParam().tempPourEtreAdulte){
        return false;
    }

    if(this->getDernierReproduction() <= 2 || animal->getDernierReproduction() <= 2){
        //les annimaux peuvent ce reproduire que les deux jour ce pour toute les espece
        return false;
    }

    if(this->getParam().niveauFaim <= 0 || animal->getParam().niveauFaim <= 0){
        //les annimaux peuvent ce reproduire quand il on faim
        return false;
    }


    // Vérifier si les deux animaux sont de la même espèce
    if (typeAnnimal != animal->tAnnimal()) {
        return false;
    }

    // Trouver une position libre autour de l'animal actuel
    int newX = getPosX();
    int newY = getPosY();

    double rayon = 1.3; // Distance de déplacement autour de l'animal
    int nombreIterationsMax = 25; // Limite d'itérations
    int nombreIterations = 0;

    // Itérer autour de l'animal actuel
    double angle = 0.0;
    while ((carte->EnDehorDesLimte(newX, newY) || carte->positionEstOccupeer(newX, newY)) && nombreIterations < nombreIterationsMax) {
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
    if(!carte->positionEstOccupeer(newX, newY) && !carte->EnDehorDesLimte(newX, newY)){
        if(carte->peuxAllerSur(newX, newY, this)){
            
            // Créer un nouvel animal de la même espèce à la nouvelle position
            Animal* nouvelAnimal = Animal::creerNouvelAnimal(tAnnimal(), newX, newY, carte);

            // Ajouter le nouvel animal à la carte
            carte->addAnnimal(newX, newY, nouvelAnimal);
            //std::cout << ", age, " << this->getAge() << ", tempPourAd, " << this->getParam().tempPourEtreAdulte << ", dern, " << this->getDernierReproduction() << ", nivFaim, " << this->getParam().niveauFaim << " avec :"<< std::endl;
            //std::cout << ", age, " << animal->getAge() << ", tempPourAd, " << animal->getParam().tempPourEtreAdulte << ", dern, " << animal->getDernierReproduction() << ", nivFaim, " << animal->getParam().niveauFaim << std::endl;
            this->resetDernierReproduction();
            animal->resetDernierReproduction();
            return true;
        }
    }
    return false;
    //verrifier que l'annimal a le droit d'y aller
}

Animal* Animal::creerNouvelAnimal(TypeAnnimal typeAnimal, int newX, int newY, Carte* carte) {
    Animal* nouvelAnimal = nullptr;
    switch (typeAnimal) {
        case TypeAnnimal::RENARD:
            nouvelAnimal = new Renard({newX, newY}, carte);
            break;
        case TypeAnnimal::POISSON:
            nouvelAnimal = new Poisson({newX, newY}, carte);
            break;
        case TypeAnnimal::LAPIN:
            nouvelAnimal = new Lapin({newX, newY}, carte);
            break;
        default:
            return nullptr;
    }
    return nouvelAnimal;
}

void Animal::addDegat(int niv) {
    parametres.barreDeVie-= niv;
    if(parametres.barreDeVie<=0){
        this->carte->suprimerAnnimal(getPosX(), getPosY());
        if(Element::afficherLesCauseDeMort){std::cout << "mort de degat" << std::endl;}
    }
}

void Animal::delFaim(int niv) {
    parametres.niveauFaim-= niv;
    if(parametres.niveauFaim<=0){
        parametres.barreDeVie-= 1;
        if(parametres.barreDeVie<=0){
            this->carte->suprimerAnnimal(getPosX(), getPosY());
            if( Element::afficherLesCauseDeMort){std::cout << "mort de faim" << std::endl;}
        }
    }
}

ParamAnimal Animal::getParam() {
    return parametres;
}

int Animal::getDernierReproduction() {
    return dernierReproduction;
}

void Animal::resetDernierReproduction() {
    dernierReproduction=0;
}

DeplacementType Animal::tDeplacement() {
    return typeDeplacement;
}

AlimentationType Animal::tAlimentaire() {
    return habitudeAlimentaire;
}

TypeAnnimal Animal::tAnnimal(){
    return typeAnnimal;
}

int Animal::ceQuiCePasseLorsDuDeplacement() {
    // Implémentez ce qui ce passe si l'annimal arrive sur la nouvelle position
    // 0 - deplacement ok / 1 - deplacement impossible / 2 - element manger / 3 - reproduction / 4 - boire

    return 0;
}