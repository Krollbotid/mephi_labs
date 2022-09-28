//
// Created by USER on 24.09.2022.
//
#include "./ButaLib/buta.h"
#include <iostream>

using namespace butas;
int main() {
    Buta buta(1, 2, 3, 4);
    Point point(3);
    int fl1 = 1;
    char *s;
    while(fl1) {
        std::cout << "Your curve is:" << std::endl;
        s = buta.getPrintableEquation();
        std::cout << s << std::endl;
        delete [] s;
        std::cout << "area: " << buta.area() << std::endl;
        std::cout << "type of curve " << buta.getPrintableType() << std::endl;
        int fl2 = 1;
        while(fl2){
            std::cout << "Enter phi for calculate value r(phi) or press ctrl+Z to quit:" << std::endl;
            double phi, r;
            std::cin >> phi;
            fl2 = std::cin.good();
            if(!fl2)
                continue;
            try{
                r = buta.distance(phi);
                std::cout << "r = " << r << std::endl;
            }
            catch(std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        double m, c;
        std::cout << "Enter new x, y, m and c to continue or press ctrl+Z to quit:" << std::endl;
        std::cin >> point.x >> point.y >> m >> c;
        if(std::cin.good()){
            buta.setP(point);
            try{
                buta.setM(m);
                buta.setC(c);
            }
            catch (std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
            }
        }
        else
            fl1 = 0;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}