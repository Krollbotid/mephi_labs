//
// Created by USER on 24.09.2022.
//

#ifndef LAB2_BUTA_H
#define LAB2_BUTA_H
#define PI 3.14159

namespace butas {
    enum types {
        ellipticPedal = 0,
        hyperbolicPedal,
        Circles,
        BernoulliLemniscate
    };

    struct Point {
        double x, y;
        Point(double x0 = 0, double y0 = 0) : x(x0), y(y0) {}
    };

    class Buta { // (x^2+y^2)^2-(2m^2+c)*x^2+(2m^2-c)*y^2=0
    private:
        Point p; // center
        double m, c; // parameters of curve
    public:
        Buta(const Point &p0, double m = 1, double c = 2);
        Buta(double m = 1, double c = 2, double x0 = 0, double y0 = 0);

        Buta& setP(const Point &p0);
        Buta& setM(double M);
        Buta& setC(double C);

        Point getP() const;
        double getM() const;
        double getC() const;

        types getType() const;
        const char* getPrintableType() const;
        double area() const;
        double getFirstCoefficient() const; // returns a from r^2 = a * (cos(phi))^2 - b * (sin(phi))^2
        double getSecondCoefficient() const; // returns b from r^2 = a * (cos(phi))^2 - b * (sin(phi))^2
        double distance(const double phi) const;
        char* getPrintableEquation() const;
    };
}

#endif //LAB2_BUTA_H
