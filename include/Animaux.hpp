#ifndef ANIMAUX_HPP
#define ANIMAUX_HPP

#include "Animal.hpp"


class Vide : public Animal {
public:
    Vide() : Animal() {};
    ~Vide() override = default; 
};


class Renard : public Animal {
public:
    Renard(Position pos, Carte* carte);
    ~Renard() override = default; 
};

class Poisson : public Animal {
public:
    Poisson(Position pos, Carte* carte);
    ~Poisson() override = default; 
};

class Lapin : public Animal {
public:
    Lapin(Position pos, Carte* carte);
    ~Lapin() override = default; 
};

class Schbalung : public Animal {
public:
    Schbalung(Position pos, Carte* carte);
    ~Schbalung() override = default; 
};

#endif // ANIMAUX_HPP
