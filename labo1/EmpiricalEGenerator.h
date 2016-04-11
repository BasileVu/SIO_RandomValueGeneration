#ifndef EMPIRICAL_E_GENERATOR
#define EMPIRICAL_E_GENERATOR

#include "RandomValueGenerator.h"

class EmpiricalEGenerator {
    const RandomValueGenerator& generator;

public:
    static double generate(RandomValueGenerator& generator, size_t nGenValues) noexcept(false) {
        if (nGenValues == 0) {
            throw std::invalid_argument("Can't generate empirical expected value with 0 simulations");
        }

        double acc = 0;
        for (size_t i = 0; i < nGenValues; ++i) {
            acc += generator.generate();
        }

        return acc / nGenValues;
    }
};

#endif // EMPIRICAL_E_GENERATOR
