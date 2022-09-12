#ifndef GRAPH_H
#define GRAPH_H

#include "useful.h"

typedef struct Info {
    char *name;
    int x,
        y;
} Info;

typedef struct Graph {
    int **matrix;
    Info *infos;
    int size;
} Graph;

void GraphInit(Graph *graph);
int GraphAddNode(Graph *graph, Info *info);
int GraphAddBound(Graph *graph, Info *info1, Info *info2, int mode);
int GraphDeleteNode(Graph *graph, Info *info, int mode);
int GraphDeleteBound(Graph *graph, Info *info1, Info *info2, int mode);
int GraphPrintMatrix(Graph *graph);
int GraphClear(Graph *graph);
int DrawGraph(Graph *graph);
int ReadGraphfromFile(Graph *graph, char *name);
int Pathfinder(Graph *graph, Info *start, Info *end, int mode);
int SigiRoivenAkaDijkstra(Graph *graph, Info *start, Info *end, int mode);
int Floyd(Graph *graph, Info *start, Info *end, int mode);

#endif
