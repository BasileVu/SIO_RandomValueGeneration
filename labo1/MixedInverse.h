#ifndef LABO1_MIXEDINVERSE_H
#define LABO1_MIXEDINVERSE_H

#include <vector>
#include <cmath>

#include "UniformGenerator.h"
#include "Slice.h"

class MixedInverse {
private:
    const std::vector<double>& xs;
    const std::vector<double>& ys;
    const std::seed_seq& seed;

    UniformRealGenerator<double>* generator;
    std::vector<Slice<double>> slices;

    std::vector<double> F_parts; // "bouts" de la fonction de répartition; F_parts[i] = F_parts[i-1] + pks[i]
public:

    MixedInverse(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed) noexcept(false)
            : xs(xs), ys(ys), seed(seed) {

        generator = new UniformRealGenerator<double>(0, 1);
        generator->setSeed(seed);

        // création de tranches
        double A = 0; // aire totale
        slices.reserve(xs.size());
        for (size_t i = 0; i < xs.size(); ++i) {

            if (i < xs.size() - 1) {

                Slice<double> s;
                s.x1 = xs[i];
                s.x2 = xs[i+1];
                s.A_k = (double)(ys[i+1] + ys[i]) * (xs[i+1] - xs[i]) / 2;
                s.f_k = [&xs, &ys, i, &s](double x) {
                    double m = (ys[i + 1] - ys[i]) / (xs[i+1] - xs[i]);
                    return (m * (x - xs[i]) + ys[i]) / s.A_k;
                };

                slices.push_back(s);
                A += s.A_k;
            }
        }

        // création des pk
        std::vector<double> pks;
        pks.reserve(xs.size()-1);
        for (size_t i = 0; i < xs.size()-1; ++i) {
            pks.push_back(slices[i].A_k/A);
        }

        // préparation des parties de F
        F_parts.resize(xs.size());
        F_parts[0] = 0; // F_0 : premiere partie de la fonction de répartition -> 0 avant xs[0]

        for (size_t i = 1; i < F_parts.size(); ++i) {
            F_parts[i] = F_parts[i-1] + pks[i-1];
        }

        std::cout << "A: " << A << std::endl;
        std::cout << "nSlices: " << this->slices.size() << " : ";
        for (Slice<double>& s: slices) {
            std::cout << "(" << s.x1 << ", " << s.x2 << "), pk = " << s.A_k/A << " ";
        }
        std::cout << std::endl;
    }

    double generate() const {

        // On commence par sélectionner une intervalle en fonction du p_k associé à la tranche liée à cette intervalle.
        // K représente l'indice de l'intervalle sélectionné.
        size_t K = generateK();

        // Ensuite, on applique la méthode des fonctions inverses.
        Slice<double> s = slices[K];

        double y1 = s.f_k(s.x1);
        double y2 = s.f_k(s.x2);

        double U = generator->next();

        // Si y1 = y2, alors on est dans le cas d'une uniforme. Sinon, on inverse la fonction de repartition associée
        // à la fonction f_k.
        if (y1 == y2) {
            return s.x1 + U*(s.x2 - s.x1);
        } else {
            double m = (y2 - y1)/(s.x2 - s.x1);
            return s.x1 + (sqrt( (y2*y2 - y1*y1) * U + y1*y1) - y1) / m;
        }
    }

    ~MixedInverse() {
        delete generator;
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

#endif //LABO1_MIXEDINVERSE_H
