#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"
#include "ind.h"
#include <limits.h>

int GetNodeExistance(Info *info, Graph *graph) {
    if (!graph || !info) {
        return 1;
    }
    int i;
    Info *ptr = graph->infos;
    for (i = 0; i < graph->size; i++) {
        if (ptr->x == info->x && ptr->y == info->y)  {
            return 12;
        }
        if (!(strcmp(info->name, ptr->name))) {
            return 13;
        }
        ptr++;
    }
    return 0;
}

int GetNodeNumbyCoords(Info *info, Graph *graph) {
    int i;
    Info *ptr = graph->infos;
    for (i = 0; i < graph->size; i++) {
        if (ptr->x == info->x && ptr->y == info->y) {
            return i;
        }
        ptr++;
    }
    return -1;
}

int GetNodeNumbyName(char *name, Graph *graph) {
    int i;
    Info *ptr = graph->infos;
    for (i = 0; i < graph->size; i++) {
        if (!(strcmp(name, ptr->name))) {
            return i;
        }
        ptr++;
    }
    return -1;
}

int GetNodeNum(Info *info, Graph *graph, int mode) {  //  mode 0 - both, mode 1 - coords, mode 2 - name
    if (!mode) {
        int k = GetNodeNumbyCoords(info, graph);
        if (k != GetNodeNumbyName(info->name, graph)) {
            return -1;
        }
        return k;
    } else if (mode == 1) {
        return GetNodeNumbyCoords(info, graph);
    }
    return GetNodeNumbyName(info->name, graph);
}

void GraphInit(Graph *graph) {
    graph->infos = NULL;
    graph->matrix = NULL;
    graph->size = 0;
    return;
}

int GraphAddNode(Graph *graph, Info *info) {
    if (!graph){
        return 1;
    }
    int errcode = GetNodeExistance(info, graph) ;
    if (errcode) {
        return errcode;
    }
    graph->size = graph->size + 1;
    int i, **ptr = graph->matrix, *ptr2;
    for (i = 0; i < graph->size - 1; i++) {
        *ptr = (int*) realloc((*ptr), sizeof(int) * graph->size);
        ptr2 = *ptr;
        ptr2[graph->size - 1] = 0;
        ptr++;
    }
    graph->matrix = (int**) realloc(graph->matrix, sizeof(int*) * graph->size);
    ptr = graph->matrix;
    ptr[graph->size - 1] = (int*) calloc(graph->size, sizeof(int));
    graph->infos = (Info*) realloc(graph->infos, sizeof(Info) * graph->size);
    (graph->infos)[graph->size - 1] = *info;
    return 0;
}

int GraphAddBound(Graph *graph, Info *info1, Info *info2, int mode) {  //  sometime I'll remember that i - row and j - column
    if (!graph){
        return 1;
    }
    int num1 = GetNodeNum(info1, graph, mode), num2 = GetNodeNum(info2, graph, mode);
    printf("%d %d\n", num1, num2);
    if (num1 < 0 || num2 < 0) {
        return 11;
    }
    (graph->matrix)[num1][num2] = 1;
    return 0;
}

int GraphDeleteNode(Graph *graph, Info *info, int mode) {
    if (!graph){
        return 1;
    }
    int num = GetNodeNum(info, graph, mode);
    if (num < 0) {
        return 4;
    }
    Info *ptri = graph->infos;
    free((ptri + num)->name);
    memmove(ptri + num, ptri + (num + 1), sizeof(Info) * (graph->size - num - 1));
    graph->infos = (Info*) realloc(ptri, sizeof(Info) * (graph->size - 1));
    int i, **ptr = graph->matrix, *ptr2;
    for (i = 0; i < graph->size; i++) {
        ptr2 = *ptr;
        memmove(ptr2 + num, ptr2 + (num + 1), sizeof(int) * (graph->size - num - 1));
        *ptr = (int*) realloc(ptr2, sizeof(int) * (graph->size - 1));
        ptr++;
    }
    ptr = graph->matrix;
    free(*(ptr + num));
    memmove(ptr + num, ptr + (num + 1), sizeof(int*) * (graph->size - num - 1));
    graph->matrix = (int**) realloc(ptr, sizeof(int*) * (graph->size - 1));
    graph->size = graph->size - 1;
    return 0;
}

int GraphDeleteBound(Graph *graph, Info *info1, Info *info2, int mode) {  //  sometime I'll remember that i - row and j - column
    if (!graph){
        return 1;
    }
    int num1 = GetNodeNum(info1, graph, mode), num2 = GetNodeNum(info2, graph, mode);
    if (num1 < 0 || num2 < 0) {
        return 11;
    }
    int **ptr = graph->matrix;
    ptr[num1][num2] = 0;
    return 0;
}

