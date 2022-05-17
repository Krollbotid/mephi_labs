#include <stdlib.h>
#include "dtree.h"
#include <stdio.h>

int main() {
	int ks2size = 0;
	Node *tree = NULL;
	char **arr = errarray;
	char (*menuoptions[]) = {
		"0.Exit",
		"1.Insert into tree.",
		"2.Remove node of tree.",
		"3.Go around tree and print it to console."
	};
	int (*Tablefuncs[]) (Node **tree) = {
		NULL,
		DTreeInsert,
		DTreeDelete,
		TreeGoAround,
	};
	const int N = sizeof(menuoptions) / sizeof(menuoptions[0]);
	int id = 1;
	while(id) {
		errcode = menu(menuoptions, N, &id);
		if (errcode) {
			errprint(errcode, arr);
			errcode = TreeClear(tree);
			if (errcode) {
				errprint(errcode, arr);
			}
			free(arr);
			return 0;
		}
		if (!id) {
			break;
		}
		errcode = Tablefuncs[id](table);
		if (errcode) {
            errprint(errcode, arr);
        }
	}
	if (NeedtoRewriteInfo) {
		errcode = rewriteTableData(table);
	}
	if (errcode) {
		errprint(errcode, arr);
	}
	errcode = writeTableStructure(table);
	if (errcode) {
		errprint(errcode, arr);
	}
	errcode = tabClear(table);
	if (errcode) {
		errprint(errcode, arr);
	}
	free(arr);
	return 0;
}
