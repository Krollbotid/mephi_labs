//
// Created by USER on 13.09.2022.
//

#include "sparse.h"
#include <iostream>
#include <cstdlib>

namespace sparse {

    int MatInit(Sparse *mat, int n, int m) {
        mat->columns = n;
        mat->lines = m;
        mat->start = NULL;
        return 0;
    }

    int Insert(Sparse *mat, int i, int j, int v) {
        Cell *nc = new Cell;
        nc->next = NULL;
        nc->number = v;
        nc->value = j;
        Line *ptr = mat->start, *ptrprev = NULL;
        while (ptr && ptr->number < i) {
            ptrprev = ptr;
            ptr = ptr->next;
        }
        if (!ptrprev) {
            Line *nl = new Line;
            nl->next = NULL;
            nl->number = i;
            nl->start = nc;
            mat->start = nl;
        } else {
            if (ptr->number == i) {
                Cell *pt = ptr->start, *ptprev = NULL;
                while (pt && pt->number < j) {
                    ptprev = pt;
                    pt = pt->next;
                }
                if (pt->number == j) {
                    throw "Cell is already occupied!";
                } else {
                    ptprev->next = nc;
                    nc->next = pt;
                }
            } else {
                Line *nl = new Line;
                nl->next = ptr;
                nl->number = i;
                nl->start = nc;
                ptrprev->next = nl;
            }
        }
        return 0;
    }

    int Clear(Sparse *mat) {
        Line *ptr = mat->start, *ptrprev;
        while (ptr) {
            ptrprev = ptr;
            ptr = ptr->next;
            Cell *pt = ptrprev->start, *ptprev;
            while (pt) {
                ptprev = pt;
                pt = pt->next;
                delete ptprev;
            }
            delete ptrprev;
        }
        return 0;
    }
}