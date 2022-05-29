#ifndef DTREE_H
#define DTREE_H

#include "timing.h"

int DTreeInsert(Tree *tree);
int DTreeDelete(Tree *tree);
char **errarray();
int errprint(int errcode, char **arr);
int menu(const char *options[], const int N, int *id);
int DTreeGoAround(Tree *tree);
int DTreeSearch(Tree *tree);
int DTreeSpecialSearch(Tree *tree);
int DReadTreefromFile(Tree *tree);
int DTimer(Tree *tree);
int DRandGenTree(Tree *tree);
int DWriteTreetoFile(Tree *tree);

#endif
