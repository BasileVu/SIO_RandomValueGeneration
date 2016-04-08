#ifndef LABO1_PART_H
#define LABO1_PART_H

#include <functional>

/**
 * Regroupe les informations du "morceau" d'une fonction affine par morceaux:
 * - les bornes de l'intervalle à prendre en compte pour le morceau.
 * - La fonction associée à cette intervalle.
 */
template <typename T>
struct Part {

    // Func : fonction affine qui prend un T et renvoie un T.
    typedef std::function<T(T)> LinearFunc;

    T x1, x2; // bornes de l'intervalle définissant ce morceau.
    LinearFunc f; // fonction associée à ce morceau.
};

#endif //LABO1_PART_H
