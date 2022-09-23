//
// Created by USER on 12.09.2022.
//
#include "dialog.h"
#include <iostream>
#include <limits>

using namespace sparse;
using namespace dialog;
int main() {
    Sparse *matrix;
    try {
         matrix = new Sparse;
    } catch (const std::bad_alloc& e) {
        std::cout << "Memory allocation error" << std::endl;
        return 0;
    }
    bool error = true;
    while (error) {
        try {
            dMatInit(matrix);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            dInsert(matrix);
            error = false;
        } catch (const char *msg) {
            std::cout << msg << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    Sparse *newmat;
    error = true;
    while (error) {
        try {
            newmat = MatCopy(matrix);
            dSortLine(newmat);
            error = false;
        } catch (const char *msg) {
            std::cout << msg << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    };
    MatPrint(matrix);
    MatPrint(newmat);
    Clear(matrix);
    Clear(newmat);
    return 0;
}