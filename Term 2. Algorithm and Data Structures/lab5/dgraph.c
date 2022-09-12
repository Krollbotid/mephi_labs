#include "dgraph.h"
#include <stdlib.h>
#include <string.h>

int getInt(int start, int end, int *ans) {// get int in [start, end)
	char *errmsg = "";
	int k = 0;
	do {
		printf(errmsg);
		errmsg = "Incorrect input. Please try again.";
		k = scanf("%d", ans);
        if (k < 0) {
            return 3;
        }
		scanf("%*[^\n]");
		scanf("%*c");
	} while (!k || *ans >=end || *ans < start);
	return 0;
}

int getCoords(Info *ans) {
	char *errmsg = "";
	int k = 0;
	do {
		printf(errmsg);
		errmsg = "Incorrect input. Please try again.\n";
		k = scanf("%d/%d", &(ans->x), &(ans->y));
        if (k < 0) {
            return 3;
        }
		scanf("%*[^\n]");
		scanf("%*c");
	} while (k < 2);
	return 0;
}

int getIntUnsized(int *ans) {//get int > 0
	char *errmsg = "";
	int k = 0;
	do {
		printf(errmsg);
		errmsg = "Incorrect input. Please try again.";
		k = scanf("%u", ans);
        if (k < 0) {
            return 3;
        }
		scanf("%*[^\n]");
		scanf("%*c");
	} while (!k || (*ans < 1));
	return 0;
}

int menu(const char *options[], const int N, int *id) {
    printf("Menu:\n");
	int i;
	for (i = 0; i < N; i++) {
		puts(options[i]);
	}
	printf("Print menu option number:");
	int errcode = getInt(0, N, id);
	if (errcode) {
		return errcode;
	}
	return 0;
}

char **errarray() {
	char **arr = (char**) malloc((23 + 1) * sizeof(char*));
	arr[0] = "Success";
	arr[1] = "Zero value in non-zero variable";
	arr[2] = "Out of memory";
	arr[3] = "End of file";
	arr[4] = "Not found";
	arr[11] = "Graph - one of nodes hasn't been found";
	arr[12] = "Graph - there is node with such coords already";
	arr[13] = "Graph - there is node with such name already";
	arr[14] = "Graph - error during reading";
	arr[15] = "Graph - can't open file";
	arr[16] = "Graph - graph isn't empty - can't read";
    arr[17] = "Graph - graph is empty";
	arr[21] = "Dialog - out of errmessages array";
	arr[22] = "Dialog - incorrect file name";
	arr[23] = "Dialog - incorrect input. Please try again.";
	return arr;
}

int errprint(int errcode, char **arr) {
	if (errcode > 23) {
		errcode = 21;
	}
	printf("%s\n", arr[errcode]);
	return 0;
}

int DGraphAddNode(Graph *graph) {
	if (!graph) {
		return 1;
	}
    Info info;
	info.name = readline("Write name of node:");
	if (!(info.name) || !(*(info.name))) {
		return 23;
	}
    printf("Print coords of node in following format: x/y\n");
    int errcode = getCoords(&info);
	if (errcode) {
        free(info.name);
		return errcode;
	}
    errcode = GraphAddNode(graph, &info);
	return errcode;
}

int DGraphDeleteNode(Graph *graph) {
	if (!graph) {
		return 1;
	}
    printf("Print 1 if you want to delete node by it's coords or 2 if you want to delete node by it's name\n");
    int id;
    int errcode = getInt(1, 3, &id);
	if (errcode) {
		return errcode;
	}
    Info info;
    info.name = NULL;
    if (id == 2) {
        info.name = readline("Write name of node:");
	    if (!(info.name) || !(*(info.name))) {
	    	return 23;
	    }
    } else {
        printf("Print coords of node in following format: x/y\n");
        int errcode = getCoords(&info);
	    if (errcode) {
	    	return errcode;
	    }
    }
	errcode = GraphDeleteNode(graph, &info, id);
    free(info.name);
	return errcode;
}

int DGraphAddBound(Graph *graph) {
	if (!graph) {
		return 1;
	}
    printf("Print 1 if you want to add bound by nodes' coords or 2 if you want to add bound by nodes' names\n");
    int id;
    int errcode = getInt(1, 3, &id);
	if (errcode) {
		return errcode;
	}
    Info info1, info2;
    if (id == 2) {
        info1.name = readline("Write name of node:");
	    if (!(info1.name) || !(*(info1.name))) {
	    	return 23;
	    }
        info2.name = readline("Write name of node:");
	    if (!(info2.name) || !(*(info2.name))) {
	    	return 23;
	    }
    } else {
        info1.name = NULL;
        info2.name = NULL;
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info1);
	    if (errcode) {
	    	return errcode;
	    }
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info2);
	    if (errcode) {
	    	return errcode;
	    }
    }
	errcode = GraphAddBound(graph, &info1, &info2, id);
    free(info1.name);
    free(info2.name);
	return errcode;
}

