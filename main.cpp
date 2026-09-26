#include <iostream>
#include "hypotenuse_plus.h"

int main() {

    std::cout << "\n hypotenuse_plus" << std::endl;
    int ia = 4, ib = 5;
    double r1 = Hypo::hypotenuse_plus<double, int>(ia, ib);
    std::cout << "int -> double : " << r1 << std::endl;

    double dda = 7.0, ddb = 8.0;
    int r3 = Hypo::hypotenuse_plus<int, double>(dda, ddb);
    std::cout << "double -> int : " << r3 << "\n" << std::endl;

    std::cout << "\n hypotenuse_plus_mod" << std::endl;
    int mx = 4, my = 5;
    std::cout << "Before / x = " << mx << ", y = " << my << std::endl;
    double rm1 = Hypo_M::hypotenuse_plus<double, int>(mx, my);
    std::cout << "After / x = " << mx << ", y = " << my << "  result = " << rm1 << std::endl;

    double mdx = 7.0, mdy = 8.0;
    std::cout << "Before / x = " << mdx << ", y = " << mdy << std::endl;
    int rm2 = Hypo_M::hypotenuse_plus<int, double>(mdx, mdy);
    std::cout << "After / x = " << mdx << ", y = " << mdy << "  result = " << rm2 << "\n" << std::endl;
    return 0;
}