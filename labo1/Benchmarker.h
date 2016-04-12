#ifndef BENCHMARKER_H
#define BENCHMARKER_H

#include <ctime>
#include <iostream>

#include "PiecewiseFunction.h"
#include "Stats.h"
#include "RandomValueGenerator.h"

class Benchmarker {
public:
    static double run(RandomValueGenerator& generator, size_t nGenValues) {
        clock_t start = clock();
        Stats::mean(Stats::generateNValues(generator, nGenValues));
        return (double)(clock() - start) / CLOCKS_PER_SEC;
    }
};

#endif // BENCHMARKER_H
