#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "RandomValueGenerator.h"
#include "PointGenerator.h"

/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
class HitOrMiss : public RandomValueGenerator {
private:
    PointGenerator* pointGenerator;
    double a, b, yMax = 0;
public:

    HitOrMiss(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator(xs, ys) {

        a = xs.front(), b = xs.back();
        yMax = *std::max_element(ys.begin(), ys.end());
        pointGenerator = new PointGenerator(seed);
    }

    double generate() const {

        Point p;  // point (X,Y) qui sera généré aléatoirement
        size_t sliceIndex;  // indice de la "tranche" dans laquelle X se trouvera"

        do {
            // génération du point (X,Y)
            p = pointGenerator->generate(a, b, 0, yMax);

            // on cherche le morceau lié à l'intervalle dans laquelle X se trouve
            sliceIndex = func.findPart(p.x);

            // rejet si Y est > que f(X), avec f_k la fonction affine associée à la tranche k
        } while (p.y > func.pieces[sliceIndex].f_k(p.x));

        return p.x;
    }

    ~HitOrMiss() {
        delete pointGenerator;
    }
};

#endif // HITORMISS_H
