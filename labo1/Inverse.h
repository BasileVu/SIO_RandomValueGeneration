#ifndef INVERSE_FUNCTIONS_H
#define INVERSE_FUNCTIONS_H

#include <vector>
#include <cmath>

#include "UniformGenerator.h"
#include "RandomValueGenerator.h"

class InverseFunctions : public RandomValueGenerator {
public:
    InverseFunctions(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed)
            : RandomValueGenerator(xs, ys) {}

    double generate() {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();

        // Ensuite, on applique la méthode des fonctions inverses.
        const Piece& piece = func.pieces[K];

        double x0 = piece.x0, x1 = piece.x1;
        double y0 = piece.y0, y1 = piece.y1;

        double U = generator.next();

        // Si y1 = y1, alors on est dans le cas d'une uniforme. Sinon, on inverse la fonction de repartition associée
        // à la fonction f_k.
        if (y0 == y1) {
            return x0 + U*(x1 - x0);
        } else {
            double m = (y1 - y0)/(x1 - x0);
            return x0 + (sqrt( (y1*y1 - y0*y0) * U + y0*y0 ) - y0) / m;
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

#endif // INVERSE_FUNCTIONS_H
