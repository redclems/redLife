#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <vector>
#include "Element.hpp"
#include "Plante.hpp"
#include "AlimentationType.hpp"
#include "DeplacementType.hpp"
#include "DeplacementStrategy.hpp"


struct ParamAnimal {
    float vitesse;
    int niveauFaim;
    int niveauSoif;
    int barreDeVie;
    float poids;
    float tailleHauteur;
    float tailleLargeur;
    int gourmandise;
    int envieReproduction;
    int espritAventure;
    int tempPourEtreAdulte;
    int tempExistantMoyen;
};

enum class TypeAnnimal {
    RENARD,
    POISSON,
    LAPIN,
    SCHBALUNG
};


class Animal : public Element{
private:
    ParamAnimal parametres;
    TypeAnnimal typeAnnimal;
    AlimentationType habitudeAlimentaire;
    DeplacementType typeDeplacement;
    DeplacementStrategy* strategieDeplacement;
    int dernierReproduction;

public:

    virtual ~Animal() = default; 
    Animal(); 

    Animal(Position pos, char s, CouleurAnimal c, Carte* carte,const ParamAnimal& parametres,
        AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement, DeplacementStrategy* strategieDeplacement, TypeAnnimal typeAnnimal);

    void seDeplacer();
    void newJour();
    void manger(Plante* plt);
    void manger(Animal* annimal);
    bool reproduire(Animal* annimal);
    bool estPlusGrosQue(Animal* animal);
    void boire();
    DeplacementType tDeplacement();
    AlimentationType tAlimentaire();
    TypeAnnimal tAnnimal();
    ParamAnimal getParam();
    int getDernierReproduction();
    void resetDernierReproduction();
    std::vector<std::vector<int>> getMatrixAround();
    bool peuxSeReproduire();

    void addDegat(int niv);
    void delFaim(int niv);




    static Animal* creerNouvelAnimal(TypeAnnimal typeAnimal, int newX, int newY, Carte* carte);

    virtual void methodeVidePourFaireUneAbstracClasse();
};

#endif // ANIMAL_HPP
