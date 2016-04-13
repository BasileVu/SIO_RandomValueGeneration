#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "RandomValueGenerator.h"

/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
class HitOrMiss : public RandomValueGenerator {
private:
    double a, b, yMax = 0;

public:

    HitOrMiss(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator(xs, ys) {

        a = xs.front(), b = xs.back();
        yMax = *std::max_element(ys.begin(), ys.end());
    }

    double generate() {

        double X, Y;
        size_t sliceIndex;  // indice de la "tranche" dans laquelle X se trouvera"

        do {
            // génération du point (X,Y)
            X = generator.next() * (b - a) + a;
            Y = generator.next() * yMax;

            // on cherche le morceau lié à l'intervalle dans laquelle X se trouve
            sliceIndex = func.findPart(X);

            // rejet si Y est > que f(X), avec f_k la fonction affine associée à la tranche k
        } while (Y > func.pieces[sliceIndex].f_k(X));

        return X;
    }
};

#endif // HITORMISS_H
