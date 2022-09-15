//
// Created by USER on 12.09.2022.
//
#include "dialog.h"
#include <iostream>

using namespace sparse;
using namespace dialog;
int main() {
    Sparse matrix;
    dMatInit(&matrix);
    std::cout<<matrix.lines;
    Clear(&matrix);
    return 0;
}