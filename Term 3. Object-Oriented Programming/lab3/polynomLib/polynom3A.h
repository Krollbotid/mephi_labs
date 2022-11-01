//
// Created by USER on 08.10.2022.
//

#ifndef LAB3_POLYNOM3A_H
#define LAB3_POLYNOM3A_H
#include <iostream>

namespace polynoms {
    class Polynom {
    private:
        static const int maxdegree = 20;
        int degree;
        double coefs[maxdegree + 1];
    public:
        Polynom(const int degree = 0);
        Polynom(const double arr[], const int degree = 0);
        Polynom& consoleInput(std::istream& stream);
        std::ostream& Print(std::ostream&) const;
        Polynom add(Polynom b) const;
        double PolynomValue(double x) const;
        Polynom derivative() const;
        Polynom& divideByXB(double& b);
        double zeroBySegment(double begin, double end) const;
    };
}

#endif //LAB3_POLYNOM3A_H
