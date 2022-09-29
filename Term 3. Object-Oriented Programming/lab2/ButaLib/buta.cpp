//
// Created by USER on 24.09.2022.
//

#include "buta.h"
#include <cmath>
#include <cstring>
#include <cstdio>

using namespace butas;

Buta::Buta(const Point &p0, double m, double c): p(p0), m(m), c(c) {}
Buta::Buta(double m, double c, double x0, double y0): p(x0, y0), m(m), c(c) {}

Buta& Buta::setP(const Point &p0){ p = p0; return *this; }
Buta& Buta::setM(double M){ m = M; return *this; }
Buta& Buta::setC(double C){ c = C; return *this; }

Point Buta::getP() const{ return p; }
double Buta::getM() const{ return m; }
double Buta::getC() const{ return c; }

types Buta::getType() const {
    if (c == 0) {
        return types::BernoulliLemniscate;
    }
    if (c > 2 * m * m) {
        return types::ellipticPedal;
    }
    if (c == 2 * m * m) {
        return types::Circles;
    } else {
        return types::hyperbolicPedal;
    }
}

std::string Buta::getPrintableType() const {
    std::string arr[] = {
            "Elliptic pedal curve",
            "Hyperbolic pedal curve",
            "2 circles",
            "Bernoulli Lemniscate"
    };
    return arr[this->getType()];
}

double Buta::area() const {
    if (c == 0) {
        return 2 * m * m;
    }
    if (c > 2 * m * m) {
        return PI * c;
    }
    if (c == 2 * m * m) {
        return PI * m * m * 2;
    } else {
        double a = 2 * m * m + c, b = a - c - c;
        return c * atan(a / b) + a * b / 2;
    }
}

double Buta::getFirstCoefficient() const {
    if (c == 0) {
        return 2 * m * m;
    }
    if (c != 2 * m * m) {
        return 2 * m * m + c;
    } else {
        return 4 * m * m;
    }
}

double Buta::getSecondCoefficient() const {
    if (c == 0) {
        return 2 * m * m;
    }
    if (c != 2 * m * m) {
        return 2 * m * m - c;
    } else {
        return 0;
    }
}

double Buta::distance(double phi) const { //r^2 = a * (cos(phi))^2 - b * (sin(phi))^2, where a=(2m^2+c), b=(2m^2-c) can be simplified depending on c, m values
    if (c == 0) {
        return fabs(m) * sqrt(2 * cos(2 * phi));
    }
    if (c != 2 * m * m) {
        return sqrt((2 * m * m + c) * cos(phi) * cos(phi) - (2 * m * m - c) * sin(phi) * sin(phi));
    } else {
        return 2 * fabs(m * cos(phi));
    }
}

char* Buta::getPrintableEquation() const{
    double k1 = this->getFirstCoefficient(), k2 = this->getSecondCoefficient();
    const char* s1 = "r ^ 2 =  * (cos(phi)) ^ 2\n", *s2 = " - () * (sin(phi)) ^ 2";
    size_t l = strlen(s1) + 1, k;
    if (k2 != 0) {
        l += strlen(s2);
    }
    char num[20];
    sprintf(num, "%.2f", k1);
    l += strlen(num);
    sprintf(num, "%.2f", k2);
    l += strlen(num);
    char *s = new char[l];
    sprintf(s, "r ^ 2 = %.2f * (cos(phi)) ^ 2", k1);
    if (k2 != 0) {
        k = strlen(s);
        sprintf(s + k, " - (%.2f) * (sin(phi)) ^ 2", k2);
    }
    k = strlen(s);
    sprintf(s + k, "\n");
    return s;
}