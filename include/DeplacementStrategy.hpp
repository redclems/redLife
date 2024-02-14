#ifndef DEPLACEMENTSTRATEGY_HPP
#define DEPLACEMENTSTRATEGY_HPP

//declaration avancée de annimal
//du a une dependance circulaire
class Animal;
struct Position;

class DeplacementStrategy {
public:
    void deplacer(Animal* annimal);

    virtual Position calculDeplacer(Animal* annimal) = 0;
};

class DeplacementBasic : public DeplacementStrategy {
public:
    DeplacementBasic();
    Position calculDeplacer(Animal* annimal) override;
};

#endif // DEPLACEMENTSTRATEGY_HPP
