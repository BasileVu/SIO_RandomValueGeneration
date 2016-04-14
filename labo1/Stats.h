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
     * \brief Cree la representation sous forme de chaine de caracteres de l'intervalle de confiance.
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
     * \return Les realisations de V.A.
     */
    static std::vector<double> generateNValues(RandomValueGenerator& generator, size_t nValues);

    /**
     * \brief Calcule la variance empirique d'un ensemble de donnees.
     * \param values Les donnes a utiliser.
     * \return La variance empirique.
     */
    static double sampleVar(const std::vector<double>& values);

    /**
     * \brief Calcule l'ecart-type empirique d'un ensemble de donnees.
     * \param values Les valeurs a utiliser.
     * \return L'ecart-type empirique.
     */
    static double sampleStdDev(const std::vector<double>& values);

    /**
     * \brief Calcule l'esperance d'une fonction affine par morceaux.
     * \param xs Les d'abscisses des points constituant la fonction affine par morceaux.
     * \param ys Les ordonnees des points constituant la fonction affine par morceaux.
     * \return L'esperance.
     */
    static double expectedValue(const std::vector<double>& xs, const std::vector<double>& ys);

    /**
     * \brief Calcule la moyenne d'un ensemble de donnees.
     * \param values Les valeurs a utiliser.
     * \return La moyenne.
     */
    static double mean(const std::vector<double>& values);

    /**
     * \brief Calcule l'intervalle de confiance d'un ensemble de donnees.
     * \param values Les valeurs a utiliser.
     * \param quantile Le coefficient associe au quantile de l'IC.
     * \return L'intervalle de confiance.
     */
    static ConfidenceInterval confidenceInterval(const std::vector<double>& values, double quantile);
};

#endif // STATS_H
