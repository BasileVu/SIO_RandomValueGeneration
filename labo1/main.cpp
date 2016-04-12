#include <iostream>
#include <random>
#include <vector>
#include <string>

#include "HitOrMiss.h"
#include "Geometric.h"
#include "Inverse.h"
#include "Benchmarker.h"
#include "Stats.h"

using namespace std;

struct Dataset {
    string name;
    pair<vector<double>, vector<double>> values;
};

void test(const string& name, RandomValueGenerator& generator, size_t nGenValues, size_t nSims) {
    std::pair<double, double> ic;
    std::vector<double> values = Stats::generateNValues(generator, nGenValues);

    cout << " " << name << endl;
    cout << "  " << nGenValues << " | " << Stats::mean(values) << " | " << Stats::sampleStdDev(values);
    ic = Stats::confidenceInterval(values, 1.96);
    cout << " | [" << ic.first << ", " << ic.second << "]" << endl;

    std::vector<double> times;
    times.reserve(nSims);
    for (size_t i = 0; i < nSims; ++i) {
        times.push_back(Benchmarker::run(generator, nGenValues));
    }

    cout << "  " << nSims << " | " << Stats::mean(times) << "s | " << Stats::sampleStdDev(values);
    ic = Stats::confidenceInterval(times, 1.96);
    cout << " | [" << ic.first << ", " << ic.second << "]" << endl;

}

int main() {

    seed_seq seed = {42, 42, 42};
    size_t nGenValues = 100000, nSims = 1000;

    cout << "Format : " << endl;
    cout << "-- <Ensemble de donnees> --" << endl;
    cout << "Esperance : <esperance>" << endl;
    cout << "<Methode>:" << endl;
    cout << " <nombre de generations> | <moyenne des V.A>    | <estimateur d'ecart-type> | <IC>" << endl;
    cout << " <nombre de simulations> | <moyenne des temps>s | <estimateur d'ecart-type> | <IC>" << endl;
    cout << endl;

    vector<Dataset> datasets = {
            {"Variable uniforme U(5,15)", {{5, 15}, {1, 1}}},
            {"Melange de deux variables triangulaires", {{2, 3, 7, 10, 14, 15}, {0, 1, 0, 0, 1, 0}}},
            {"Profil plutot plat", {{2, 4, 7, 9, 12, 13, 17, 20}, {8, 10, 10, 9, 5, 9, 10, 6}}},
            {"Profil accidente", {{2, 3, 5, 10, 12, 13, 15, 17, 19, 20}, {1, 10, 0, 1, 8, 4, 1, 0, 2, 9}}}
    };

    cout << "Tests avec " << nGenValues << " generations de V.A. et " << nSims << " simulations" << "\n\n";

    for (const Dataset& dataset : datasets) {
        const vector<double>& xs = dataset.values.first;
        const vector<double>& ys = dataset.values.second;

        cout << "-- " + dataset.name << " --" << endl;
        cout << " Esperance theorique    : " << Stats::expectedValue(xs, ys) << endl;

        HitOrMiss hom(xs, ys, seed);
        Geometric geo(xs, ys, seed);
        InverseFunctions inv(xs, ys, seed);


        test("Acceptation - rejet   ", hom, nGenValues, nSims);
        test("Melanges - geometrique", geo, nGenValues, nSims);
        test("Melanges - inverses   ", inv, nGenValues, nSims);
        cout << endl;
    }

    return EXIT_SUCCESS;
}