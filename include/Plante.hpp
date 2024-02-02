#ifndef PLANTE_HPP
#define PLANTE_HPP

class Plante {
private:
    int niveauNutrition;
    int raretePousse;
    bool pousseDansEau;

public:
    Plante();

    void pousse();
};

#endif // PLANTE_HPP
