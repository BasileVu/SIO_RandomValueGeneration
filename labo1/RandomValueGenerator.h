#ifndef LABO1_RANDOM_VALUE_GENERATOR_H
#define LABO1_RANDOM_VALUE_GENERATOR_H

#include <vector>
#include "PointGenerator.h"
#include "Part.h"

template <typename T>
class RandomValueGenerator {
protected:
    const std::vector<T>& xs, ys;
    RealPointGenerator<T>* generator;
    T a, b, yMax = 0;
    std::vector<Part<T>> slices;

public:
    RandomValueGenerator(const std::vector<T>& xs, const std::vector<T>& ys, const std::seed_seq& seed)
            : xs(xs), ys(ys) {

        /*if (!Checker<T>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        a = xs.front(), b = xs.back();
        slices.reserve(xs.size());

        for (size_t i = 0; i < xs.size(); ++i) {

            if (yMax < ys[i]) {
                yMax = ys[i];
            }

            // création de tranches
            if (i < xs.size() - 1) {
                slices.push_back({xs[i], xs[i+1], [&xs, &ys, i](T x) {
                    T m = (ys[i+1] - ys[i]) / (xs[i+1] - xs[i]);
                    return m * (x - xs[i]) + ys[i];
                }});
            }
        }

        generator = new RealPointGenerator<T>(a, b, 0, yMax, seed);
    }

    virtual ~RandomValueGenerator() {
        delete generator;
    }

    virtual T generate() = 0;
};

#endif //LABO1_RANDOM_VALUE_GENERATOR_H
