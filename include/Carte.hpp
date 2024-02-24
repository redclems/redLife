#ifndef CARTE_HPP
#define CARTE_HPP

#include <vector>

class Decor;
class Animal;

class Carte {
private:
    int nbElement;

    int hauteur;
    int largeur;
    int heure;
    int jour;
    std::vector<std::vector<Decor *>> decor; // Matrice pour les éléments décoratifs
    std::vector<std::vector<Animal *>> animaux; // Matrice pour les animaux
    
    void afficherLigneEnHautDeLaCarte() const;
    void creerLeDecor();
    void creerLesAnimaux();

public:
    Carte(int hauteur, int largeur);

    void afficherCarte();
    void createCarte();
    void lancer();
    void nouvelleJournee();
    void nouvelleHeure();
    bool deplacerAnimal(int x, int y, int newX, int newY);

    void suprimerAnimal(int x, int y);
    void suprimerElement(int x, int y);
    void suprimerDecor(int x, int y, bool eau=false);
    void addAnimal(int x, int y, Animal* animal);

    Animal* getAnimal(int x, int y) const { return animaux[x][y];}

    bool estCache(int x, int y) const;
    bool estUnHerbivore(int x, int y) const;
    bool estMemeTypeQue(int x, int y, Animal* animal);
    bool ilYaUnePlante(int x, int y) const;
    bool peuxAllerSur(int newX, int newY, Animal* animal);
    bool positionEstOccupeer(int x, int y) const;
    bool enDehorDesLimites(int x, int y) const;
};

#endif // CARTE_HPP
