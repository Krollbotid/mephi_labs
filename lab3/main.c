#include <stdlib.h>
#include "dtable.h"

int main() {
    int ks2size = 0;
    getsizeofks2(&ks2size);
	Table *table = (Table*) malloc(sizeof(Table));
	char **arr = errarray();
	if (!table) {
		errprint(2, arr);
		return 0;
	}
	int work = 1, errcode = tabInit(table, ks2size), id;
	if (errcode) {
		errprint(errcode, arr);
		return 0;
	}
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
		switch(id) {
			case 1:
                errcode = dInsert(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
				break;
			case 2:
                errcode = dRemove(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
				break;
			case 3:
				errcode = tabPrint(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
				break;
			case 4:
				errcode = dSearch(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
				break;
			case 5:
				errcode = dSearchAny(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
				break;
            case 6:
                errcode = dRemoveAny(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
                break;
            case 7:
                errcode = dmultRemove(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
                break;
            case 8:
                errcode = dparSearch(table);
                if (errcode) {
                    errprint(errcode, arr);
                }
                break;
			case 0:
				work = 0;
				break;
		}
	}
	errcode = tabClear(table);
	if (errcode) {
		errprint(errcode, arr);
	}
	free(arr);
	return 0;
}
