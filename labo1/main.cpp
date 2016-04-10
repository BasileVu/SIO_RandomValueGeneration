#include <iostream>
#include <random>
#include <vector>
#include <string>

#include "HitOrMiss.h"
#include "MixedGeometric.h"
#include "MixedInverse.h"
#include "Benchmarker.h"

using namespace std;

int main() {

    using namespace std;
    typedef pair<vector<double>, vector<double>> Dataset;

    seed_seq seed = {42, 42, 42};
    size_t nSim = 1000000;

    cout << "Format : " << endl;
    cout << "-- <Ensemble de donnees> --" << endl;
    cout << "<Methode> : <esperance empirique>, <temps>s" << endl;
    cout << endl;

    vector<Dataset> dataSets = {
            {{5, 15}, {1,1}},
            {{2, 3, 7, 10, 14, 15}, {0, 1, 0, 0, 1, 0}},
            {{2, 4, 7, 9, 12, 13, 17, 20}, {8, 10, 10, 9, 5, 9, 10, 6}},
            {{2, 3, 5, 10, 12, 13, 15, 17, 19, 20}, {1, 10, 0, 1, 8, 4, 1, 0, 2, 9}}
    };

    vector<string> datasetNames = {
        "Uniforme",
        "Deux triangulaires",
        "Profil plutot plat",
        "Profil accidente"
    };

    for (size_t i = 0; i < dataSets.size(); ++i) {
        cout << "-- " + datasetNames[i] << " --" << endl;
        vector<double>& xs = dataSets[i].first;
        vector<double>& ys = dataSets[i].second;

        Benchmarker(HitOrMiss(xs, ys, seed), xs, ys).run("Acceptation - rejet    ", nSim);
        Benchmarker(MixedGeometric(xs, ys, seed), xs, ys).run("Melanges - geometrique ", nSim);
        Benchmarker(MixedInverse(xs, ys, seed), xs, ys).run("Melanges - inverses    ", nSim);
        cout << endl;
    }

    return EXIT_SUCCESS;
}