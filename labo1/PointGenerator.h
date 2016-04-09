#ifndef LABO1_POINTGENERATOR_H
#define LABO1_POINTGENERATOR_H

#include "Point.h"
#include "UniformGenerator.h"

template <typename RealType>
class RealPointGenerator {
private:
    UniformRealGenerator<RealType> generator;
public:

    RealPointGenerator(const std::seed_seq& seed)
            : generator(UniformRealGenerator<RealType>(0, 1)) {

        generator.setSeed(seed);
    }

    Point<RealType> generate(RealType xMin, RealType xMax, RealType yMin, RealType yMax) {
        return {generator.next() * (xMax - xMin) + xMin, generator.next() * (yMax - yMin) + yMin};
    }
};

#endif //LABO1_POINTGENERATOR_H
