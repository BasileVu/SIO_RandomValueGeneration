#ifndef PERSO2_PRNG_H
#define PERSO2_PRNG_H

#include <random>

/**
 * Generates numbers using the uniform distribution.
 */
template <typename UIntType>
class UniformGenerator {

private:
    std::mt19937_64 generator;
    std::uniform_int_distribution<UIntType> distribution;

public:
    UniformGenerator(UIntType a, UIntType b, std::seed_seq seed)
            : distribution(std::uniform_int_distribution<UIntType>(a, b)), generator(std::mt19937_64(seed)) {}

    UIntType next() {
        return distribution(generator);
    }
};

#endif //PERSO2_PRNG_H
