#ifndef CHECKER_H
#define CHECKER_H

#include <vector>

template <typename T>
class Checker {

public:
    static bool check(const std::vector<T>& xs, const std::vector<T>& ys) {

        if (xs.size() < 2 || ys.size() < 2) {
            return false;
        }

        return checkX(xs) && checkY(ys);
    }

private:
    static bool checkX(const std::vector<T>& v) {
        return iterate(v, [](const T& item) {

        });
    }

    static bool checkY(const std::vector<T>& v) {
        return iterate(v, [](const T& item) {

        });
    }


    template <typename Func>
    static bool iterate(const std::vector<T>& v, const Func& f) {
        const T& last = v[0];
        for (const T& item : v) {
            if (f(item)) {
                return false;
            }
        }
        return true;
    }
};

#endif // CHECKER_H
