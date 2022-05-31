#ifndef DGRAPH_H
#define DGRAPH_H

#include "graph.h"

char **errarray();
int errprint(int errcode, char **arr);
int menu(const char *options[], const int N, int *id);
int DGraphAddNode(Graph *graph);
int DGraphAddBound(Graph *graph);
int DGraphDeleteNode(Graph *graph);
int DGraphDeleteBound(Graph *graph);
int DReadGraphfromFile(Graph *graph);
int DPathfinder(Graph *graph);
int DShortestPathfinder(Graph *graph);
int DShortestPathfinderFloyd(Graph *graph);

#endif
