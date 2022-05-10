#include <stdlib.h>
#include "dtable.h"
#include "ftable.h"

int main() {
    int ks2size = 0;
    getsizeofks2(&ks2size);
	Table *table = (Table*) malloc(sizeof(Table));
	char **arr = errarray();
	if (!table) {
		errprint(2, arr);
		return 0;
	}
	int work = 1, errcode = tabInit(table, ks2size, "lab3b_INFODATA", "lab3b_STRUCTUREDATA"), id;
	if (errcode) {
		errprint(errcode, arr);
		return 0;
	}
	int (*Tablefuncs[]) (Table *table) = {dInsert, 
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
	while(work) {
		errcode = menu(&id);
		if (errcode) {
			errprint(errcode, arr);
			errcode = tabClear(table);
			if (errcode) {
				errprint(errcode, arr);
			}
			return 0;
		}
		if (!id) {
			break;
		}
		errcode = Tablefuncs[id - 1];
		if (errcode) {
            errprint(errcode, arr);
        }
	}
	errcode = tabClear(table);
	if (errcode) {
		errprint(errcode, arr);
	}
	free(arr);
	return 0;
}
