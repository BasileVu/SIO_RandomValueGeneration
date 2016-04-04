#ifndef LABO1_POINTGENERATOR_H
#define LABO1_POINTGENERATOR_H

#include "Generator.h"

template <typename T>
struct Point {
    T x, y;
};

template <typename RealType>
class RealPointGenerator {
private:
    UniformRealGenerator<RealType> xGen, yGen;
public:

    RealPointGenerator(RealType xMin, RealType xMax, RealType yMin, RealType yMax)
            : xGen(UniformRealGenerator<RealType>(xMin, xMax)), yGen(UniformRealGenerator<RealType>(yMin, yMax)) {}

    void setSeed(const std::seed_seq& seed) {
        xGen.setSeed(seed);
        yGen.setSeed(seed);
    }

    Point<RealType> next() {
        return {xGen.next(), yGen.next()};
    }
};

#endif //LABO1_POINTGENERATOR_H
