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
	if (!table) {
		return 0;
	}
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

int tabInsert(Table *table, KeyType1 par, Item *info) {
	if (!table) {
		return 1;
	}
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

int tabSearch(Table *table, KeyType1 key1, KeyType2 key2, Item **ans) {
	if (!table || !ans || !key1) {
		return 1;
	}
	int errcode = ks2Search(table->ks2, table->msize2, key2, ans);
	if (errcode) {
		return errcode;
	}
}

int tabRemove(Table *table, KeyType1 key1, KeyType2 key2) {
	if (!table || !key1) {
		return 1;
	}
	Item *toremove1 = NULL, *toremove2 = NULL;
	int errcode = ks2Remove(table->ks2, key2, table->msize2, &toremove2, 0);
	if (errcode) {
		return errcode;
	}
	errcode = ks1Remove(table->ks1, key1, &toremove1, 0);
	if (errcode) {
		return errcode;
	}
	if (toremove1 != toremove2) {
		return 666;
	}
	errcode = ItemDelete(toremove);
	if (errcode) {
		return errcode;
	}
	return 0;
}

int tabSearchAny(Table *table, KeyType1 key1, KeyType2 key2, int mode, Table *copied) {// 1 - key1, 2 - key2, 3 - key1&key2
	if (!table || !key1 || !copied) {
		return 1;
	}
	int errcode = tabInit(copied, table->msize2);
	if (errcode) {
		return errcode;
	}
	Item **ans;
	switch (mode) {
		case 1: {
			ks1Search(table->key1, key1
		}
	}
}
