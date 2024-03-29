//
// Created by USER on 08.10.2022.
//

#include "polynom3A.h"

using namespace polynoms;

Polynom::Polynom(const int degree): degree(degree) {
    if (degree > maxdegree) { throw std::invalid_argument("Too big degree!"); }
    if (degree < 0) { throw std::invalid_argument("Degree cannot be negative!"); }
    for (int i = 0; i <= degree; i++) {
        coefs[i] = 1;
    }
    for (int i = degree + 1; i < maxdegree + 1; i++) {
        coefs[i] = 0;
    }
}

Polynom::Polynom(const double arr[], const int degree): degree(degree) {
    if (arr == nullptr) { throw std::invalid_argument("Incorrect array pf coefficients"); }
    if (degree > maxdegree) { throw std::invalid_argument("Too big degree!"); }
    if (degree < 0) { throw std::invalid_argument("Degree cannot be negative!"); }
    for (int i = 0; i <= degree; i++) {
        coefs[i] = arr[i];
    }
    for (int i = degree + 1; i < maxdegree + 1; i++) {
        coefs[i] = 0;
    }
}

Polynom& Polynom::consoleInput(std::istream& stream) {
    int degree;
    stream >> degree;
    stream.clear();
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (degree < 0 || degree > maxdegree) {
        throw std::invalid_argument("Incorrect degree");
    }
    Polynom::degree = degree;
    for (int i = 0; i <= degree; i++) {
        stream >> coefs[i];
        if (!stream.good()) {
            throw std::invalid_argument("Incorrect coefficient");
        }
    }
    for (int i = degree + 1; i < maxdegree + 1; i++) {
        coefs[i] = 0;
    }
    return *this;
}

std::ostream& Polynom::Print(std::ostream& stream) const {
    for (int i = degree; i > 0; i--) {
        if (coefs[i] != 0) {
            if (coefs[i] != 1) {
                stream << coefs[i] << " * ";
            }
            stream << "x ^ " << i;
            if (coefs[i - 1] != 0) {
                stream << " + ";
            }
        }
    }
    if (coefs[0] != 0 || !degree) {
        stream << coefs[0];
    }
    stream << std::endl;
    return stream;
}

Polynom Polynom::add(Polynom b) const {
    int newdegree;
    if (degree > b.degree) {
        newdegree = degree;
    } else {
        newdegree = b.degree;
    }
    double arr[maxdegree];
    for (int i = 0; i <= newdegree; i++) {
        arr[i] = coefs[i] + b.coefs[i];
    }
    return Polynom(arr, newdegree);
}

double Polynom::PolynomValue(double x) const {
    double ans = 0, adding = 1;
    for (int i = 0; i <= degree; i++) {
        ans += coefs[i] * adding;
        adding *= x;
    }
    return ans;
}

Polynom Polynom::derivative() const {
    int newdegree = degree - 1;
    double arr[maxdegree];
    if (newdegree < 0) {
        arr[0] = 0;
        return Polynom(arr,0);
    }
    for (int i = 0; i <= newdegree; i++) {
        arr[i] = coefs[i + 1] * (i + 1);
    }
    return Polynom(arr, newdegree);
}

Polynom& Polynom::divideByXB(double &b) {
    if (!degree) {
        throw std::range_error("Degree of given polynom is 0");
    }
    int newdegree = degree - 1;
    double arr[maxdegree], highcoef = coefs[degree];
    for (int i = newdegree;  i >= 0; i--) {
        arr[i] = highcoef;
        highcoef = b * highcoef + coefs[i];
    }
    b = highcoef;
    degree = newdegree;
    for (int i = 0; i <= degree; i++) {
        coefs[i] = arr[i];
    }
    for (int i = degree + 1; i < maxdegree + 1; i++) {
        coefs[i] = 0;
    }
    return *this;
}

double Polynom::zeroBySegment(double begin, double end) const {
    double step = (end - begin) / 1000000; // 10 ^ 6
    double ans = begin - step;
    for (double i = begin; i < end; i += step) {
        if (this->PolynomValue(i) * this->PolynomValue(i + step) < 0) {
            if (ans > begin) {
                throw std::length_error("More than one zero! Decrease");
            }
            ans = i + step / 2;
        }
        if (this->PolynomValue(i) == 0) {
            if (ans > begin) {
                throw std::length_error("More than one zero! Decrease");
            }
            ans = i;
        }
    }
    if (this->PolynomValue(end) == 0) {
        if (ans > begin) {
            throw std::length_error("More than one zero! Decrease");
        }
        ans = end;
    }
    return ans;
}
