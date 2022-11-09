//
// Created by USER on 31.10.2022.
//

#ifndef LAB3_POLYNOM3V_H
#define LAB3_POLYNOM3V_H
#include <iostream>

namespace polynoms {
    class Polynom {
    private:
        int degree;
        double *coefs;
    public:
        Polynom(const int degree = 0);
        Polynom(const double arr[], const int degree = 0);
        Polynom(const Polynom&);
        Polynom(Polynom&&) noexcept ;
        ~Polynom();
        char* getStrPol() const;
        Polynom& operator =(const Polynom&);
        Polynom& operator =(Polynom&&) noexcept ;
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

#endif //LAB3_POLYNOM3V_H
