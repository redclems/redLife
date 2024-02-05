#ifndef DEPLACEMENTSTRATEGY_HPP
#define DEPLACEMENTSTRATEGY_HPP

//declaration avancée de annimal
//du a une dependance circulaire
class Animal;

class DeplacementStrategy {
public:
    virtual void deplacer(Animal& annimal) = 0;
};

class DeplacementBasic : public DeplacementStrategy {
public:
    void deplacer(Animal& annimal) override;
};

#include "Animal.hpp"


#endif // DEPLACEMENTSTRATEGY_HPP
