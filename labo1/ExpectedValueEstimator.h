#ifndef EXPECTED_VALUE_ESTIMATOR
#define EXPECTED_VALUE_ESTIMATOR

#include "RandomValueGenerator.h"

template <typename T, typename ResultType>
class ExpectedValueEstimator {
    const RandomValueGenerator<T>& generator;

public:
    ExpectedValueEstimator(const RandomValueGenerator<T>& generator) : generator(generator) {}

    ResultType generate(size_t numSimulations) const noexcept(false) {
        if (numSimulations == 0) {
            throw std::invalid_argument("Can't estimate expected value with 0 value");
        }

        ResultType acc = 0;
        for (size_t i = 0; i < numSimulations; ++i) {
            acc += generator.generate();
        }

        return acc / numSimulations;
    }
};

#endif // EXPECTED_VALUE_ESTIMATOR
