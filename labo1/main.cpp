#include <iostream>
#include <random>
#include "HitOrMiss.h"

using namespace std;

int main() {

    using namespace std;

    seed_seq seed = {42, 42, 42};

    {
        vector<double> xs = {1, 15};
        vector<double> ys = {1, 1};

        HitOrMiss<double> hom(xs, ys, seed);
        double acc = 0;
        for (int i = 0; i < 1000000; ++i) {
            //cout << " > " << hom.generate() << endl;
            acc += hom.generate();
        }

        cout << "> " << acc / 1000000 << endl;
    }

    {
        vector<double> xs = {2, 3, 7, 10, 14, 15};
        vector<double> ys = {0, 1, 0, 0, 1, 0};

        HitOrMiss<double> hom(xs, ys, seed);
        double acc = 0;
        for (int i = 0; i < 1000000; ++i) {
           //cout << " > " << hom.generate() << endl;
            acc += hom.generate();
        }

        cout << "> " << acc / 1000000 << endl;
    }

    {
        vector<double> xs = {2, 4, 7, 9, 12, 13, 17, 20};
        vector<double> ys = {8, 10, 10, 9, 5, 9, 19, 6};

        HitOrMiss<double> hom(xs, ys, seed);
        double acc = 0;
        for (int i = 0; i < 1000000; ++i) {
            //cout << " > " << hom.generate() << endl;
            acc += hom.generate();
        }

        cout << "> " << acc / 1000000 << endl;
    }
    
    {
        vector<double> xs = {2, 3, 5, 10, 12, 13, 15, 17, 19, 20};
        vector<double> ys = {1, 10, 0, 1, 8, 4, 1, 0, 2, 9};

        HitOrMiss<double> hom(xs, ys, seed);
        double acc = 0;
        for (int i = 0; i < 1000000; ++i) {
            //cout << " > " << hom.generate() << endl;
            acc += hom.generate();
        }

        cout << "> " << acc / 1000000 << endl;
    }

    return EXIT_SUCCESS;
}