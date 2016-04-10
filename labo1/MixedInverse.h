#ifndef LABO1_MIXEDINVERSE_H
#define LABO1_MIXEDINVERSE_H

#include <vector>
#include <cmath>

#include "UniformGenerator.h"
#include "RandomValueGenerator.h"

class MixedInverse : public RandomValueGenerator<double> {
private:
    UniformRealGenerator<double>* generator;

public:

    MixedInverse(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator<double>(xs, ys) {

        generator = new UniformRealGenerator<double>(0, 1);
        generator->setSeed(seed);
    }

    double generate() const {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();

        // Ensuite, on applique la méthode des fonctions inverses.
        Piece<double> s = pieces[K];

        double x1 = s.p0.x, x2 = s.p1.x;
        double y1 = s.p0.y, y2 = s.p1.y;

        double U = generator->next();

        // Si y1 = y2, alors on est dans le cas d'une uniforme. Sinon, on inverse la fonction de repartition associée
        // à la fonction f_k.
        if (y1 == y2) {
            return x1 + U*(x2 - x1);
        } else {
            double m = (y2 - y1)/(x2 - x1);
            return x1 + (sqrt( (y2*y2 - y1*y1) * U + y1*y1 ) - y1) / m;
        }
    }

    ~MixedInverse() {
        delete generator;
    }

private:
    // permet de trouve dans quel intervalle k on tombe en fonction de la probablilité p_k de la tranche liée à
    // cette intervalle
    size_t generateK() const {
        size_t j = 1;
        double U = generator->next();

        // on cherche l'indice de l'intervalle dans lequel on est tombé
        while (true) {
            if (U <= F_parts[j]) {
                return j-1;
            }
            ++j;
        }
    }
};

#endif //LABO1_MIXEDINVERSE_H
