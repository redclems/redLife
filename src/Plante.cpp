#include "Plante.hpp"

Plante::Plante(int x, int y, std::string s, CouleurAnimal c, Carte* carte, int niveauNutrition, bool pousseDansEau) 
    : Element(x, y, s, TypeElement::PLANTE, c, carte), niveauNutrition(niveauNutrition), pousseDansEau(pousseDansEau) {}
