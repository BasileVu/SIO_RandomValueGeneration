#ifndef LABO1_MIXEDGEOMETRIC_H
#define LABO1_MIXEDGEOMETRIC_H

#include "PointGenerator.h"
#include "UniformGenerator.h"

class MixedGeometric {
private:
    const std::vector<double>& xs;
    const std::vector<double>& ys;
    RealPointGenerator<double>* pointGenerator;
    UniformRealGenerator<double>* generator;
    double a, b, yMax = 0;
    std::vector<Slice<double>> slices;

    std::vector<double> pks;
    double A = 0;
public:

    MixedGeometric(const std::vector<double>& xs, const std::vector<double>& ys, const std::seed_seq& seed) noexcept(false)
            : xs(xs), ys(ys) {

        generator = new UniformRealGenerator<double>(0, 1);

        a = xs.front(), b = xs.back();
        slices.reserve(xs.size());
        pks.reserve(xs.size()-1);

        for (size_t i = 0; i < xs.size(); ++i) {

            if (yMax < ys[i]) {
                yMax = ys[i];
            }

            // création de tranches
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
        for (size_t i = 0; i < xs.size()-1; ++i) {
            pks.push_back(slices[i].A_k/A);
        }

        pointGenerator = new RealPointGenerator<double>(a, b, 0, yMax, seed);

        std::cout << "a: " << this->a << ", b: " << this->b << ", yMax : " << this->yMax << std::endl;
        std::cout << "A: " << A << std::endl;
        std::cout << "nSlices: " << this->slices.size() << " : ";
        for (Slice<double>& s: slices) {
            std::cout << "(" << s.x1 << ", " << s.x2 << "), pk = " << s.A_k/A << " ";
        }
        std::cout << std::endl;
    }

    double generate() const {

        // on commence par générer la réalisation de la variable aléatoire discrete K de loi de proba P(K = k) = p_k.
        size_t K = generateK();

        // on génère une réalisation d'une variable de densité f_K
        double X;

        return X;
    }

    ~MixedGeometric() {
        delete pointGenerator;
        delete generator;
    }

private:
    // permet de trouve dans quel intervalle k on tombe en fonction de la probablilité p_k de la tranche liée à
    // cette intervalle
    size_t generateK() const {
        std::vector<double> F_parts(xs.size()); // "bouts" de la fonction de répartition; F_parts[i] = F_parts[i-1] + pks[i]
        F_parts[0] = 0; // F_0 : la fonction de répartition vaut 0 avant a

        for (size_t i = 1; i < F_parts.size(); ++i) {
            F_parts[i] = F_parts[i-1] + pks[i-1];
        }

        size_t j = 0;
        double U = generator->next();

        // on cherche l'indice de l'intervalle dans lequel on est tombé
        while (true) {
            if (U <= F_parts[j]) {
                return j;
            }
            ++j;
        }
    }
};

#endif //LABO1_MIXEDGEOMETRIC_H
