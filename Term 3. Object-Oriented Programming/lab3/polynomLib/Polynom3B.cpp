//
// Created by USER on 28.10.2022.
//

#include "Polynom3B.h"

namespace polynoms {
    Polynom::Polynom(const int degree) : degree(degree) {
        if (degree > maxdegree) { throw std::invalid_argument("Too big degree!"); }
        if (degree < 0) { throw std::invalid_argument("Degree cannot be negative!"); }
        for (int i = 0; i <= degree; i++) {
            coefs[i] = 1;
        }
        for (int i = degree + 1; i < maxdegree + 1; i++) {
            coefs[i] = 0;
        }
    }

    Polynom::Polynom(const double arr[], const int degree) : degree(degree) {
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

    std::istream& operator >>(std::istream &stream, Polynom &p) {
        stream >> p.degree;
        stream.clear();
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (p.degree < 0 || p.degree > p.maxdegree) {
            throw std::invalid_argument("Incorrect degree");
        }
        for (int i = 0; i <= p.degree; i++) {
            stream >> p.coefs[i];
            if (!stream.good()) {
                throw std::invalid_argument("Incorrect coefficient");
            }
        }
        for (int i = p.degree + 1; i < p.maxdegree + 1; i++) {
            p.coefs[i] = 0;
        }
        return stream;
    }

    std::ostream& operator <<(std::ostream &stream, const Polynom &p) {
        for (int i = p.degree; i > 0; i--) {
            if (p.coefs[i] != 0) {
                if (p.coefs[i] != 1) {
                    stream << p.coefs[i] << " * ";
                }
                stream << "x ^ " << i;
                if (p.coefs[i - 1] != 0) {
                    stream << " + ";
                }
            }
        }
        if (p.coefs[0] != 0 || !p.degree) {
            stream << p.coefs[0];
        }
        stream << std::endl;
        return stream;
    }

    const Polynom operator +(const Polynom& a, const Polynom& b) {
        Polynom tmp;
        if (a.degree > b.degree) {
            tmp.degree = a.degree;
        } else {
            tmp.degree = b.degree;
        }
        for (int i = 0; i <= tmp.degree; i++) {
            tmp.coefs[i] = a.coefs[i] + b.coefs[i];
        }
        return tmp;
    }

    double Polynom::PolynomValue(double x) const {
        double ans = 0, adding = 1;
        for (int i = 0; i <= degree; i++) {
            ans += coefs[i] * adding;
            adding *= x;
        }
        return ans;
    }

    Polynom Polynom::operator ~ () const {
        Polynom tmp;
        tmp.degree = degree - 1;
        if (tmp.degree < 0) {
            tmp.degree = 0;
            tmp.coefs[0] = 0;
            return tmp;
        }
        for (int i = 0; i <= tmp.degree; i++) {
            tmp.coefs[i] = coefs[i + 1] * (i + 1);
        }
        return tmp;
    }

    Polynom &Polynom::divideByXB(double &b) {
        int newdegree = degree - 1;
        double arr[maxdegree], highcoef = coefs[degree];
        for (int i = newdegree; i >= 0; i--) {
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

    const bool operator == (const Polynom& a, const Polynom& b) {
        if (a.degree != b.degree) {
            return false;
        }
        for (int i = 0; i <= a.degree; i++) {
            if (a.coefs[i] != b.coefs[i]) {
                return false;
            }
        }
        return true;
    }
}