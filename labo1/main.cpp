#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <iomanip>

#include "HitOrMiss.h"
#include "Geometric.h"
#include "Inverse.h"
#include "Stats.h"

using namespace std;

struct Dataset {
    string name;
    pair<vector<double>, vector<double>> values;
};

void printHeader(const string& name) {
    cout << " " << name << "\n\n";
    cout << "                 moyenne  |  ecart-type  |           IC           |  delta" << endl;
}

void print(const string& name, double mean, double stdDev, const ConfidenceInterval& ic) {
    cout << name
    << setw(8) << mean << " | "
    << setw(12) << stdDev << " | "
    << setw(22) << ic.toString() << " | " << setw(8) << ic.delta << endl;
}

void test(const string& name, RandomValueGenerator& generator, size_t nGenValues, size_t nSims) {
    std::vector<double> values = Stats::generateNValues(generator, nGenValues);

    printHeader(name);
    print("  generations :  ", Stats::mean(values), Stats::sampleStdDev(values), Stats::confidenceInterval(values, 1.96));

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

    seed_seq seed = {42, 42, 42};
    size_t nGenValues = 1000000, nSims = 2;

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
        cout << " Esperance : " << Stats::expectedValue(xs, ys) << endl;

        HitOrMiss hom(xs, ys, seed);
        Geometric geo(xs, ys, seed);
        InverseFunctions inv(xs, ys, seed);

        hom.setSeed(seed);
        geo.setSeed(seed);
        inv.setSeed(seed);

        test("Acceptation - rejet   ", hom, nGenValues, nSims);
        test("Melanges - geometrique", geo, nGenValues, nSims);
        test("Melanges - inverses   ", inv, nGenValues, nSims);
        cout << "\n\n";
    }

    return EXIT_SUCCESS;
}