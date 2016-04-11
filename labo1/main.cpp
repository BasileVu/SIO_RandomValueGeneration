#include <iostream>
#include <random>
#include <vector>
#include <string>

#include "HitOrMiss.h"
#include "MixedGeometric.h"
#include "MixedInverse.h"
#include "Benchmarker.h"

using namespace std;

struct Dataset {
    string name;
    pair<vector<double>, vector<double>> values;
};

void test(const string& name, RandomValueGenerator& generator, size_t nGenValues, size_t nIntervals) {
    cout << " " << name << "(" << nGenValues << ") :" << endl;
    cout << "  " << EmpiricalEGenerator::generate(generator, nGenValues) << endl;

    double meanTime = 0;
    for (size_t i = 0; i < nIntervals; ++i) {
        meanTime += Benchmarker::run(generator, nGenValues);
    }

    cout << "  " << meanTime/nIntervals << "s" << endl;
}

int main() {

    seed_seq seed = {42, 42, 42};
    size_t nGenValues = 1000000, nIntervals = 1;

    cout << "Format : " << endl;
    cout << "-- <Ensemble de donnees> --" << endl;
    cout << "Esperance theorique: <esperance theorique>" << endl;
    cout << "<Methode> (<nombre de generations>):" << endl;
    cout << " <esperance empirique>" << endl;
    cout << " <moyenne des temps>s" << endl;
    cout << endl;

    vector<Dataset> datasets = {
            {"Variable uniforme U(5,15)", {{5, 15}, {1, 1}}},
            {"Melange de deux variables triangulaires", {{2, 3, 7, 10, 14, 15}, {0, 1, 0, 0, 1, 0}}},
            {"Profil plutot plat", {{2, 4, 7, 9, 12, 13, 17, 20}, {8, 10, 10, 9, 5, 9, 10, 6}}},
            {"Profil accidente", {{2, 3, 5, 10, 12, 13, 15, 17, 19, 20}, {1, 10, 0, 1, 8, 4, 1, 0, 2, 9}}}
    };

    for (const Dataset& dataset : datasets) {
        const vector<double>& xs = dataset.values.first;
        const vector<double>& ys = dataset.values.second;

        cout << "-- " + dataset.name << " --" << endl;
        cout << " Esperance theorique    : " << TheoricalECalculator::calculate(xs, ys) << endl;

        HitOrMiss hom(xs, ys, seed);
        MixedGeometric mgeo(xs, ys, seed);
        MixedInverse minv(xs, ys, seed);


        test("Acceptation - rejet   ", hom, nGenValues, nIntervals);
        test("Melanges - geometrique", mgeo, nGenValues, nIntervals);
        test("Melanges - inverses   ", minv, nGenValues, nIntervals);
        cout << endl;
    }

    return EXIT_SUCCESS;
}