#ifndef BENCHMARKER_H
#define BENCHMARKER_H

#include <ctime>
#include <string>
#include <iostream>

#include "PiecewiseFunction.h"
#include "EmpiricalEGenerator.h"
#include "TheoricalECalculator.h"
#include "RandomValueGenerator.h"

class Benchmarker {
private:
    const EmpiricalEGenerator<double> eve;

public:
    Benchmarker(const RandomValueGenerator<double>& generator)
            : eve(EmpiricalEGenerator<double>(generator)) {}

    void run(const std::string& name, size_t nSim) const noexcept(false) {
        clock_t start = clock();
        double empiricalEVal = eve.generate(nSim);
        double timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

        std::cout << name << ": " << empiricalEVal << ", " << timeElapsed << "s" << std::endl;
    }
};

#endif // BENCHMARKER_H
