#include <stdlib.h>
#include "dtable.h"

int main() {
	Table *table = (Table*) malloc(sizeof(Table));
	if (!table) {
		errprint(2);
		return 0;
	}
	int work = 1, errcode = tabInit(table, 40), id;
	if (errcode) {
		errprint(errcode);
		return 0;
	}
	while(work) {
		errcode = menu(&id);
		if (errcode) {
			errprint(errcode);
			errcode = tabClear(table);
			if (errcode) {
				errprint(errcode);
			}
			return 0;
		}
		switch(id) {
			case 1:
				dInsert(table);
				break;
			case 2:
				dRemove(table);
				break;
			case 3:
				tabPrint(table);
				break;
			case 0:
				work = 0;
				break;
		}
	}
	errcode = tabClear(table);
	if (errcode) {
		errprint(errcode);
	}
	return 0;
}
