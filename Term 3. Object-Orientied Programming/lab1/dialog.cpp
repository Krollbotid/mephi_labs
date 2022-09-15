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
        int i, j, value;
        std::cout << "Adding new value. Print number of line, number of column and value." << std::endl;
        std::cin >> i >> j >> value;
        Insert(mat, i, j, value);
        return 0;
    }
}