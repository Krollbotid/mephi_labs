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
        mat->start = nullptr;
        return 0;
    }

    int Insert(Sparse *mat, int i, int j, int v) {
        Cell *nc;
        try {
            nc = new Cell;
        } catch (const std::bad_alloc& e) {
            throw "Memory allocation error";
        }
        nc->next = nullptr;
        nc->number = j;
        nc->value = v;
        Line *ptr = mat->start, *ptrprev = nullptr;
        while (ptr && ptr->number < i) {
            ptrprev = ptr;
            ptr = ptr->next;
        }
        if (!ptrprev && !ptr) {
            Line *nl;
            try {
                nl = new Line;
            } catch (const std::bad_alloc& e) {
                delete nc;
                throw "Memory allocation error";
            }
            nl->next = nullptr;
            nl->number = i;
            nl->amount = 1;
            nl->sum = v;
            nl->start = nc;
            mat->start = nl;
        } else {
            if (ptr && ptr->number == i) {
                Cell *pt = ptr->start, *ptprev = nullptr;
                while (pt && pt->number < j) {
                    ptprev = pt;
                    pt = pt->next;
                }
                if (pt && pt->number == j) {
                    delete nc;
                    throw "Cell is already occupied!";
                } else {
                    ptprev->next = nc;
                    (ptr->amount)++;
                    (ptr->sum) += v;
                    nc->next = pt;
                }
            } else {
                Line *nl;
                try {
                    nl = new Line;
                } catch (const std::bad_alloc& e) {
                    delete nc;
                    throw "Memory allocation error";
                }
                nl->next = ptr;
                nl->number = i;
                nl->start = nc;
                nl->sum = v;
                nl->amount = 1;
                ptrprev->next = nl;
            }
        }
        return 0;
    }

    int MatPrint(Sparse *mat) {
        Line *ptr = mat->start;
        while (ptr) {
            Cell *cptr = ptr->start;
            std::cout << "Line " << ptr->number << ": ";
            while (cptr) {
                std::cout << cptr->value << "(" << cptr->number << ") ";
                cptr = cptr->next;
            }
            std::cout << std::endl;
            ptr = ptr->next;
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
        delete mat;
        return 0;
    }

    int CopyCells(Line *oline, Line *nline) {
        *nline = *oline;
        Cell *ptr = oline->start, *newprev = new Cell;
        nline->start = newprev;
        *newprev = *ptr;
        ptr = ptr->next;
        while (ptr) {
            Cell *nc = new Cell;
            *nc = *ptr;
            newprev->next = nc;
            newprev = nc;
            ptr = ptr->next;
        }
        return 0;
    }

    Sparse *MatCopy(Sparse *mat) {
        Sparse *nmat;
        try {
            nmat = new Sparse;
        } catch (const std::bad_alloc& e) {
            throw "Memory allocation error";
        }
        *nmat = *mat;
        Line *ptr = mat->start;
        if (!ptr) {
            return nmat;
        }
        Line *newprev;
        try {
            newprev = new Line;
            nmat->start = newprev;
            *newprev = *ptr;
            CopyCells(ptr, newprev);
            ptr = ptr->next;
            while (ptr) {
                Line *nl = new Line;
                *nl = *ptr;
                newprev->next = nl;
                newprev = nl;
                CopyCells(ptr, nl);
                ptr = ptr->next;
            }
        } catch (const std::bad_alloc& e) {
            Clear(nmat);
            throw "Memory allocation error";
        } catch (const char *msg) {
            Clear(nmat);
            throw msg;
        }
        return nmat;
    }

    int comp(const void *x1, const void *x2) {
        int ix1 = (*(Cell**)x1)->value, ix2 = (*(Cell**)x2)->value;
        if (ix1 > ix2){
            return 1;
        } else {
            if (ix1 == ix2){
                return 0;
            } else {
                return -1;
            }
        }
    }

    int revcomp(const void *x1, const void *x2) {
        return -1 * comp(x1, x2);
    }

    int SortLine(Sparse *mat, int i) {
        Line *line = mat->start;
        while (line && line->number < i) {
            line = line->next;
        }
        if (line && line->number == i) {
            Line *lptr = mat->start;
            int min = lptr->sum, max = min;
            while (lptr) {
                if (min > lptr->sum) {
                    min = lptr->sum;
                }
                if (max < lptr->sum) {
                    max = lptr->sum;
                }
                lptr = lptr->next;
            }
            if ((line->sum != min && line->sum != max) || min == max) {
                return 0;
            }
            Cell **arr, *ptr = line->start;
            int *numbers;
            try {
                arr = new Cell* [line->amount];
                numbers = new int [line->amount];
            } catch (const std::bad_alloc& e) {
                throw "Memory allocation error";
            }
            for (int k = 0; k < line->amount; k++) {
                arr[k] = ptr;
                numbers[k] = ptr->number;
                ptr = ptr->next;
            }

            if (line->sum == min) {
                qsort(arr, line->amount, sizeof(Cell*), comp);
            }
            if (line->sum == max) {
                qsort(arr, line->amount, sizeof(Cell*), revcomp);
            }

            line->start = *arr;
            for (int k = 0; k < line->amount - 1; k++) {
                (arr[k])->next = arr[k + 1];
                (arr[k])->number = numbers[k];
            }
            (arr[line->amount - 1])->next = nullptr;
            (arr[line->amount - 1])->number = numbers[line->amount - 1];
            delete[] arr;
            delete[] numbers;
        } else {
            throw "There's no line with such number";
        }
        return 0;
    }
}