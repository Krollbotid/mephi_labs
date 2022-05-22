#include <stdlib.h>
#include "dtree.h"
#include <stdio.h>

int main() {
	Node *tree = NULL;
	char **arr = errarray();
	const char (*menuoptions[]) = {
		"0.Exit",
		"1.Insert into tree.",
		"2.Remove node of tree.",
		"3.Go around tree and print it to console.",
		"4.Search elements in the tree by the key.",
		"5.Search max ranged element from the element with entered key.",
		"6.Print Tree by level.",
		"7.Read tree from file."
	};
	int (*Treefuncs[]) (Node **tree) = {
		NULL,
		DTreeInsert,
		DTreeDelete,
		TreeGoAround,
		DTreeSearch,
		DTreeSpecialSearch,
		PrintTree,
		DReadTreefromFile
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
	free(arr);
	return 0;
}
