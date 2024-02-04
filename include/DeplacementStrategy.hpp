#ifndef DEPLACEMENTSTRATEGY_HPP
#define DEPLACEMENTSTRATEGY_HPP

#include "Animal.hpp"

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
#endif // DEPLACEMENTSTRATEGY_HPP
