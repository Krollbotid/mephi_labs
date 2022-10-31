//
// Created by USER on 28.10.2022.
//

#ifndef LAB3B_POLYNOM3B_H
#define LAB3B_POLYNOM3B_H
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
        friend std::istream& operator >> (std::istream&, Polynom&);
        friend std::ostream& operator << (std::ostream&, const Polynom&);
        friend const Polynom operator + (const Polynom&, const Polynom&);
        double PolynomValue(double x) const;
        Polynom operator ~ () const;
        Polynom& divideByXB(double& b);
        double zeroBySegment(double begin, double end) const;
        friend const bool operator == (const Polynom&, const Polynom&);
    };
}

#endif //LAB3B_POLYNOM3B_H
