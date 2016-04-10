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
    double theoricalEval = 0;
    const EmpiricalEGenerator<double> eve;

public:
    Benchmarker(const RandomValueGenerator<double>& generator, const std::vector<double>& xs, const std::vector<double>& ys)
            : eve(EmpiricalEGenerator<double>(generator)) {

        //theoricalEval = TheoricalECalculator<double>::calculate(PiecewiseLinearFunction<double>(xs, ys));
    }

    void run(const std::string& name, size_t nSim) const noexcept(false) {
        clock_t start = clock();
        double empiricalEVal = eve.generate(nSim);
        double timeElapsed = (double)(clock() - start) / CLOCKS_PER_SEC;

        std::cout << name << ": " << theoricalEval << ", " << empiricalEVal << ", " << timeElapsed << "s" << std::endl;
    }
};

#endif // BENCHMARKER_H
