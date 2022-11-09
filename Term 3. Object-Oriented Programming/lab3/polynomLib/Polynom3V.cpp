//
// Created by USER on 31.10.2022.
//

#include "Polynom3V.h"
#include <limits>
#include <cstring>
#include <cmath>

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
        for (int i = degree; i >= 0; i--) {
            if (coefs[i] == 0) {
                continue;
            }
            if (i != degree || coefs[i] < 0) {
                if (coefs[i] > 0) {
                    len += 3;
                } else {
                    if (i == degree) {
                        len++;
                    } else {
                        len += 3;
                    }
                }
            }
            if (fabs(coefs[i]) != 1 || i == 0){
                sprintf(num, "%.2f", fabs(coefs[i]));
                len += strlen(num);
            }
            if (i != 0) {
                len++;
            }
            if (i > 1) {
                sprintf(num, "%d", i);
                len += 3 + strlen(num);
            }
        }
        char *ans = new char[len + 1];
        len = 0;
        for (int i = degree; i >= 0; i--) {
            if (coefs[i] == 0) {
                continue;
            }
            if (i != degree || coefs[i] < 0) {
                if (coefs[i] > 0) {
                    sprintf(ans + len, " + ");
                    len += 3;
                } else {
                    if (i == degree) {
                        sprintf(ans + len, "-");
                        len++;
                    } else {
                        sprintf(ans + len, " - ");
                        len += 3;
                    }
                }
            }
            if (fabs(coefs[i]) != 1 || i == 0){
                sprintf(ans + len, "%.2f", fabs(coefs[i]));
                len = strlen(ans);
            }
            if (i != 0) {
                sprintf(ans + len, "x");
                len++;
            }
            if (i > 1) {
                sprintf(ans + len, " ^ %d", i);
                len = strlen(ans);
            }
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
        if (!stream.good()) {
            throw std::invalid_argument("Incorrect degree");
        }
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

    std::ostream& operator <<(std::ostream& stream, const Polynom& p) {
        for (int i = p.degree; i >= 0; i--) {
            if (p.coefs[i] == 0) {
                continue;
            }
            if (i != p.degree || p.coefs[i] < 0) {
                if (p.coefs[i] > 0) {
                    stream << " + ";
                } else {
                    if (i == p.degree) {
                        stream << "-";
                    } else {
                        stream << " - ";
                    }
                }
            }
            if (fabs(p.coefs[i]) != 1 || i == 0){
                stream << fabs(p.coefs[i]);
            }
            if (i != 0) {
                stream << "x";
            }
            if (i > 1) {
                stream << " ^ " << i;
            }
        }
        return stream;
    }

    const Polynom operator +(const Polynom& a, const Polynom& b) {
        Polynom tmp;
        int min;
        if (a.degree > b.degree) {
            tmp = a;
            min = b.degree;
        } else {
            tmp = b;
            min = a.degree;
        }
        for (int i = 0; i <= min; i++) {
            if (a.degree > b.degree) {
                tmp.coefs[i] += b.coefs[i];
            } else {
                tmp.coefs[i] += a.coefs[i];
            }
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
            b = coefs[0];
            coefs[0] = 0;
            return *this;
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
                    throw std::length_error("More than one zero! Decrease segment!");
                }
                ans = i + step / 2;
            }
            if (this->PolynomValue(i) == 0) {
                if (ans > begin) {
                    throw std::length_error("More than one zero! Decrease segment!");
                }
                ans = i;
            }
        }
        if (this->PolynomValue(end) == 0) {
            if (ans > begin) {
                throw std::length_error("More than one zero! Decrease segment!");
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