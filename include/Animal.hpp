#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <vector>
#include <string>

#include "AlimentationType.hpp"
#include "DeplacementType.hpp"
#include "Couleur.hpp"

#include "Element.hpp"

class DeplacementStrategy;
class Plante;
class Carte;
struct Position;

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

enum class TypeAnimal {
    RENARD,
    POISSON,
    LAPIN,
    SCHBALUNG
};


class Animal : public Element{
private:
    ParamAnimal parametres;
    TypeAnimal typeAnimal;
    AlimentationType habitudeAlimentaire;
    DeplacementType typeDeplacement;
    DeplacementStrategy* strategieDeplacement;
    int dernierReproduction;

    void resetDernierReproduction();
    Position trouverPositionAuTour();
public:
 
    Animal() = default; 
    virtual ~Animal() = 0;


    Animal(Position pos, char s, Couleur c, Carte* carte,const ParamAnimal& parametres,
        AlimentationType habitudeAlimentaire, DeplacementType typeDeplacement, DeplacementStrategy* strategieDeplacement, TypeAnimal typeAnimal);

    void seDeplacer();
    void nouveauJour();
    void manger(Plante* plt);
    void manger(Animal* annimal);
    bool reproduire(Animal* annimal);
    void boire();

    void ajDegat(int niv, std::string typeDegat="degat");
    void supFaim(int niv);

    bool estPlusGrosQue(Animal* animal) const;//pourais etre remplacer par une surcharge
    DeplacementType tDeplacement() const {return typeDeplacement;};
    AlimentationType tAlimentaire() const {return habitudeAlimentaire;};
    TypeAnimal tAnimal() const {return typeAnimal;};
    ParamAnimal getParam() const {return parametres;};
    int getDernierReproduction() const {return dernierReproduction;};
    std::vector<std::vector<int>> getMatrixAround();
    bool peuxSeReproduire() const;

    static Animal* creerNouvelAnimal(TypeAnimal typeAnimal, int newX, int newY, Carte* carte);
};

inline Animal::~Animal() {}

#endif // ANIMAL_HPP
