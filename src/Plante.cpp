#include "Plante.hpp"

Plante::Plante(Position pos, char s, CouleurAnimal c, Carte* carte, int niveauNutrition, bool pousseDansEau) 
    : Decor(pos, s, c, TypeElement::PLANTE, carte, false, pousseDansEau, true), niveauNutrition(niveauNutrition), pousseDansEau(pousseDansEau) {}


void Plante::methodeVidePourFaireUneAbstracClasse(){
    
}