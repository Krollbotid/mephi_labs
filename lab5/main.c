#include <stdlib.h>
#include "dgraph.h"

int main() {
	Graph graph;
	GraphInit(&graph);
	char **arr = errarray();
	const char (*menuoptions[]) = {
		"0.Exit",
		"1.Add node to graph.",
		"2.Add bound between nodes to graph.",
		"3.Remove node from graph.",
		"4.Remove bound between nodes from graph.",
		"5.Print graph",
		"6.Clear graph",
		"7.Draw graph",
		"8.Read graph from file",
		"9.Find path from one node to other node.",
		"10.Find shortest path (Dijkstra) from one node to other node.",
		"11.Find shortest path (Floyd) from one node to other node."
	};
	int (*Treefuncs[]) (Graph *graph) = {
		NULL,
		DGraphAddNode,
		DGraphAddBound,
		DGraphDeleteNode,
		DGraphDeleteBound,
		GraphPrintMatrix,
		GraphClear,
		DrawGraph,
		DReadGraphfromFile,
		DPathfinder,
		DShortestPathfinder,
		DShortestPathfinderFloyd
	};
	const int N = sizeof(menuoptions) / sizeof(menuoptions[0]);
	int id = 1, errcode = 0;
	while(id) {
		errcode = menu(menuoptions, N, &id);
		if (errcode) {
			errprint(errcode, arr);
			errcode = GraphClear(&graph);
			if (errcode) {
				errprint(errcode, arr);
			}
			free(arr);
			return 0;
		}
		if (!id) {
			break;
		}
		errcode = Treefuncs[id](&graph);
		if (errcode) {
            errprint(errcode, arr);
        }
	}
	errcode = GraphClear(&graph);
	if (errcode) {
		errprint(errcode, arr);
	}
	free(arr);
	return 0;
}
