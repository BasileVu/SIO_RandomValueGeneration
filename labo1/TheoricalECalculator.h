#ifndef THEORICAL_E_CALCULATOR_H
#define THEORICAL_E_CALCULATOR_H

#include "PiecewiseFunction.h"

template <typename T>
class TheoricalECalculator {
public:
    static double calculate(const std::vector<T>& xs, const std::vector<T>& ys) {
        PiecewiseLinearFunction<T> func(xs, ys);
        double res = 0;
        for (const Piece<T>& p : func.pieces) {
            T x0 = p.p0.x, x1 = p.p1.x;
            T y0 = p.p0.y, y1 = p.p1.y;

            if (y0 + y1 > 0) {
                double eVal = (y0 * (2 * x0 + x1) + y1 * (x0 + 2 * x1)) / (3 * (y0 + y1));
                res += eVal * p.A_k;
            }
        }
        return res / func.A;
    }
};

#endif // THEORICAL_E_CALCULATOR_H
