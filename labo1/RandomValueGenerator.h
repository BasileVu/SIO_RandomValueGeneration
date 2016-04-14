#ifndef RANDOM_VALUE_GENERATOR_H
#define RANDOM_VALUE_GENERATOR_H

#include <vector>
#include <algorithm>
#include "UniformGenerator.h"
#include "PiecewiseLinearFunction.h"

/**
 *
 */
class RandomValueGenerator {
protected:
    PiecewiseLinearFunction func;
    UniformGenerator generator;
    std::vector<double> F_parts; // parties de la fonction de répartition F

public:
    RandomValueGenerator(const std::vector<double>& xs, const std::vector<double>& ys);

    void setSeed(const std::seed_seq& seed);

    virtual double generate() = 0;

protected:

    // permet de trouve dans quel intervalle k on tombe en fonction de la probablilité p_k de la tranche liée à
    // cette intervalle
    size_t generateK();
};


/**
 * Classe utilisant une methode bete et mechante d'acceptation-rejet afin de générer des
 * réalisations de variable aléatoires.
 */
class HitOrMiss : public RandomValueGenerator {
private:
    double a, b, yMax = 0;

public:

    HitOrMiss(const std::vector<double>& xs, const std::vector<double>& ys);

    double generate();
};


class Geometric : public RandomValueGenerator {
public:
    Geometric(const std::vector<double>& xs, const std::vector<double>& ys);

    double generate();
};


class InverseFunctions : public RandomValueGenerator {
public:
    InverseFunctions(const std::vector<double>& xs, const std::vector<double>& ys);

    double generate();
};

#endif // RANDOM_VALUE_GENERATOR_H
