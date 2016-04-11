#ifndef UNIFORM_GENERATOR_H
#define UNIFORM_GENERATOR_H

#include <random>

/**
 * Generates numbers using the uniform distribution.
 */
class UniformGenerator {

private:
    std::mt19937_64 generator;
    std::uniform_real_distribution<double> distribution;

public:
    UniformGenerator(double a, double b) : distribution(std::uniform_real_distribution<double>(a, b)) {}

    void setSeed(std::seed_seq seed) {
        generator.seed(seed);
    }

    double next() {
        return distribution(generator);
    }
};

#endif // UNIFORM_GENERATOR_H
