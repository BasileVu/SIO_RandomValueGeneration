#include <iostream>
#include <random>
#include "UPRNG.h"

using namespace std;

int main() {
    std::seed_seq seed = {42, 42, 42};
    UniformGenerator<uintmax_t> generator(5, 10, seed);

    for (int i = 0; i < 20; ++i) {
        cout << generator.next() << endl;
    }

    return EXIT_SUCCESS;
}