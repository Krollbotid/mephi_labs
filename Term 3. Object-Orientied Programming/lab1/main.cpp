//
// Created by USER on 12.09.2022.
//
#include "dialog.h"
#include <iostream>

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
    dMatInit(matrix);
    while (1) {
        try {
            dInsert(matrix);
        } catch (const char *msg) {
            std::cout << msg << std::endl;
        }
        break;
    }
    Sparse *newmat;
    try {
        newmat = MatCopy(matrix);
        dSortLine(newmat);
    } catch (const char *msg) {
        std::cout << msg << std::endl;
    }
    MatPrint(matrix);
    MatPrint(newmat);
    Clear(matrix);
    Clear(newmat);
    return 0;
}