int GraphPrintMatrix(Graph *graph) {
	if (!graph) {
		return 1;
	}
    int size = graph->size, i;
    Info *ptr = graph->infos;
    printf("Graph has nodes:\n");
    for (i = 0; i < size; i++) {
        printf("Node %d: Name:\"%s\"; X-coord:%d; Y-coord:%d.\n", i, ptr->name, ptr->x, ptr->y);
        ptr++;
    }
    printf("Matrix of Adjacency:\n\t");
    for (i = 0; i < size; i++) {
        printf("\t%d",i);
    }
    printf("\n");
    int **ptr2 = graph->matrix, *ptr3, j;
    Info *ptri1 = graph->infos, *ptri2;
    for (i = 0; i < size; i++) {
        printf("\t%d", i);
        ptr3 = *ptr2;
        ptri2 = graph->infos;
        for (j = 0; j < size; j++) {
            double len = -1;
            if (*ptr3) {
                int dx = ptri1->x - ptri2->x, dy = ptri1->y - ptri2->y;
                len = dx * dx + dy * dy;
            }
            printf("\t%6.2f", sqrt(len));
            ptri2++;
            ptr3++;
        }
        printf("\n");
        ptri1++;
        ptr2++;
    }
    return 0;
}

int GraphClear(Graph *graph) {
    if (!graph || !(graph->size)) {
        return 0;
    }
    int i, size = graph->size, **ptr = graph->matrix;
    Info *ptr2 = graph->infos;
    for (i = 0; i < size; i++) {
        free(*ptr);
        free(ptr2->name);
        ptr2++;
        ptr++;
    }
    free(graph->matrix);
    free(graph->infos);
    graph->infos = NULL;
    graph->matrix = NULL;
    graph->size = 0;
    return 0;
}

int ReadGraphfromFile(Graph *graph, char *name) {
    if (!graph) {
        return 1;
    }
    if (graph->size) {
        return 16;
    }
	FILE *fp = fopen(name, "r");
	if (!fp) {
		return 15;
	}
    int size, i;
    if (fscanf(fp, "%d", &size) < 1) {
        fclose(fp);
        return 14;
    }
	fscanf(fp, "%*[^\n]");
	fscanf(fp, "%*c");
    for (i = 0; i < size; i++) {
        Info info;
        if (fscanf(fp, "%d %d", &(info.x), &(info.y)) < 2) {
            fclose(fp);
            return 14;
        }
		fscanf(fp, "%*c");
	    info.name = freadline(fp);
	    if (!(info.name) || !(*(info.name))) {
            fclose(fp);
	    	return 14;
	    }
        int errcode = GraphAddNode(graph, &info);
        if (errcode) {
            free(info.name);
            fclose(fp);
	        return errcode;
        }
    }
    graph->size = size;
    int j, **ptr = graph->matrix;
    for (i = 0; i < size; i++) {
        int bound, *ptr2 = *ptr;
        for (j = 0; j < size; j++) {
            if (fscanf(fp, "%d", &bound) < 0) {
                fclose(fp);
                return 14;
            }
            if (bound) {
                *ptr2 = 1;
            }
            ptr2++;
        }
		fscanf(fp, "%*c");
        ptr++;
    }
    fclose(fp);
    return 0;
}

int DrawGraph(Graph *graph) {
	if (!graph) {
		return 1;
	}
	if (!(graph->size)) {
		return 17;
	}
	FILE *fp = fopen("graph.dot", "w");
	if (!fp) {
		return 15;
	}
	fprintf(fp, "digraph G {\n");
    int i, j, **ptr = graph->matrix, *ptr2;
    Info *ptr3 = graph->infos;
    for (i = 0; i < graph->size; i++) {
        fprintf(fp, "\t%d [label=\"%s\\n(%d, %d)\"];\n", i,  ptr3->name, ptr3->x, ptr3->y);
        ptr3++;
    }
    ptr3 = graph->infos;
    for (i = 0; i < graph->size; i++) {
        ptr2 = *ptr;
        for (j = 0; j < graph->size; j++) {
            if (*ptr2) {
                int dx = (ptr3 + i)->x - (ptr3 + j)->x, dy = (ptr3 + i)->y - (ptr3 + j)->y;
                fprintf(fp, "\t%d -> %d [label=\"%6.2f\"];\n", i, j, sqrt((double) (dx * dx + dy * dy)));
            }
            ptr2++;
        }
        ptr++;
    }
	fprintf(fp, "}");
	fclose(fp);
	system("dot -Tpng graph.dot -o graph.png");
	return 0;
}

