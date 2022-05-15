#include <stdlib.h>
#include "dtable.h"
#include "ftable.h"
#include <stdio.h>

int main() {
    int ks2size = 0;
    getsizeofks2(&ks2size);
	Table *table = (Table*) malloc(sizeof(Table));
	char **arr = errarray();
	if (!table) {
		errprint(2, arr);
		free(arr);
		return 0;
	}
	int errcode = tabInit(table, ks2size, "lab3bINFODATA", "lab3bSTRUCTUREDATA");
	if (errcode) {
		errprint(errcode, arr);
		tabClear(table);
		free(arr);
		return 0;
	}
	errcode = filechecks(table->structurefile, table->infofile);
	if (errcode) {
		errprint(errcode, arr);
		tabClear(table);
		free(arr);
		return 0;
	}
	errcode = readTableStructure(table);
	if (errcode) {
		errprint(errcode, arr);
		tabClear(table);
		free(arr);
		return 0;
	}
	const char (*menuoptions[]) = {
		"0.Exit",
		"1.Insert into table.",
		"2.Remove out of table.",
		"3.Print table to console.",
		"4.Search elements by compound key.",
		"5.Search elements by non-compound key.",
		"6.Remove all elements by non-compound key.",
		"7.Recursive removing of elements by key1.",
		"8.Search all elements by parent key.",
		"9.Write structure of table into file.",
		"10.Read structure of table from file.",
		"11.Rewrite data of table into file."
	};
	int (*Tablefuncs[]) (Table *table) = {
		NULL,
		dInsert, 
		dRemove,
		tabPrint,
		dSearch,
		dSearchAny,
		dRemoveAny,
		dmultRemove,
		dparSearch,
		writeTableStructure,
		readTableStructure,
		rewriteTableData
	};
	const int N = sizeof(menuoptions) / sizeof(menuoptions[0]);
	int id = 1, NeedtoRewriteInfo = 0;
	while(id) {
		errcode = menu(menuoptions, N, &id);
		if (errcode) {
			errprint(errcode, arr);
			errcode = tabClear(table);
			if (errcode) {
				errprint(errcode, arr);
			}
			free(arr);
			return 0;
		}
		if (!id) {
			break;
		}
		NeedtoRewriteInfo = NeedtoRewriteInfo * (id != 11) + (id == 2 || id == 6 || id == 7);
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
