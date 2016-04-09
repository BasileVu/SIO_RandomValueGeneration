#ifndef LABO1_PART_H
#define LABO1_PART_H

#include <functional>
#include "Point.h"

/**
 * Regroupe les informations du "morceau" d'une fonction affine par morceaux.
 */
template <typename T>
struct Slice {

    // fonction linéaire prenant un T et renvoyant un T
    typedef std::function<T(T)> LinearFunc;

    Point<T> p1, p2;         // les deux points définissant f_k.
    double A_k;              // aire sous la fonction f_k
    LinearFunc f_k; // fonction associée à ce morceau k.
};

#endif //LABO1_PART_H
