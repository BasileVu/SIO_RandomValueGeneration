#include <iostream>
#include <vector>
#include <iomanip>

#include "Stats.h"

using namespace std;


// Represente un jeu de donnees
struct Dataset {
    string name; // nom du jeu de donnees
    pair<vector<double>, vector<double>> values; // valeurs associees
};


// Affichage des en-tetes des colonnes.
void printHeader(const string& name) {
    cout << " " << name << endl;
    cout << "                     moyenne  |  ecart-type  |             IC             |   delta" << endl;
}

// Affichage des valeurs.
void print(const string& name, double mean, double stdDev, const ConfidenceInterval& ic) {
    cout << name
    << setw(12) << mean << " | "
    << setw(12) << stdDev << " | "
    << setw(26) << ic.toString() << " | " << setw(12) << ic.delta << endl;
}

// lance nSims simulations de nGenValues generations de realisations de variables aleatoires
// et affiche les resultats.
void test(const string& name, RandomValueGenerator& generator, size_t nGenValues, size_t nSims) {
    std::vector<double> values = Stats::generateNValues(generator, nGenValues);

    printHeader(name);
    print("  generations :  ", Stats::mean(values), Stats::sampleStdDev(values), Stats::confidenceInterval(values, 1.96));

    // creation des temps
    std::vector<double> times;
    times.reserve(nSims);
    for (size_t i = 0; i < nSims; ++i) {
        clock_t start = clock();
        Stats::generateNValues(generator, nGenValues);
        times.push_back((double)(clock() - start) / CLOCKS_PER_SEC);
    }

    print("  temps[s]    :  ", Stats::mean(times), Stats::sampleStdDev(times), Stats::confidenceInterval(times, 1.96));
    cout << endl;
}


int main() {

    // graine
    seed_seq seed = {24, 512, 42};

    // nombre de realisations a generer et nombre de simulations a effectuer
    size_t nGenValues = 1000000, nSims = 5;

    // jeux de donnees
    vector<Dataset> datasets = {
            {"Variable uniforme U(5,15)", {{5, 15}, {1, 1}}},
            {"Melange de deux variables triangulaires", {{2, 3, 7, 10, 14, 15}, {0, 1, 0, 0, 1, 0}}},
            {"Profil plutot plat", {{2, 4, 7, 9, 12, 13, 17, 20}, {8, 10, 10, 9, 5, 9, 10, 6}}},
            {"Profil accidente", {{2, 3, 5, 10, 12, 13, 15, 17, 19, 20}, {1, 10, 0, 1, 8, 4, 1, 0, 2, 9}}}
    };

    cout << "Tests de " << nSims << " simulations avec " << nGenValues << " generations" << "\n\n";

    // test de tous les jeux de donnees avec les differentes methodes
    for (const Dataset& dataset : datasets) {
        const vector<double>& xs = dataset.values.first;
        const vector<double>& ys = dataset.values.second;

        // affiche de l'esperance
        cout << "-- " + dataset.name << " --" << endl;
        cout << " Esperance : " << Stats::expectedValue(xs, ys) << endl;

        // creation des generateurs
        HitOrMiss hom(xs, ys);
        Geometric geo(xs, ys);
        InverseFunctions inv(xs, ys);

        // on donne la graine aux generateurs
        hom.setSeed(seed);
        geo.setSeed(seed);
        inv.setSeed(seed);

        // lancement des tests
        test("Acceptation - rejet   ", hom, nGenValues, nSims);
        test("Melanges - geometrique", geo, nGenValues, nSims);
        test("Melanges - inverses   ", inv, nGenValues, nSims);
        cout << "\n\n";
    }

    return EXIT_SUCCESS;
}