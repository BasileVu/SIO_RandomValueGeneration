#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H

#include <vector>
#include "Checker.h"
#include "PointGenerator.h"
#include "PiecewiseLinearFunction.h"

class RandomValueGenerator {
protected:
    PiecewiseLinearFunction func;
    std::vector<double> F_parts; // parties de la fonction de répartition F

public:
    RandomValueGenerator(const std::vector<double>& xs, const std::vector<double>& ys) noexcept(false)
            : func(xs, ys) {

        // verification de la validité des données
        if (!Checker::check(xs, ys)) {
            throw std::invalid_argument("Les donnees ne sont pas valides.");
        }

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

    virtual double generate() const = 0;
};

#endif // RANDOM_VALUE_GENERATOR_H
