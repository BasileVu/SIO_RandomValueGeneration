#include <iostream>
#include <random>
#include "UniformGenerator.h"
#include "HitOrMiss.h"

using namespace std;

int main() {

    using namespace std;

    seed_seq seed = {42, 42, 42};

    {
        vector<double> xs = {5, 15};
        vector<double> ys = {1, 1};

        HitOrMiss<double> hom(xs, ys, seed);
        double acc = 0;
        for (int i = 0; i < 10000000; ++i) {
           //cout << " > " << hom.generate() << endl;
            acc += hom.generate();
        }

        cout << acc / 10000000 << endl;
    }

    return EXIT_SUCCESS;
}