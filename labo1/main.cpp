#include <iostream>
#include <random>
#include "HitOrMiss.h"
#include "MixedGeometric.h"
#include "MixedInverse.h"
#include "ExpectedValueEstimator.h"

using namespace std;

int main() {

    using namespace std;

    seed_seq seed = {42, 42, 42};

    {
        cout << "-- Uniforme (5,1) (15, 1) --" << endl;
        vector<double> xs = {5, 15};
        vector<double> ys = {1, 1};

        cout << ExpectedValueEstimator<double, double>(HitOrMiss(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedGeometric(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedInverse(xs, ys, seed)).generate(1000000) << endl;
    }

    {
        cout << "-- Deux triangulaires --" << endl;
        vector<double> xs = {2, 3, 7, 10, 14, 15};
        vector<double> ys = {0, 1, 0, 0, 1, 0};

        cout << ExpectedValueEstimator<double, double>(HitOrMiss(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedGeometric(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedInverse(xs, ys, seed)).generate(1000000) << endl;
    }

    {
        cout << "-- profil plutot plat --" << endl;
        vector<double> xs = {2, 4, 7, 9, 12, 13, 17, 20};
        vector<double> ys = {8, 10, 10, 9, 5, 9, 10, 6};

        cout << ExpectedValueEstimator<double, double>(HitOrMiss(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedGeometric(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedInverse(xs, ys, seed)).generate(1000000) << endl;
    }
    
    {
        cout << "-- Profil accidenté --" << endl;
        vector<double> xs = {2, 3, 5, 10, 12, 13, 15, 17, 19, 20};
        vector<double> ys = {1, 10, 0, 1, 8, 4, 1, 0, 2, 9};

        cout << ExpectedValueEstimator<double, double>(HitOrMiss(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedGeometric(xs, ys, seed)).generate(1000000) << endl;
        cout << ExpectedValueEstimator<double, double>(MixedInverse(xs, ys, seed)).generate(1000000) << endl;
    }

    return EXIT_SUCCESS;
}