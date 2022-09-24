//
// Created by USER on 15.09.2022.
//

#include "dialog.h"
#include "sparse.h"
#include <iostream>
#include <limits>

using namespace sparse;
namespace dialog {
    int dMatInit(Sparse *mat) {
        int m = -1, n = -1;
        std::cout << "Initialising matrix. Print amount of lines, amount of columns." << std::endl;
        std::cin >> m >> n;
        if (m < 0 || n < 0) {
            throw "Amount is out of borders";
        }
        MatInit(mat, n, m);
        return 0;
    }

    int dInsert(Sparse *mat) {
        int i, j, value, amount = -1;
        std::cout << "Adding new values. Print amount of values." << std::endl;
        std::cin >> amount;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (amount <= 0 || amount > (mat->lines * mat->columns)) {
            throw "Amount is out of borders or equal to zero.";
        }
        for (int k = 0; k < amount; k++) {
            std::cout << "Adding new value. Print number of line, number of column and value." << std::endl;
            try {
                std::cin >> i >> j >> value;
                if (i < 0 || i > mat->lines || j < 0 || j > mat->columns) {
                    throw "Number of line/column is out of borders";
                }
                Insert(mat, i, j, value);
            } catch (const char *msg) {
                std::cout << msg << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                k--;
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