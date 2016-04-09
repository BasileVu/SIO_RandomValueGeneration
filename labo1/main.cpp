#include <iostream>
#include <random>

#include "HitOrMiss.h"
#include "MixedGeometric.h"
#include "MixedInverse.h"
#include "Benchmarker.h"

using namespace std;

int main() {

    using namespace std;

    seed_seq seed = {42, 42, 42};
    size_t nSim = 10000000;

    cout << "Format : " << endl;
    cout << "-- <Ensemble de donnees> --" << endl;
    cout << "<Methode> : <esperance empirique>, <temps>s" << endl;
    cout << endl;

    {
        cout << "-- Uniforme (5,1) (15, 1) --" << endl;
        vector<double> xs = {5, 15};
        vector<double> ys = {1, 1};

        Benchmarker(HitOrMiss(xs, ys, seed)).run("Acceptation - rejet    ", nSim);
        Benchmarker(MixedGeometric(xs, ys, seed)).run("Melanges - geometrique ", nSim);
        Benchmarker(MixedInverse(xs, ys, seed)).run("Melanges - inverses    ", nSim);
        cout << endl;
    }

    {
        cout << "-- Deux triangulaires --" << endl;
        vector<double> xs = {2, 3, 7, 10, 14, 15};
        vector<double> ys = {0, 1, 0, 0, 1, 0};

        Benchmarker(HitOrMiss(xs, ys, seed)).run("Acceptation - rejet    ", nSim);
        Benchmarker(MixedGeometric(xs, ys, seed)).run("Melanges - geometrique ", nSim);
        Benchmarker(MixedInverse(xs, ys, seed)).run("Melanges - inverses    ", nSim);
        cout << endl;
    }

    {
        cout << "-- profil plutot plat --" << endl;
        vector<double> xs = {2, 4, 7, 9, 12, 13, 17, 20};
        vector<double> ys = {8, 10, 10, 9, 5, 9, 10, 6};

        Benchmarker(HitOrMiss(xs, ys, seed)).run("Acceptation - rejet    ", nSim);
        Benchmarker(MixedGeometric(xs, ys, seed)).run("Melanges - geometrique ", nSim);
        Benchmarker(MixedInverse(xs, ys, seed)).run("Melanges - inverses    ", nSim);
        cout << endl;
    }
    
    {
        cout << "-- Profil accidente --" << endl;
        vector<double> xs = {2, 3, 5, 10, 12, 13, 15, 17, 19, 20};
        vector<double> ys = {1, 10, 0, 1, 8, 4, 1, 0, 2, 9};

        Benchmarker(HitOrMiss(xs, ys, seed)).run("Acceptation - rejet    ", nSim);
        Benchmarker(MixedGeometric(xs, ys, seed)).run("Melanges - geometrique ", nSim);
        Benchmarker(MixedInverse(xs, ys, seed)).run("Melanges - inverses    ", nSim);
        cout << endl;
    }

    return EXIT_SUCCESS;
}