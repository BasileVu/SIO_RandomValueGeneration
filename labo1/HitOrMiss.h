#ifndef HITORMISS_H
#define HITORMISS_H

#include <cstdint>
#include "Generator.h"

template <typename RealType>
class HitOrMiss {
private:
    UniformRealGenerator& generator;

public:
    HitOrMiss(UniformRealGenerator& generator) : generator(generator) {}

    RealType generate(RealType x1, RealType x2) {
        RealType Y = 1/(x2 - x1);
        RealType U = generator.next();

    }
};

#endif // HITORMISS_H
