#ifndef STATS_H
#define STATS_H

#include <vector>
#include <string>

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
    std::string toString() const;
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
    static std::vector<double> generateNValues(RandomValueGenerator& generator, size_t nValues);

    /**
     * \brief
     */
    static double sampleVar(const std::vector<double>& values);

    static double sampleStdDev(const std::vector<double>& values);

    static double expectedValue(const std::vector<double>& xs, const std::vector<double>& ys);

    static double mean(const std::vector<double>& values);

    static ConfidenceInterval confidenceInterval(const std::vector<double>& values, double quantile);
};

#endif // STATS_H
