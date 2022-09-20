//
// Created by USER on 15.09.2022.
//

#include "dialog.h"
#include "sparse.h"
#include <iostream>

using namespace sparse;
namespace dialog {
    int dMatInit(Sparse *mat) {
        int m, n;
        std::cout << "Initialising matrix. Print amount of lines, amount of columns." << std::endl;
        std::cin >> m >> n;
        MatInit(mat, n, m);
        return 0;
    }

    int dInsert(Sparse *mat) {
        int i, j, value, amount;
        std::cout << "Adding new values. Print amount of values." << std::endl;
        std::cin >> amount;
        for (int k = 0; k < amount; k++) {
            std::cout << "Adding new value. Print number of line, number of column and value." << std::endl;
            try {
                std::cin >> i >> j >> value;
                if (i < 0 || i > mat->lines || j < 0 || j > mat->columns) {
                    throw "Number of line/column is out of borders";
                }
            } catch (const char *msg) {
                std::cout << msg << "Entering values stopped" << std::endl;
                return 0;
            }
            try {
                Insert(mat, i, j, value);
            } catch (const char *msg) {
                std::cout << msg;
            }
        }
        return 0;
    }

    int dSortLine(Sparse *mat) {
        int i = -1;
        std::cout << "Sorting line. Print number of line." << std::endl;
        std::cin >> i;
        if (i < 0 || i > mat->lines) {
            throw "Number of line/column is out of borders";
        }
        SortLine(mat, i);
        return 0;
    }
}