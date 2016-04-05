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
    UniformRealGenerator<RealType> generator;
    RealType xMin, xMax;
    RealType yMin, yMax;
public:

    RealPointGenerator(RealType xMin, RealType xMax, RealType yMin, RealType yMax, const std::seed_seq& seed)
            : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), generator(UniformRealGenerator<RealType>(0, 1)) {

        generator.setSeed(seed);
    }

    Point<RealType> next() {
        return {generator.next() * (xMax - xMin), generator.next() * (yMax - yMin)};
    }
};

#endif //LABO1_POINTGENERATOR_H
