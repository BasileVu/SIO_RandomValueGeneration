#ifndef LABO1_RANDOM_VALUE_GENERATOR_H
#define LABO1_RANDOM_VALUE_GENERATOR_H

#include <vector>
#include "PointGenerator.h"
#include "Slice.h"

template <typename T>
class RandomValueGenerator {
protected:
    const std::vector<T>& xs;
    const std::vector<T>& ys;
    RealPointGenerator<T>* generator;
    T a, b, yMax = 0;
    std::vector<Slice<T>> slices;

public:
    RandomValueGenerator(const std::vector<T>& xs, const std::vector<T>& ys, const std::seed_seq& seed)
            : xs(xs), ys(ys) {

        /*if (!Checker<T>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        a = xs.front(), b = xs.back();
        slices.reserve(xs.size());

        generator = new RealPointGenerator<T>(a, b, 0, yMax, seed);
    }

    virtual ~RandomValueGenerator() {
        delete generator;
    }

    virtual T generate() const = 0;
};

#endif //LABO1_RANDOM_VALUE_GENERATOR_H
