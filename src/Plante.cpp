#include "Plante.hpp"

Plante::Plante(int x, int y, char s, CouleurAnimal c, Carte* carte, int niveauNutrition, bool pousseDansEau) 
    : Element(x, y, s, c, TypeElement::PLANTE, carte), niveauNutrition(niveauNutrition), pousseDansEau(pousseDansEau) {}


void Plante::methodeVidePourFaireUneAbstracClasse(){
    
}