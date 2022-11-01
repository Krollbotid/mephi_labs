//
// Created by USER on 31.10.2022.
//


#include "./polynomLib/polynom3V.h"
#include <iostream>
using namespace polynoms;

int main() {
    double arr[] = {1, 2, 3}, sqr[] = {1, -2, 1}, abb[] = {2, -3, 1};
    Polynom a, b(4), c(arr), d(arr, 2), e;
    std::cin >> e;
    std::cout << "abcde " << a << b << c << d << e;
    Polynom f = a + b;
    std::cout << "f " << f;
    std::cout << "bdf values " << b.PolynomValue(1) << " " << d.PolynomValue(1) << " " << f.PolynomValue(4) << std::endl;
    Polynom g = ~d;
    std::cout << "g " << g;
    Polynom h(sqr, 2);
    double root = 1;
    h.divideByXB(root);
    std::cout << "h " << h;
    std::cout << "root " << root << std::endl;
    Polynom i(abb, 2);
    try {
        std::cout << i.zeroBySegment(0, 3);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "i first " << i.zeroBySegment(0, 1.5) << std::endl;
    std::cout << "i second " << i.zeroBySegment(1.5, 4) << std::endl;
}