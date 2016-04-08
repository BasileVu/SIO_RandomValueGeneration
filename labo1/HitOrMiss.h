#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include <iostream>
#include <algorithm>

#include "UniformGenerator.h"
#include "PointGenerator.h"
#include "Checker.h"
#include "Slice.h"

/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
template <typename RealType>
class HitOrMiss {
private:
    const std::vector<RealType>& xs, ys;
    RealType a, b, yMax = 0;
    RealPointGenerator<RealType>* generator;

    std::vector<Slice<RealType>> slices;

public:

    HitOrMiss(const std::vector<RealType>& xs, const std::vector<RealType>& ys, const std::seed_seq& seed) throw(std::invalid_argument)
            : xs(xs), ys(ys) {

        /*if (!Checker<RealType>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        a = xs.front(), b = xs.back();
        slices.reserve(xs.size());

        for (size_t i = 0; i < xs.size(); ++i) {

            if (yMax < ys[i]) {
                yMax = ys[i];
            }

            // création de tranches
            if (i < xs.size() - 1) {
                slices.push_back({xs[i], xs[i+1], [&xs, &ys, i](RealType x) {
                    RealType m = (ys[i+1] - ys[i]) / (xs[i+1], xs[i]);
                    return m * (x - xs[i]) + ys[i];
                }});
            }
        }

        generator = new RealPointGenerator<RealType>(a, b, 0, yMax, seed);

        std::cout << "a: " << a << ", b: " << b << ", yMax : " << yMax << std::endl;
        std::cout << "nSlices: " << slices.size() << std::endl;

        for (int i = 0; i < 10; ++i) {
            Point<double> p = generator->next();
            std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
        }
    }

    ~HitOrMiss() {
        delete generator;
    }

    RealType generate() {

        Point<RealType> p;  // point (X,Y) qui sera généré aléatoirement
        size_t sliceIndex;  // indice de la "tranche" dans laquelle X se trouvera"

        do {
            // génération du point (X,Y)
            p = generator->next();

            // on cherche la "tranche" (l'intervalle) dans laquelle X se trouve
            sliceIndex = findSlice(p.x);

            //std::cout << "X = " << p.x << ", " << "Y = " << p.y << ", " << "f(X) = " << slices[sliceIndex].f(p.x) << std::endl;

            // rejet si Y est > que f(X), avec f la fonction affine associée à la tranche
        } while (p.y > slices[sliceIndex].f(p.x));

        return p.x;
    }

private:
    size_t findSlice(RealType x) {

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
