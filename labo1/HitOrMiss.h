#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "RandomValueGenerator.h"
#include "UniformGenerator.h"
#include "PointGenerator.h"
#include "Checker.h"
#include "Part.h"

/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
template <typename RealType>
class HitOrMiss : public RandomValueGenerator<RealType> {
public:

    HitOrMiss(const std::vector<RealType>& xs, const std::vector<RealType>& ys, const std::seed_seq& seed) noexcept(false)
            : RandomValueGenerator<RealType>(xs, ys, seed) {

        std::cout << "a: " << this->a << ", b: " << this->b << ", yMax : " << this->yMax << std::endl;
        std::cout << "nSlices: " << this->slices.size() << " : ";
        for (Part<RealType>& s: this->slices) {
            std::cout << "(" << s.x1 << ", " << s.x2 << ") ";
        }
        std::cout << std::endl;
    }

    RealType generate() {

        Point<RealType> p;  // point (X,Y) qui sera généré aléatoirement
        size_t sliceIndex;  // indice de la "tranche" dans laquelle X se trouvera"

        do {
            // génération du point (X,Y)
            p = this->generator->next();

            // on cherche le morceau de dans laquelle X se trouve
            sliceIndex = findPart(p.x);

            //std::cout << "X = " << p.x << ", Y = " << p.y << ", sliceIndex = " << sliceIndex << ", f(X) = " << slices[sliceIndex].f(p.x) << std::endl;

            // rejet si Y est > que f(X), avec f la fonction affine associée à la tranche
        } while (p.y > this->slices[sliceIndex].f(p.x));

        return p.x;
    }

private:

    /**
     * \brief Recherche dichotomique afin de trouver dans quelle intervalle x se trouve.
     * \param x l'abscisse dont on veut connaître l'intervalle.
     * \return l'indice du morceau dans lequel x se trouve.
     */
    size_t findPart(RealType x) {

        size_t first = 0, last = this->slices.size() - 1; // indices des tranches à prendre en compte

        while (true) {

            // il ne reste qu'une tranche -> x est dedans
            if (first == last) {
                return first;
            }

            // on regarde si x est dans la première ou deuxième moitié de l'intervalle de recherche
            size_t mid = (last-first)/2 + first;
            if (x < this->slices[mid].x2) {   // première moitié
                last = mid;
            } else {                    // deuxième moitié
                first = mid+1;
            }
        }
    }

    
};

#endif // HITORMISS_H
