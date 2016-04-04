#include <iostream>
#include <random>
#include "Generator.h"
#include "HitOrMiss.h"

using namespace std;

double a = 3, b = 4;
double gVal = 1/(b-a);

double f(double x) {
    return x;
}

double g(double x) {
   return gVal;
}


int main() {

    using namespace std;

    seed_seq seed = {42, 42, 42};

    vector<double> xs = {1, 15};
    vector<double> ys = {15, 15};

    HitOrMiss<double> hom(xs, ys, seed);
    for (int i = 0; i < 20; ++i) {
        cout << hom.generate() << endl;
    }

    return EXIT_SUCCESS;
}