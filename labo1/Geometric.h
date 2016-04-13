#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include "UniformGenerator.h"

/**
 *
 */
class Geometric : public RandomValueGenerator {
public:
    Geometric(const std::vector<double>& xs, const std::vector<double>& ys) : RandomValueGenerator(xs, ys) {}

    double generate() {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();


        // Ensuite, on génère une réalisation d'une variable de densité f_K en acceptant à tous les coups X.
        const Piece& piece = func.pieces[K];

        double x0 = piece.x0, x1 = piece.x1;
        double yMax = std::max(piece.y0, piece.y1);

        double X = generator.next() * (x1 - x0) + x0;
        double Y = generator.next() * yMax;

        // Si Y est sous f_k, ok, on retourne X. Sinon, on applique une symétrie à X et on le retourne.
        if (Y <= piece.f_k(X)) {
            return X;
        } else {
            return x0 + (x1 - X);
        }
    }

private:
    // permet de trouve dans quel intervalle k on tombe en fonction de la probablilité p_k de la tranche liée à
    // cette intervalle
    size_t generateK() {
        size_t j = 1;
        double U = generator.next();

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
