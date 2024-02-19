#ifndef CARTE_HPP
#define CARTE_HPP

#include <vector>
#include "Decor.hpp"
#include "Animal.hpp"

class Carte {
private:
    int nbElement;

    int hauteur;
    int largeur;
    int heure;
    int jour;
    std::vector<std::vector<Decor *>> decor; // Matrice pour les éléments décoratifs
    std::vector<std::vector<Animal *>> animaux; // Matrice pour les animaux
    

public:
    Carte(int hauteur, int largeur);

    void afficherCarte();
    void createMap();
    void run();
    void nouvelJournee();
    void nouvelHeure();
    bool deplacerAnnimal(int x, int y, int newX, int newY);
    bool positionEstOccupeer(int x, int y);
    bool EnDehorDesLimte(int x, int y);

    void suprimerAnnimal(int x, int y);
    void suprimerDecor(int x, int y);
    void suprimerElement(int x, int y);
    void suprimerDecor(int x, int y, bool eau);
    void addAnnimal(int x, int y, Animal* animal);
    Animal* getAnnimal(int x, int y);

    bool estUnHerbivore(int x, int y);
    bool estMemeTypeQue(int x, int y, Animal* animal);
    bool ilYaUnePlante(int x, int y);
    bool peuxAllerSur(int newX, int newY, Animal* animal);
};

#endif // CARTE_HPP
