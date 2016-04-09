#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H

#include <vector>
#include "PointGenerator.h"
#include "Slice.h"

template <typename T>
class RandomValueGenerator {
protected:
    const std::vector<T>& xs;
    const std::vector<T>& ys;
    std::vector<Slice<T>> slices;

public:
    RandomValueGenerator(const std::vector<T>& xs, const std::vector<T>& ys) noexcept(false)
            : xs(xs), ys(ys) {

        /*if (!Checker<T>::check(xs, ys)) {
            throw std::invalid_argument("Incorrect values");
        }*/

        createSlices();
    }

    virtual T generate() const = 0;

private:

    void createSlices() {
        slices.reserve(xs.size());
        for (size_t i = 0; i < xs.size(); ++i) {

            // création de tranches
            if (i < xs.size() - 1) {

                Slice<T> s {{xs[i], ys[i]}, {xs[i+1], ys[i+1]}};
                s.A_k = (double)(ys[i+1] + ys[i]) * (xs[i+1] - xs[i]) / 2;
                s.f_k = [this, i](T x) {
                    T m = (ys[i + 1] - ys[i]) / (xs[i+1] - xs[i]);
                    return m * (x - xs[i]) + ys[i];
                };

                slices.push_back(s);
            }
        }
    }
};

#endif //LABO1_RANDOM_VALUE_GENERATOR_H
