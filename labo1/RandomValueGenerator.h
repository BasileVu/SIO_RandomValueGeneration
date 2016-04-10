#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H

#include <vector>
#include "PointGenerator.h"
#include "PiecewiseFunction.h"

template <typename T>
class RandomValueGenerator {
protected:
    PiecewiseLinearFunction<double> func;
    std::vector<double> F_parts; // parties de la fonction de répartition F

public:
    RandomValueGenerator(const std::vector<T>& xs, const std::vector<T>& ys) noexcept(false)
            : func(xs, ys) {

        /*if (!Checker<T>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        // création des pk
        std::vector<double> pks;
        pks.reserve(xs.size()-1);
        for (size_t i = 0; i < xs.size()-1; ++i) {
            pks.push_back(func.pieces[i].A_k/func.A);
        }

        // préparation des parties de F
        F_parts.resize(xs.size());
        F_parts[0] = 0; // F_0 : premiere partie de la fonction de répartition -> 0 avant xs[0]

        for (size_t i = 1; i < F_parts.size(); ++i) {
            F_parts[i] = F_parts[i-1] + pks[i-1];
        }
    }

    virtual T generate() const = 0;
};

#endif // RANDOM_VALUE_GENERATOR_H
