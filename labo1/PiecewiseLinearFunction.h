#ifndef PIECEWISE_LINEAR_FUNCTION_H
#define PIECEWISE_LINEAR_FUNCTION_H

#include <vector>
#include <functional>
#include "Point.h"

/**
 * Regroupe les informations du "morceau" d'une fonction affine par morceaux.
 */
struct Piece {

    // fonction linéaire prenant un double et renvoyant un double
    typedef std::function<double(double)> LinearFunc;

    Point p0, p1;         // les deux points définissant f_k.
    double A_k;       // aire sous la fonction f_k
    LinearFunc f_k;   // fonction associée à ce morceau k.
};

struct PiecewiseLinearFunction {
    std::vector<Piece> pieces;   // "morceaux" de la fonction
    double A = 0;                   // aire totale sous la fonction

    PiecewiseLinearFunction(const std::vector<double>& xs, const std::vector<double>& ys) {

        pieces.reserve(xs.size());
        for (size_t i = 0; i < xs.size(); ++i) {

            if (i < xs.size() - 1) {

                Piece s {{xs[i], ys[i]}, {xs[i+1], ys[i+1]}};
                s.A_k = (double)(ys[i+1] + ys[i]) * (xs[i+1] - xs[i]) / 2;
                s.f_k = [&xs, &ys, i](double x) {
                    double m = (ys[i + 1] - ys[i]) / (xs[i+1] - xs[i]);
                    return m * (x - xs[i]) + ys[i];
                };

                pieces.push_back(s);
                A += s.A_k;
            }
        }
    }

};

#endif // PIECEWISE_LINEAR_FUNCTION_H
