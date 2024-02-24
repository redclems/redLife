#ifndef DEPLACEMENTSTRATEGY_HPP
#define DEPLACEMENTSTRATEGY_HPP

//declaration avancée de annimal
//du a une dependance circulaire
class Animal;
struct Position;

class DeplacementStrategy {
public:
    void deplacer(Animal* annimal);

    virtual Position calculDeplacer(Animal* animal) = 0;
};

class DeplacementBasic : public DeplacementStrategy {
public:
    DeplacementBasic();
    Position calculDeplacer(Animal* animal) override;
};

class DeplacementReflechitHerbivore : public DeplacementStrategy {
public:
    DeplacementReflechitHerbivore();
    Position calculDeplacer(Animal* animal) override;
};

class DeplacementReflechitCarnivore : public DeplacementStrategy {
public:
    DeplacementReflechitCarnivore();
    Position calculDeplacer(Animal* animal) override;
};

#endif // DEPLACEMENTSTRATEGY_HPP