int RecPrintPath(Graph *graph, int start, int v, int *pred) {
    if (start == v) {
        printf ("-> %d:%s ", v, ((graph->infos)[v]).name);
    } else {
        if (pred[v] < 0) {
            printf("Path doesn't exist\n");
        } else {
            RecPrintPath(graph, start, pred[v], pred);
            printf ("-> %d:%s ", v, ((graph->infos)[v]).name);
        }
    }
    return 0;
}

int Pathfinder(Graph *graph, Info *start, Info *end, int mode) {
    int nums = GetNodeNum(start, graph, mode), nume = GetNodeNum(end, graph, mode);
	if (nums < 0 || nume < 0) {
                return 4;
        }
    queue Q = newqueue(1);  // colors: 0 - white, 1 - gray, 2 - black
    int *color = (int*) malloc(sizeof(int) * graph->size), *d = (int*) malloc(sizeof(int) * graph->size), *pred = (int*) malloc(sizeof(int) * graph->size), *ptrc = color, *ptrd = d, *ptrp = pred, i;
    for (i = 0; i < graph->size; i++) {
        *ptrc = 0;
        *ptrd = INT_MAX;
        *ptrp = -1;
        ptrc++;
        ptrd++;
        ptrp++;
    }
    color[nums] = 1;
    d[nums] = 0;
    qpush(&Q, nums);
    int *row;
    while (Q.last) {
        int u = getfirst(&Q);
        row = (graph->matrix)[u];
        for (i = 0; i < graph->size; i++) {
            if (*row && !(color[i])) {
                color[i] = 1;
                d[i] = d[i] + 1;
                pred[i] = u;
                qpush(&Q, i);
            }
            row++;
        }
        color[u] = 2;
        qpop(&Q);
    }
    RecPrintPath(graph, nums, nume, pred);
    printf("\n");
    free(d);
    free(color);
    free(pred);
    return 0;
}

double Weight(Info *info1, Info *info2) {
    int dx = info1->x -info2->x, dy = info1->y - info2->y;
    return sqrt((double) (dx * dx + dy * dy));
}

int SigiRoivenAkaDijkstra(Graph *graph, Info *start, Info *end, int mode) {
    int s = GetNodeNum(start, graph, mode), numend = GetNodeNum(end, graph, mode);
	if (s < 0 || numend < 0) {
                return 4;
        }
    queue Q = newqueue(1);  // colors: 0 - white, 1 - gray, 2 - black
    int *pred = (int*) malloc(sizeof(int) * graph->size), *ptrp = pred, i, *S = (int*) malloc(sizeof(int) * graph->size);
    double *d = (double*) malloc(sizeof(double) * graph->size),  *ptrd = d;
    for (i = 0; i < graph->size; i++) {
        *ptrd = INT_MAX;
        *ptrp = -1;
        ptrd++;
        ptrp++;
        qpush(&Q, i);
    }
    d[s] = 0;
    int *row, *ptr = S;
    while (Q.last) {
        int u = ExtractMin(&Q, d);
        *ptr = u;
        row = (graph->matrix)[u];
        for (i = 0; i < graph->size; i++) {
            int w = Weight(graph->infos + i, graph->infos + u);
            if (*row && d[i] > d[u] + w) {
                d[i] = d[u] + w;
                pred[i] = u;
            }
            row++;
        }
        ptr++;
    }
    RecPrintPath(graph, s, numend, pred);
    printf("\nLength of path:%6.2f\n", d[numend]);
    free(d);
    free(pred);
    free(S);
    return 0;
}

/*void makepred(int *pred, int **pi, int size, int s, int numend, int start, int end) {
	int i;
	for (i = 0; i < size; i++) {
        	if (i != start) {
        		pred[i] = pi[start][i];
        	}
    	}
	pred[start] = s;
	pred[s] = -1;
	if (numend != end) {
		pred[numend] = end;
	}
	return;
}*/

