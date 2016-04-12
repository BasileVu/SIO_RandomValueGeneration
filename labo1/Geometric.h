#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "PointGenerator.h"
#include "UniformGenerator.h"

/**
 *
 */
class Geometric : public RandomValueGenerator {
private:
    UniformGenerator* generator;
    PointGenerator* pointGenerator;

public:

    Geometric(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator(xs, ys) {

        generator = new UniformGenerator(0, 1);
        generator->setSeed(seed);

        pointGenerator = new PointGenerator(seed);
    }

    double generate() const {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();


        // Ensuite, on génère une réalisation d'une variable de densité f_K en acceptant à tous les coups X.
        const Piece& piece = func.pieces[K];

        Point p = pointGenerator->generate(piece.p0.x, piece.p1.x, 0, std::max(piece.p0.y, piece.p1.y));

        // Si Y est sous f_k, ok, on retourne X. Sinon, on applique une symétrie à X et on le retourne.
        if (p.y <= piece.f_k(p.x)) {
            return p.x;
        } else {
            return (piece.p0.x + (piece.p1.x - p.x));
        }
    }

    ~Geometric() {
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

#endif // GEOMETRIC_H
