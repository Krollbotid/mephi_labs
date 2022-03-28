#include "table.h"

int tabInit(Table *table, int msize2) {
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int errcode = 0;
    errcode = ks1InitCreate(&ks1);
    if (errcode) {
        return errcode;
    }
    errcode = ks2ArrCreate(msize2, &ks2);
    if (errcode) {
        ks1Clear(ks1, 1);
        return errcode;
    }
    table->ks1 = ks1;
    table->ks2 = ks2;
    table->msize2 = msize2;
    return 0;
}

int tabClear(Table *table) {
    int errcode = 0;
    errcode = ks1Clear(table->ks1, 1);
    if (errcode) {
        return errcode;
    }
    errcode = ks2Clear(table->ks2, table->msize2, 0);
    if (errcode) {
        return errcode;
    }
    free(table);
}

int tableInsert(Table *table, KeyType1 par, Item *info) {
	Item *dubl2 = NULL, *dubl1 = NULL;
	int errcode = 0;
	errcode = ks2Insert(table->ks2, table->msize2, info, &dubl1);
	if (errcode) {
		return errcode;
	}
	errcode = ks1Insert(table->ks1, par, info, &dub1);
	if (errcode) {
		ks2Remove(table->ks2, info->key2, table->msize2, &dubl2, 0);
		return errcode;
	}
	if (dubl1 != dubl2) {
		return 666;
	}
	errcode = ItemReleaseInsert(dubl, info);
	if (errcode) {
		return errcode;
	}
	return 0;
}
