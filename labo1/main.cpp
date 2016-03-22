#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "PRNG.h"

using namespace std;

int main() {
    UniformGenerator<uintmax_t> generator(5, 10);

    for (int i = 0; i < 20; ++i) {
        cout << generator.next() << endl;
    }

    return EXIT_SUCCESS;
}