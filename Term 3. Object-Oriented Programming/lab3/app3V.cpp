//
// Created by USER on 31.10.2022.
//


#include "./polynomLib/polynom3V.h"
#include <iostream>
using namespace polynoms;

int main() {
    double arr[] = {1, 2, 3};
    Polynom a, b(4), c(arr), d(arr, 2), e;
    std::cout << "Testing program" << std::endl << "Enter polynom degree and it's coefficients in ascending order" << std::endl;
    std::cin >> e;
    std::cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << " e: " << e << std::endl;
    Polynom f = a + b;
    std::cout << "f: " << f << std::endl;
    std::cout << "bdf values " << b.PolynomValue(1) << " " << d.PolynomValue(1) << " " << f.PolynomValue(4) << std::endl;
    Polynom g = ~d;
    std::cout << "g: " << g << std::endl;
    double sqr[] = {1, -2, 1};
    Polynom h(sqr, 2);
    double remainder = 1;
    h.divideByXB(remainder);
    std::cout << "h: " << h << std::endl;;
    std::cout << "remainder " << remainder << std::endl;
    double abb[] = {2, -3, 1};
    Polynom i(abb, 2);
    try {
        std::cout << i.zeroBySegment(0, 3);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << "i first root " << i.zeroBySegment(0, 1.5) << std::endl;
    std::cout << "i second root " << i.zeroBySegment(1.5, 4) << std::endl;
}