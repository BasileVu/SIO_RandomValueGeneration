#ifndef MIXEDINVERSE_H
#define MIXEDINVERSE_H

#include <vector>
#include <cmath>

#include "UniformGenerator.h"
#include "RandomValueGenerator.h"

class MixedInverse : public RandomValueGenerator {
private:
    UniformGenerator* generator;

public:

    MixedInverse(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator(xs, ys) {

        generator = new UniformGenerator(0, 1);
        generator->setSeed(seed);
    }

    double generate() const {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();

        // Ensuite, on applique la méthode des fonctions inverses.
        const Piece& piece = func.pieces[K];

        double x0 = piece.p0.x, x1 = piece.p1.x;
        double y0 = piece.p0.y, y1 = piece.p1.y;

        double U = generator->next();

        // Si y1 = y1, alors on est dans le cas d'une uniforme. Sinon, on inverse la fonction de repartition associée
        // à la fonction f_k.
        if (y0 == y1) {
            return x0 + U*(x1 - x0);
        } else {
            double m = (y1 - y0)/(x1 - x0);
            return x0 + (sqrt( (y1*y1 - y0*y0) * U + y0*y0 ) - y0) / m;
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

#endif // MIXEDINVERSE_H
