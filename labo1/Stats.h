#ifndef STATS_H
#define STATS_H

#include <vector>

#include "PiecewiseFunction.h"
#include "RandomValueGenerator.h"

class Stats {
public:

    static std::vector<double> generateNValues(RandomValueGenerator& generator, size_t nValues) {
        if (nValues < 0) {
            throw std::invalid_argument("Cannot generate a negative number of values");
        }

        std::vector<double> values;
        values.reserve(nValues);

        for (size_t i = 0; i < nValues; ++i) {
            values.push_back(generator.generate());
        }

        return values;
    }

    static double mean(const std::vector<double>& values) {
        double sum = std::accumulate(values.begin(), values.end(), 0.0);
        return sum / values.size();
    }

    static double var(const std::vector<double>& values) {
        // V(X) = ((somme de i = 1 à n (x_i ^ 2)) / n) - moyenne^2

        double var = 0;
        double mean = 0;
        for (const double& d : values) {
            var += d*d;
            mean += d;
        }
        mean /= values.size();
        var /= values.size();
        return var - mean*mean;
    }

    static double stdDev(const std::vector<double>& values) {
        return std::sqrt(var(values));
    }

    static double theoricalEVal(const std::vector<double>& xs, const std::vector<double>& ys) {
        PiecewiseLinearFunction func(xs, ys);
        double res = 0;
        for (const Piece& p : func.pieces) {
            double x0 = p.p0.x, x1 = p.p1.x;
            double y0 = p.p0.y, y1 = p.p1.y;

            if (y0 + y1 > 0) {
                double eVal = (y0 * (2 * x0 + x1) + y1 * (x0 + 2 * x1)) / (3 * (y0 + y1));
                res += eVal * p.A_k;
            }
        }
        return res / func.A;
    }

    static double empiricalEVal(RandomValueGenerator& generator, size_t nValues) {
        return mean(generateNValues(generator, nValues));
    }
};

#endif // STATS_H
