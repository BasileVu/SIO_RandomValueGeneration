#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>

/**
 * Generates numbers using the uniform distribution.
 */
template <typename RealType>
class UniformRealGenerator {

private:
    std::mt19937_64 generator;
    std::uniform_real_distribution<RealType> distribution;

public:
    UniformRealGenerator(RealType a, RealType b)
            : distribution(std::uniform_real_distribution<RealType>(a, b)) {}

    void setSeed(std::seed_seq seed) {
        generator.seed(seed);
    }

    RealType next() {
        return distribution(generator);
    }
};

#endif // GENERATOR_H
