#include "Checker.h"
#include "RandomValueGenerator.h"

RandomValueGenerator::RandomValueGenerator(const std::vector<double>& xs, const std::vector<double>& ys)
            : func(xs, ys), generator(UniformGenerator(0, 1)) {

    // verification de la validité des données
    if (!Checker::check(xs, ys)) {
        throw std::invalid_argument("Les donnees ne sont pas valides.");
    }

    // création des pk
    std::vector<double> pks;
    pks.reserve(xs.size()-1);
    for (size_t i = 0; i < xs.size()-1; ++i) {
        pks.push_back(func.pieces[i].A_k/func.A);
    }

    // préparation des parties de F
    F_parts.resize(xs.size());
    F_parts[0] = 0; // F_0 : premiere partie de la fonction de répartition -> 0 avant xs[0]

    for (size_t i = 1; i < F_parts.size(); ++i) {
        F_parts[i] = F_parts[i-1] + pks[i-1];
    }
}

void RandomValueGenerator::setSeed(const std::seed_seq& seed) {
    generator.setSeed(seed);
}

size_t RandomValueGenerator::generateK() {
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

HitOrMiss::HitOrMiss(const std::vector<double>& xs, const std::vector<double>& ys)
        : RandomValueGenerator(xs, ys) {
    a = xs.front(), b = xs.back();
    yMax = *std::max_element(ys.begin(), ys.end());
}

Geometric::Geometric(const std::vector<double>& xs, const std::vector<double>& ys)
        : RandomValueGenerator(xs, ys) {}

InverseFunctions::InverseFunctions(const std::vector<double>& xs, const std::vector<double>& ys)
        : RandomValueGenerator(xs, ys) {}


double HitOrMiss::generate() {

    double X, Y;
    size_t sliceIndex;  // indice de la "tranche" dans laquelle X se trouvera

    do {
        // génération du point (X,Y)
        X = generator.next() * (b - a) + a;
        Y = generator.next() * yMax;

        // on cherche le morceau lié à l'intervalle dans laquelle X se trouve
        sliceIndex = func.findPart(X);

        // rejet si Y est > que f(X), avec f_k la fonction affine associée à la tranche k
    } while (Y > func.pieces[sliceIndex].f_k(X));

    return X;
}


double Geometric::generate() {

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

double InverseFunctions::generate() {

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
