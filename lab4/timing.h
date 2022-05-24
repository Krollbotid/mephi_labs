#ifndef TIMING_H
#define TIMING_H

#include "tree.h"

int randGenTree(Node **tree, int minlength, int maxlength, int amount);
int InsertTimer(int dotnumber, int amount, int multiplier);
int DeleteTimer(int dotnumber, int amount, int multiplier);
int GoAroundTimer(int dotnumber, int amount, int multiplier);
int SearchTimer(int dotnumber, int amount, int multiplier);
int SpecialSearchTimer(int dotnumber, int amount, int multiplier);

#endif