#include <stdlib.h>
#include "dtree.h"

int main() {
	Tree tree = TreeInit();
	char **arr = errarray();
	const char (*menuoptions[]) = {
		"0.Exit",
		"1.Insert into tree.",
		"2.Remove node of tree.",
		"3.Go around tree and print to console elements which key is higher than entered key.",
		"4.Search elements in the tree by the key.",
		"5.Search min ranged (in centrilized going around) element from the element  with entered key.",
		"6.Print Tree by level.",
		"7.Read tree from file.",
		"8.Write tree to file for drawing graph.",
		"9.Timer",
		"10.Generate random tree.",
		"11.Write tree to file.",
		"12.Clear Tree"
	};
	int (*Treefuncs[]) (Tree *tree) = {
		NULL,
		DTreeInsert,
		DTreeDelete,
		DTreeGoAround,
		DTreeSearch,
		DTreeSpecialSearch,
		PrintTree,
		DReadTreefromFile,
		WriteTreeforGraph,
		DTimer,
		DRandGenTree,
		DWriteTreetoFile,
		TreeClear
	};
	const int N = sizeof(menuoptions) / sizeof(menuoptions[0]);
	int id = 1, errcode = 0;
	while(id) {
		errcode = menu(menuoptions, N, &id);
		if (errcode) {
			errprint(errcode, arr);
			errcode = TreeClear(&tree);
			if (errcode) {
				errprint(errcode, arr);
			}
			free(arr);
			return 0;
		}
		if (!id) {
			break;
		}
		errcode = Treefuncs[id](&tree);
		if (errcode) {
            errprint(errcode, arr);
        }
	}
	errcode = TreeClear(&tree);
	if (errcode) {
		errprint(errcode, arr);
	}
	ClearTREE(&tree);
	free(arr);
	return 0;
}
