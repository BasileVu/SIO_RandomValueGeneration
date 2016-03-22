#include <iostream>
#include <random>
#include "Generator.h"

using namespace std;

int main() {

    UniformRealGenerator<double> generator(0, 1);
    generator.setSeed({42, 42, 42});

    for (int i = 0; i < 20; ++i) {
        cout << generator.next() << endl;
    }

    return EXIT_SUCCESS;
}