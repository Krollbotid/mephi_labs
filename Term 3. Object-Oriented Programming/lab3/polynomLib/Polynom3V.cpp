//
// Created by USER on 31.10.2022.
//

#include "Polynom3V.h"
#include <limits>
#include <cstring>

namespace polynoms {
    Polynom::Polynom(const int degree) : degree(degree) {
        if (degree < 0) { throw std::invalid_argument("Degree cannot be negative!"); }
        coefs = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefs[i] = 1;
        }
    }

    Polynom::Polynom(const double arr[], const int degree) : degree(degree) {
        if (arr == nullptr) { throw std::invalid_argument("Incorrect array pf coefficients"); }
        if (degree < 0) { throw std::invalid_argument("Degree cannot be negative!"); }
        coefs = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefs[i] = arr[i];
        }
    }

    Polynom::Polynom(const Polynom& p) : degree(p.degree) {
        coefs = new double[degree + 1];
        for (int i = 0; i <= degree; i++) {
            coefs[i] = p.coefs[i];
        }
    }

    Polynom::Polynom(Polynom &&p) noexcept: degree(p.degree), coefs(p.coefs) {
        p.coefs = nullptr;
    }

    Polynom::~Polynom() {
        delete[] coefs;
    }

    char *Polynom::getStrPol() const {
        char num[25];
        size_t len = 0;
        for (int i = degree; i > 0; i--) {
            if (coefs[i] != 0) {
                if (coefs[i] != 1) {
                    sprintf(num, "%.2f * ", coefs[i]);
                    len += strlen(num);
                }
                sprintf(num, "x ^ %d", i);
                len += strlen(num);
                if (coefs[i - 1] != 0) {
                    len += 3;
                }
            }
        }
        if (coefs[0] != 0 || !degree) {
            sprintf(num, "%.2f", coefs[0]);
            len += strlen(num);
        }
        char* ans = new char[len + 1];
        len = 0;
        for (int i = degree; i > 0; i--) {
            if (coefs[i] != 0) {
                if (coefs[i] != 1) {
                    sprintf(ans + len, "%.2f * ", coefs[i]);
                    len = strlen(ans);
                }
                sprintf(ans + len, "x ^ %d", i);
                len = strlen(ans);
                if (coefs[i - 1] != 0) {
                    sprintf(ans + len, " + ");
                    len += 3;
                }
            }
        }
        if (coefs[0] != 0 || !degree) {
            sprintf(ans + len, "%.2f", coefs[0]);
        }
        return ans;
    }

    Polynom& Polynom::operator = (const Polynom& p) {
        degree = p.degree;
        delete[] coefs;
        coefs = new double[degree + 1];
        for (int i = 0; i <= p.degree; i++) {
            coefs[i] = p.coefs[i];
        }
        return *this;
    }

    Polynom& Polynom::operator = (Polynom&& p) noexcept {
        int tmp = degree;
        degree = p.degree;
        p.degree = tmp;
        double *ptr = coefs;
        coefs = p.coefs;
        p.coefs = ptr;
        return *this;
    }

    std::istream& operator >>(std::istream &stream, Polynom &p) {
        stream >> p.degree;
        stream.clear();
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (p.degree < 0) {
            throw std::invalid_argument("Incorrect degree");
        }
        delete[] p.coefs;
        p.coefs = new double[p.degree + 1];
        for (int i = 0; i <= p.degree; i++) {
            stream >> p.coefs[i];
            if (!stream.good()) {
                throw std::invalid_argument("Incorrect coefficient");
            }
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
        Polynom tmp, min(a), max(b);
        if (a.degree > b.degree) {
            max = a;
            min = b;
        }
        tmp = max;
        for (int i = 0; i <= min.degree; i++) {
            tmp.coefs[i] += min.coefs[i];
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
        if (degree < 1) {
            tmp = Polynom(0);
            tmp.coefs[0] = 0;
            return tmp;
        }
        tmp = Polynom(degree - 1);
        for (int i = 0; i <= tmp.degree; i++) {
            tmp.coefs[i] = coefs[i + 1] * (i + 1);
        }
        return tmp;
    }

    Polynom &Polynom::divideByXB(double &b) {
        if (!degree) {
            throw std::range_error("Degree of given polynom is 0");
        }
        double *arr = new double[degree], highcoef = coefs[degree];
        for (int i = degree - 1; i >= 0; i--) {
            arr[i] = highcoef;
            highcoef = b * highcoef + coefs[i];
        }
        b = highcoef;
        degree = degree - 1;
        delete[] coefs;
        coefs = arr;
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