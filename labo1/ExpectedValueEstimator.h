#ifndef EMPIRICAL_E_GENERATOR
#define EMPIRICAL_E_GENERATOR

#include "RandomValueGenerator.h"

template <typename T, typename ResultType>
class EmpiricalEGenerator {
    const RandomValueGenerator<T>& generator;

public:
    EmpiricalEGenerator(const RandomValueGenerator<T>& generator) : generator(generator) {}

    ResultType generate(size_t nSim) const noexcept(false) {
        if (nSim == 0) {
            throw std::invalid_argument("Can't estimate expected value with 0 value");
        }

        ResultType acc = 0;
        for (size_t i = 0; i < nSim; ++i) {
            acc += generator.generate();
        }

        return acc / nSim;
    }
};

#endif // EMPIRICAL_E_GENERATOR
