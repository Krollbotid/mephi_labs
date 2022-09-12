#ifndef USEFUL_H
#define USEFUL_H

int strtoint(char *s); // return int from string if there are only digits, returns -1 in other case
void clear(int **mat, int amount, int *sizes);
int scalerand(const int start, const int end); // scales rand() [0; RANDMAX] to [start; end) if start<end, returns end-1 in other case

#endif