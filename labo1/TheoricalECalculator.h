#ifndef THEORICAL_E_CALCULATOR_H
#define THEORICAL_E_CALCULATOR_H

#include "PiecewiseFunction.h"

template <typename T>
class TheoricalECalculator {
public:
    static T calculate(const PiecewiseLinearFunction<T>& func) {
        for (const Piece<T>& p : func.pieces) {
            T x1 = p.p0.x, x2 = p.p1.x;
            T y1 = p.p0.y, y2 = p.p1.y;
        }
    }
};

#endif // THEORICAL_E_CALCULATOR_H
