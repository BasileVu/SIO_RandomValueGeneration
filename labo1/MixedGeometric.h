#ifndef MIXEDGEOMETRIC_H
#define MIXEDGEOMETRIC_H

#include "PointGenerator.h"
#include "UniformGenerator.h"

/**
 *
 */
class MixedGeometric : public RandomValueGenerator<double> {
private:
    UniformRealGenerator<double>* generator;
    RealPointGenerator<double>* pointGenerator;

public:

    MixedGeometric(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator<double>(xs, ys) {

        generator = new UniformRealGenerator<double>(0, 1);
        generator->setSeed(seed);

        pointGenerator = new RealPointGenerator<double>(seed);
    }

    double generate() const {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();


        // Ensuite, on génère une réalisation d'une variable de densité f_K en acceptant à tous les coups X.
        Piece<double> s = pieces[K];

        Point<double> p = pointGenerator->generate(s.p0.x, s.p1.x, 0, std::max(s.p0.y, s.p1.y));

        // Si Y est sous f_k, ok, on retourne X. Sinon, on applique une symétrie à X et on le retourne.
        if (p.y <= s.f_k(p.x)) {
            return p.x;
        } else {
            return (s.p0.x + (s.p1.x - p.x));
        }
    }

    ~MixedGeometric() {
        delete generator;
        delete pointGenerator;
    }

private:
    // permet de trouve dans quel intervalle k on tombe en fonction de la probablilité p_k de la tranche liée à
    // cette intervalle
    size_t generateK() const {
        size_t j = 1;
        double U = generator->next();

        // on cherche l'indice de l'intervalle dans lequel on est tombé
        while (true) {
            if (U <= F_parts[j]) {
                return j-1;
            }
            ++j;
        }
    }
};

#endif // MIXEDGEOMETRIC_H