int Floyd(Graph *graph, Info *start, Info *end, int mode) {
    int i, j, s = GetNodeNum(start, graph, mode), numend = GetNodeNum(end, graph, mode), **pi = (int**) malloc(sizeof(int*) * graph->size);  // pi is number of last inner node in shortest path from i to j
	if (s < 0 || numend < 0) {
		free(pi);
		return 4;
	}
    double **d = (double**) malloc(sizeof(double*) * graph->size); // d is len of shortest path from i to j
    Info *row = graph->infos, *column;
    int **matrix = graph->matrix, *mrow;
    for (i = 0; i < graph->size; i++) {
        d[i] = (double*) malloc(sizeof(double) * graph->size);
        pi[i] = (int*) malloc(sizeof(int) * graph->size);
        column = graph->infos;
        mrow = *matrix;
        for (j = 0; j < graph->size; j++) {
            if (*mrow) {
                d[i][j] = Weight(row, column);
            } else {
                d[i][j] = -1;
            }
            if (i == j || d[i][j] < 0) {
                pi[i][j] = -1;
            } else {
                pi[i][j] = i;
            }
            column++;
            mrow++;
        }
        matrix++;
    }
    int k;
    double **prevd = (double**) malloc(sizeof(double*) * graph->size);
    int **previ = (int**) malloc(sizeof(int*) * graph->size);
    for (i = 0; i < graph->size; i++) {
        prevd[i] = (double*) malloc(sizeof(double) * graph->size);
        previ[i] = (int*) malloc(sizeof(int) * graph->size);
    }
    for (k = 0; k < graph->size; k++) {
        for (i = 0; i < graph->size; i++) {
            memcpy(previ[i], pi[i], sizeof(int) * graph->size);
            memcpy(prevd[i], d[i], sizeof(double) * graph->size);
        }
        for (i = 0; i < graph->size; i++) {
            for (j = 0; j < graph->size; j++) {
                if ((prevd[i][j] < 0 || prevd[i][j] > prevd[i][k] + prevd[k][j]) && prevd[i][k] >= 0 && prevd[k][j] >= 0) {
                    pi[i][j] = previ[k][j];
                    d[i][j] = prevd[i][k] + prevd[k][j];
                }
            }
        }
    }
	/*double min1 = (double) INT_MAX, min2 = min1, min3 = min1, x1 = -1, x2 = -1, x3 = -1, y1 = -1, y2 = -1, y3 = -1;
	for (i = 0; i < graph->size; i++) {
		for (j = 0; j < graph->size; j++) {
			double len = -1;
			if (i != s && j != numend && d[i][j] * d[s][i] * d[j][numend] > 0) {
				len =  d[i][j] + d[s][i] + d[j][numend];
			}
			if (len >= 0 && len < min1 && len < min2 && len < min3) {
				if (min1 >= min2 && min1 >= min3) {
					min1 = len;
					x1 = i;
					y1 = j;
				} else if (min2 >= min3) {
					min2 = len;
					x2 = i;
					y2 = j;
				} else {
					min3 = len;
					x3 = i;
					y3 = j;
				}
			}
		}
	}
	int *pred1 = (int*) malloc(sizeof(int) * graph->size), *pred2 = (int*) malloc(sizeof(int) * graph->size), *pred3 = (int*) malloc(sizeof(int) * graph->size);*/
	int *pred = (int*) malloc(sizeof(int) * graph->size);
	/*if (min1 != INT_MAX) {
	makepred(pred1, pi, graph->size, s, numend, x1, y1);
	}
	if (min2 != INT_MAX) {
        	makepred(pred2, pi, graph->size, s, numend, x2, y2);
	}
	if (min3 != INT_MAX) {
        	makepred(pred3, pi, graph->size, s, numend, x3, y3);
	}*/
    for (i = 0; i < graph->size; i++) {
        if (i == s) {
            pred[i] = -1;
        } else {
            pred[i] = pi[s][i];
        }
    }
    pred[s] = -1;
    RecPrintPath(graph, s, numend,  pred);
    printf("\nLength of path:%6.2f\n", d[s][numend]);
	/*if (min1 >= 0) {
    RecPrintPath(graph, s, numend,  pred1);
    printf("\nLength of path:%6.2f\n", min1);
    }
        if (min2 >= 0) {
    RecPrintPath(graph, s, numend,  pred2);
    printf("\nLength of path:%6.2f\n", min2);
    }
        if (min3 >= 0) {
    RecPrintPath(graph, s, numend,  pred3);
    printf("\nLength of path:%6.2f\n", min3);
    }*/
    for (i = 0; i < graph->size; i++) {
        free(d[i]);
        free(pi[i]);
        free(prevd[i]);
        free(previ[i]);
    }
    free(d);
    free(pi);
    free(prevd);
    free(previ);
    free(pred);
	/*free(pred1);
	free(pred2);
	free(pred3);*/
    return 0;
}
