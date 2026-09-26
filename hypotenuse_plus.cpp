/*
#include "hypotenuse_plus.h"
#include <cmath>

    // int, double
double Hypo::hypotenuse_plus(const int& a, const int& b) {
    return std::sqrt(static_cast<double>(a) * a +
        static_cast<double>(b) * b);
}

    // double, int
int Hypo::hypotenuse_plus(const double& a, const double& b) {
    return static_cast<int>(std::sqrt(a * a + b * b));
}


template <>
double Hypo_M::hypotenuse_plus<double, int>(int& a, int& b) {
    double h = std::sqrt(static_cast<double>(a) * a + static_cast<double>(b) * b);
    a = static_cast<int>(h);
    b = static_cast<int>(h);
    return h;
}

template <>
int Hypo_M::hypotenuse_plus<int, double>(double& a, double& b) {
    double h = std::sqrt(a * a + b * b);
    a = h;
    b = h;
    return static_cast<int>(h);
}
*/