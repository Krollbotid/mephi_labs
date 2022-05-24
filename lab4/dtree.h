#ifndef DTREE_H
#define DTREE_H

#include "timing.h"

int DTreeInsert(Node **tree);
int DTreeDelete(Node **tree);
char **errarray();
int errprint(int errcode, char **arr);
int menu(const char *options[], const int N, int *id);
int DTreeSearch(Node **tree);
int DTreeSpecialSearch(Node **tree);
int DReadTreefromFile(Node **tree);
int DTimer(Node **tree);
int DRandGenTree(Node **tree);
int DWriteTreetoFile(Node **tree);

#endif