int DGraphDeleteBound(Graph *graph) {
	if (!graph) {
		return 1;
	}
    printf("Print 1 if you want to delete bound by nodes' coords or 2 if you want to delete bound by nodes' names\n");
    int id;
    int errcode = getInt(1, 3, &id);
	if (errcode) {
		return errcode;
	}
    Info info1, info2;
    if (id == 2) {
        info1.name = readline("Write name of node:");
	    if (!(info1.name) || !(*(info1.name))) {
	    	return 23;
	    }
        info2.name = readline("Write name of node:");
	    if (!(info2.name) || !(*(info2.name))) {
	    	return 23;
	    }
    } else {
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info1);
	    if (errcode) {
	    	return errcode;
	    }
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info2);
	    if (errcode) {
	    	return errcode;
	    }
    }
	errcode = GraphDeleteBound(graph, &info1, &info2, id);
    free(info1.name);
    free(info2.name);
	return errcode;
}

int DReadGraphfromFile(Graph *graph) {
	//char *name = "test.txt";
	char *name = readline("Please write name of file:");
	if (!name) {
		return 22;
	}
	int errcode = ReadGraphfromFile(graph, name);
	free(name);
	return errcode;
}

int DPathfinder(Graph *graph) {
    if (!graph) {
		return 1;
	}
    printf("Print 1 if you want to mark nodes bynodes' coords or 2 if you want to mark nodes by nodes' names\n");
    int id;
    int errcode = getInt(1, 3, &id);
	if (errcode) {
		return errcode;
	}
    Info info1, info2;
    if (id == 2) {
        info1.name = readline("Write name of node:");
	    if (!(info1.name) || !(*(info1.name))) {
	    	return 23;
	    }
        info2.name = readline("Write name of node:");
	    if (!(info2.name) || !(*(info2.name))) {
	    	return 23;
	    }
    } else {
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info1);
	    if (errcode) {
	    	return errcode;
	    }
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info2);
	    if (errcode) {
	    	return errcode;
	    }
    }
	errcode = Pathfinder(graph, &info1, &info2, id);
    free(info1.name);
    free(info2.name);
	return errcode;
}

int DShortestPathfinder(Graph *graph) {
    if (!graph) {
		return 1;
	}
    printf("Print 1 if you want to mark nodes by nodes' coords or 2 if you want to mark nodes by nodes' names\n");
    int id;
    int errcode = getInt(1, 3, &id);
	if (errcode) {
		return errcode;
	}
    Info info1, info2;
    if (id == 2) {
        info1.name = readline("Write name of node:");
	    if (!(info1.name) || !(*(info1.name))) {
	    	return 23;
	    }
        info2.name = readline("Write name of node:");
	    if (!(info2.name) || !(*(info2.name))) {
	    	return 23;
	    }
    } else {
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info1);
	    if (errcode) {
	    	return errcode;
	    }
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info2);
	    if (errcode) {
	    	return errcode;
	    }
    }
	errcode = SigiRoivenAkaDijkstra(graph, &info1, &info2, id);
    free(info1.name);
    free(info2.name);
	return errcode;
}

int DShortestPathfinderFloyd(Graph *graph) {
    if (!graph) {
		return 1;
	}
    printf("Print 1 if you want to mark nodes by nodes' coords or 2 if you want to mark nodes by nodes' names\n");
    int id;
    int errcode = getInt(1, 3, &id);
	if (errcode) {
		return errcode;
	}
    Info info1, info2;
    if (id == 2) {
        info1.name = readline("Write name of node:");
	    if (!(info1.name) || !(*(info1.name))) {
	    	return 23;
	    }
        info2.name = readline("Write name of node:");
	    if (!(info2.name) || !(*(info2.name))) {
	    	return 23;
	    }
    } else {
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info1);
	    if (errcode) {
	    	return errcode;
	    }
        printf("Print coords of node in following format: x/y\n");
        errcode = getCoords(&info2);
	    if (errcode) {
	    	return errcode;
	    }
    }
	errcode = Floyd(graph, &info1, &info2, id);
    free(info1.name);
    free(info2.name);
	return errcode;
}

/*int DWriteTreetoFile(Graph *graph) {
	//char *name = "test.txt";
	char *name = readline("Please write name of file:");
	if (!name) {
		return 22;
	}
	int errcode = WriteTreetoFile(graph, name);
	free(name);
	return errcode;
}

int DRandGenTree(Graph *graph) {
	int minlen, maxlen, amount;
	printf("Print min length of keys from [1; 20]:");
	getInt(1, 21, &minlen);
	printf("Print max length of keys from [1; 20]:");
	getInt(1, 21, &maxlen);
	printf("Print amount of elements:");
	getIntUnsized(&amount);
	randGenTree(graph, minlen, maxlen, amount);
	return 0;
}*/
