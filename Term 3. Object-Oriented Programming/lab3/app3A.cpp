//
// Created by USER on 17.10.2022.
//

#include "./polynomLib/polynom.h"
#include <iostream>
using namespace polynoms;

int main() {
    double arr[] = {1, 2, 3}, sqr[] = {1, 2, 1}, abb[] = {2, -3, 1};
    Polynom a, b(4), c(arr), d(arr, 2), e;
    //e.consoleInput(std::cin);
    a.Print(std::cout);
    b.Print(std::cout);
    c.Print(std::cout);
    d.Print(std::cout);
    //e.Print(std::cout);
    Polynom f = a.add(b);
    f.Print(std::cout);
    std::cout << b.PolynomValue(1) << " " << d.PolynomValue(1) << " " << f.PolynomValue(4) << std::endl;
    Polynom g = d.derivative();
    g.Print(std::cout);
    Polynom h(sqr, 2);
    double root = 1;
    h.divideByXB(root);
    h.Print(std::cout);
    std::cout << root << std::endl;
    Polynom i(abb, 2);
    try {
        std::cout << i.zeroBySegment(0, 3);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << i.zeroBySegment(0, 1.5) << std::endl;
    std::cout << i.zeroBySegment(1.5, 4) << std::endl;
}