#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "RandomValueGenerator.h"
#include "PointGenerator.h"
#include "Checker.h"
#include "Slice.h"

/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
class HitOrMiss : public RandomValueGenerator<double> {
private:
    RealPointGenerator<double>* pointGenerator;
    double a, b, yMax = 0;
public:

    HitOrMiss(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed) noexcept(false)
            : RandomValueGenerator<double>(xs, ys) {

        a = xs.front(), b = xs.back();
        yMax = *std::max_element(ys.begin(), ys.end());

        pointGenerator = new RealPointGenerator<double>(seed);
    }

    double generate() const {

        Point<double> p;  // point (X,Y) qui sera généré aléatoirement
        size_t sliceIndex;  // indice de la "tranche" dans laquelle X se trouvera"

        do {
            // génération du point (X,Y)
            p = pointGenerator->next(a, b, 0, yMax);

            // on cherche le morceau de dans laquelle X se trouve
            sliceIndex = findPart(p.x);

            // rejet si Y est > que f(X), avec f_k la fonction affine associée à la tranche k
        } while (p.y > slices[sliceIndex].f_k(p.x));

        return p.x;
    }

    ~HitOrMiss() {
        delete pointGenerator;
    }

private:

    /**
     * \brief Recherche dichotomique afin de trouver dans quelle intervalle x se trouve.
     * \param x l'abscisse dont on veut connaître l'intervalle.
     * \return l'indice du morceau dans lequel x se trouve.
     */
    size_t findPart(double x) const {

        size_t first = 0, last = slices.size() - 1; // indices des tranches à prendre en compte

        while (true) {

            // il ne reste qu'une tranche -> x est dedans
            if (first == last) {
                return first;
            }

            // on regarde si x est dans la première ou deuxième moitié de l'intervalle de recherche
            size_t mid = (last-first)/2 + first;
            if (x < slices[mid].x2) {   // première moitié
                last = mid;
            } else {                    // deuxième moitié
                first = mid+1;
            }
        }
    }

    
};

#endif // HITORMISS_H
