#ifndef POINTGENERATOR_H
#define POINTGENERATOR_H

#include "Point.h"
#include "UniformGenerator.h"

class PointGenerator {
private:
    UniformGenerator generator;
public:

    PointGenerator(const std::seed_seq& seed)
            : generator(UniformGenerator(0, 1)) {

        generator.setSeed(seed);
    }

    Point generate(double xMin, double xMax, double yMin, double yMax) {
        return {generator.next() * (xMax - xMin) + xMin, generator.next() * (yMax - yMin) + yMin};
    }
};

#endif // POINTGENERATOR_H
