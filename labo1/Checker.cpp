#include <vector>
#include <cstddef>

#include "Checker.h"

bool Checker::check(const std::vector<double>& xs, const std::vector<double>& ys) {
    if (xs.size() < 2 || ys.size() < 2 || xs.size() != ys.size()) {
        return false;
    }

    return checkX(xs) && checkY(ys);
}


bool Checker::checkX(const std::vector<double>& v) {

    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i] <= v[i-1]) {
            return false;
        }
    }

    return true;
}

bool Checker::checkY(const std::vector<double>& v) {
    bool yNotZero = false;

    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] < 0) {
            return false;
        }

        if (v[i] > 0) {
            yNotZero = true;
        }
    }

    return yNotZero;
}
