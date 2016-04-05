#include <iostream>
#include <random>
#include "Generator.h"
#include "HitOrMiss.h"

using namespace std;

int main() {

    using namespace std;

    seed_seq seed = {42, 42, 42};

    vector<double> xs = {1, 2, 3, 4, 15};
    vector<double> ys = {15, 2, 3, 4, 15};

    HitOrMiss<double> hom(xs, ys, seed);
    for (int i = 0; i < 20; ++i) {
        cout << hom.generate() << endl;
    }

    return EXIT_SUCCESS;
}