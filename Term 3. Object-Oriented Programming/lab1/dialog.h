//
// Created by USER on 15.09.2022.
//

#ifndef MEPHI_LABS_DIALOG_H
#define MEPHI_LABS_DIALOG_H

#include "sparse.h"
namespace dialog {
    int dMatInit(sparse::Sparse *mat);
    int dInsert(sparse::Sparse *mat);
    int dSortLine(sparse::Sparse *mat);
}

#endif //MEPHI_LABS_DIALOG_H
