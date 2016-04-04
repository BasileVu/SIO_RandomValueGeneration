#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <functional>

#include "Generator.h"
#include "PointGenerator.h"
#include "Checker.h"

/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
template <typename RealType>
class HitOrMiss {
private:

    // Func : fonction qui prend un RealType et renvoie un RealType
    typedef std::function<RealType(RealType)> Func;

    const std::vector<RealType>& xs, ys;
    RealType a, b, yMax = 0;
    RealPointGenerator<RealType>* generator;

    std::vector<Func> fParts;

public:

    HitOrMiss(const std::vector<RealType>& xs, const std::vector<RealType>& ys, const std::seed_seq& seed) throw(std::invalid_argument)
            : xs(xs), ys(ys) {

        /*if (!Checker<RealType>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        a = xs.front(), b = xs.back();
        fParts.reserve(xs.size());

        for (size_t i = 0; i < xs.size(); ++i) {

            if (yMax < ys[i]) {
                yMax = ys[i];
            }

            if (i < xs.size() - 1) {
                Func f = [](RealType x) { return x; };
                fParts.push_back(f);
            }
        }

        generator = new RealPointGenerator<RealType>(a, b, 0, yMax);
        std::cout << "yMax :" << yMax << std::endl;
    }

    ~HitOrMiss() {
        delete generator;
    }

    RealType generate() {

        size_t sliceIndex = 0; // TODO: find slice

        Point<RealType> p;

        do {
            p = generator->next();

            std::cout << p.x << ", " << p.y << std::endl;
        } while (p.y > fParts[sliceIndex](p.x));

        return p.x;
    }
};

#endif // HITORMISS_H
