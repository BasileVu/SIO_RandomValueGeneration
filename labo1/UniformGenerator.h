#ifndef UNIFORM_GENERATOR_H
#define UNIFORM_GENERATOR_H

#include <random>

/**
 * Permet de generer des nombres entre deux bornes de maniere plus legere qu'en utilisant directement la
 * distribution uniforme "uniform_real_distribution" de la librairie standard.
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
