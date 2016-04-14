#ifndef CHECKER_H
#define CHECKER_H

#include <vector>
#include <cstddef>

class Checker {
public:
    static bool check(const std::vector<double>& xs, const std::vector<double>& ys);

private:
    static bool checkX(const std::vector<double>& v);
    static bool checkY(const std::vector<double>& v);
};

#endif // CHECKER_H
