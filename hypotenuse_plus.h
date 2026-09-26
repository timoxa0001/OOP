#ifndef HYPOTENUSE_PLUS_H
#define HYPOTENUSE_PLUS_H
#include <cmath>
namespace Hypo {

    template <typename T2, typename T1>
    T2 hypotenuse_plus(const T1& a, const T1& b) {
        double h = std::sqrt(static_cast<double>(a) * a +
                             static_cast<double>(b) * b);
        return static_cast<T2>(h);
    }
}

namespace Hypo_M {

    template <typename T2, typename T1>
    T2 hypotenuse_plus(T1& a, T1& b) {
        double h = std::sqrt(static_cast<double>(a) * a +
            static_cast<double>(b) * b);
        a = static_cast<T1>(h);
        b = static_cast<T1>(h);
        return static_cast<T2>(h);
    }
}
#endif