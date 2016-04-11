#ifndef LABO1_POINTGENERATOR_H
#define LABO1_POINTGENERATOR_H

#include "Point.h"
#include "UniformGenerator.h"

class PointGenerator {
private:
    UniformRealGenerator<double> generator;
public:

    PointGenerator(const std::seed_seq& seed)
            : generator(UniformRealGenerator<double>(0, 1)) {

        generator.setSeed(seed);
    }

    Point generate(double xMin, double xMax, double yMin, double yMax) {
        return {generator.next() * (xMax - xMin) + xMin, generator.next() * (yMax - yMin) + yMin};
    }
};

#endif //LABO1_POINTGENERATOR_H
