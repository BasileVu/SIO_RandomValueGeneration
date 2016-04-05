#ifndef LABO1_SLICE_H
#define LABO1_SLICE_H

#include <functional>

/**
 * Aire sous le morceau ("Tranche") d'une fonction affine par morceaux.
 */
template <typename T>
struct Slice {

    // Func : fonction affine qui prend un RealType et renvoie un RealType
    typedef std::function<T(T)> LinearFunc;

    T x1, x2; // x est dans la tranche si x appartient à [x1, x2]
    LinearFunc f;
};

#endif //LABO1_SLICE_H
