#ifndef STATS_H
#define STATS_H

#include <vector>
#include <string>
#include <sstream>

#include "PiecewiseLinearFunction.h"
#include "RandomValueGenerator.h"

/**
 * Represente une intervalle de confiance.
 */
struct ConfidenceInterval {
    double lower; // borne inferieure
    double upper; // borne superieure
    double delta; // difference entre les deux bornes

    /**
     * \brief Cree la representation sous forme de string de l'intervalle de confiance.
     */
    std::string toString() const {
        std::stringstream ss;
        ss << "[" << lower << "," << upper << "]";
        return ss.str();
    }
};

/**
 * Regroupe differentes fonctions relatives aux statistiques.
 */
class Stats {
public:

    /**
     * \brief Genere nValues realisations de variables aleatoires en utilisant un generateur.
     * \param generator Le generateur a utiliser afin de generer des ralisations de V.A.
     * \param nValues le nombre de realisations à generer.
     * \return Un vector de double contenant les realisations de V.A.
     */
    static std::vector<double> generateNValues(RandomValueGenerator& generator, size_t nValues) {
        std::vector<double> values;
        values.reserve(nValues);

        for (size_t i = 0; i < nValues; ++i) {
            values.push_back(generator.generate());
        }

        return values;
    }

    /**
     * \brief
     */
    static double sampleVar(const std::vector<double>& values) {
        double sum = 0;
        double m = mean(values);

        for (const double& d : values) {
            double item = d - m;
            sum += item * item;
        }
        return sum / (values.size() - 1);
    }

    static double sampleStdDev(const std::vector<double>& values) {
        return std::sqrt(sampleVar(values));
    }

    static double expectedValue(const std::vector<double>& xs, const std::vector<double>& ys) {
        PiecewiseLinearFunction func(xs, ys);
        double res = 0;
        for (const Piece& p : func.pieces) {
            double x0 = p.x0, x1 = p.x1;
            double y0 = p.y0, y1 = p.y1;

            if (y0 + y1 > 0) {
                double eVal = (y0 * (2 * x0 + x1) + y1 * (x0 + 2 * x1)) / (3 * (y0 + y1));
                res += eVal * p.A_k;
            }
        }
        return res / func.A;
    }

    static double mean(const std::vector<double>& values) {
        return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
    }

    static ConfidenceInterval confidenceInterval(const std::vector<double>& values, double quantile) {
        double m = mean(values);
        double halfDelta = quantile * (sampleStdDev(values) / std::sqrt(values.size()));
        return ConfidenceInterval {m - halfDelta, m + halfDelta, halfDelta*2};
    };
};

#endif // STATS_H
