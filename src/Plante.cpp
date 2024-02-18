#include "Plante.hpp"

Plante::Plante(Position pos, char s, CouleurAnimal c, Carte* carte, int niveauNutrition, bool pousseDansEau) 
    : Decor(pos, s, c, TypeElement::PLANTE, carte, false, pousseDansEau, true, 3), niveauNutrition(niveauNutrition), pousseDansEau(pousseDansEau) {
    }


int Plante::getNiveauNutrition(){
    return niveauNutrition;
}


void Plante::methodeVidePourFaireUneAbstracClasse(){
    
}