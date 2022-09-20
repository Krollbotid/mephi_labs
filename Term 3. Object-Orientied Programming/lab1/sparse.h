//
// Created by USER on 13.09.2022.
//

#ifndef MEPHI_LABS_SPARSE_H
#define MEPHI_LABS_SPARSE_H

namespace sparse {

    typedef struct Cell {
        int value, number;
        Cell *next;
    } Cell;

    typedef struct Line {
        int number, amount, sum;
        Cell *start;
        Line *next;
    } Line;

/*
for idiots like author of this code: matrix A_m_n where m - number of lines, n - number of columns
            \j/
A=  (a_1_1  ...     a_1_n)
i-> (...    a_i_j   ...  )
    (a_m_1  ...     a_m_n)

 */

    typedef struct Sparse {
        int lines, columns;
        Line *start;
    } Sparse;

    int MatInit(Sparse *mat, int n, int m);
    int Insert(Sparse *mat, int i, int j, int v);
    Sparse *MatCopy(Sparse *mat);
    int Clear(Sparse *mat);
    int MatPrint(Sparse *mat);
    int SortLine(Sparse *mat, int i);
} //namespace end

#endif MEPHI_LABS_SPARSE_H
