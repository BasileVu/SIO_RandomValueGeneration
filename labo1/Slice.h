#ifndef LABO1_PART_H
#define LABO1_PART_H

#include <functional>
#include "Point.h"

/**
 * Regroupe les informations du "morceau" d'une fonction affine par morceaux:
 * - les bornes de l'intervalle à prendre en compte pour le morceau.
 * - La fonction associée à cette intervalle.
 */
template <typename T>
struct Slice {

    // Func : fonction affine qui prend un T et renvoie un T.
    typedef std::function<T(T)> LinearFunc;

    T x1, x2; // bornes de l'intervalle définissant ce morceau.
    LinearFunc f_k; // fonction associée à ce morceau k.

    double A_k; // aire sous al fonction f_k
};

#endif //LABO1_PART_H
