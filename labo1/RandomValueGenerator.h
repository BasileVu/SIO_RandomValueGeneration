#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H

#include <vector>
#include "PointGenerator.h"
#include "PiecewiseFunction.h"

template <typename T>
class RandomValueGenerator {
protected:
    const std::vector<T>& xs;
    const std::vector<T>& ys;
    PiecewiseLinearFunction<double> func;
    std::vector<Piece<T>> pieces;
    double A = 0; // aire totale
    std::vector<double> F_parts; // parties de la fonction de répartition F

public:
    RandomValueGenerator(const std::vector<T>& xs, const std::vector<T>& ys) noexcept(false)
            : xs(xs), ys(ys), func(xs, ys) {

        /*if (!Checker<T>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        pieces.reserve(xs.size());
        for (size_t i = 0; i < xs.size(); ++i) {

            if (i < xs.size() - 1) {

                Piece<T> s {{xs[i], ys[i]}, {xs[i+1], ys[i+1]}};
                s.A_k = (double)(ys[i+1] + ys[i]) * (xs[i+1] - xs[i]) / 2;
                s.f_k = [&xs, &ys, i](T x) {
                    T m = (ys[i + 1] - ys[i]) / (xs[i+1] - xs[i]);
                    return m * (x - xs[i]) + ys[i];
                };

                pieces.push_back(s);
                A += s.A_k;
            }
        }

        // création des pk
        std::vector<double> pks;
        pks.reserve(xs.size()-1);
        for (size_t i = 0; i < xs.size()-1; ++i) {
            pks.push_back(pieces[i].A_k/A);
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
