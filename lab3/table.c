#include <string.h>
#include <stdlib.h>
#include "table.h"
#include <stdio.h>

int tabInit(Table *table, int msize2) {
	if (!table) {
		return 1;
	}
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
	return 0;
}

int tabInsert(Table *table, KeyType1 par, Item *info) {
	if (!table) {
		return 1;
	}
	Item *dubl2 = NULL, *dubl1 = NULL;
	int errcode = 0;
	errcode = ks2Insert(table->ks2, table->msize2, info, &dubl2);
	if (errcode) {
		return errcode;
	}
	errcode = ks1Insert(&(table->ks1), par, info, &dubl1);
	if (errcode) {
		ks2Remove(table->ks2, info->key2, table->msize2, &dubl2, 0);
		return errcode;
	}
	if (dubl1 != dubl2) {
		return 6;
	}
    if (dubl1) {
        errcode = ItemReleaseInsert(dubl1, info);
    } else {
        info->release = 1;
    }
	return errcode;
}

int tabPrint(Table *table) {
    if (!table) {
        return 1;
    }
    printf("Size of KeySpace2:%d. Printing table:\n", table->msize2);
    if (!(table->ks1)) {
        printf("Table is empty.\n");
        return 0;
    }
    int errcode = ks1Print(table->ks1);
    if (errcode) {
        return errcode;
    }
	printf("\n");
    errcode = ks2Print(table->ks2, table->msize2);
    return errcode;
}


int tabSearch(Table *table, KeyType1 key1, KeyType2 key2) {
	if (!table || !key1) {
		return 1;
	}
	Item *ans;
	int errcode = ks2Search(table->ks2, table->msize2, key2, &ans);
	if (errcode) {
		return errcode;
	}
	Table *cop = (Table*) malloc(sizeof(Table));
	if (!cop) {
		return 2;
	}
	errcode = tabInit(cop, 1);
	if (errcode) {
        return errcode;
    }
	KeySpace1 *ptr = (KeySpace1*) ans->p1;
	while (ans) {
		InfoType *info = (InfoType*) malloc(sizeof(InfoType));
		if (!info) {
			return 2;
		}
		Item *item = (Item*) malloc(sizeof(Item));
		if (!item) {
            free(info);
			return 2;
		}
		memcpy(info, ans->info, sizeof(InfoType));
		memcpy(item, ans, sizeof(Item));
		item->info = info;
		ans = ans->next;
		errcode = tabInsert(cop, 0, item);
	    if (errcode) {
        	return errcode;
        }
	}
	errcode = tabPrint(cop);
    if (errcode) {
        return errcode;
    }
	errcode = tabClear(cop);
	return errcode;
}

int tabRemove(Table *table, KeyType1 key1, KeyType2 key2, int mode) {
	if (!table) {
		return 1;
	}
	Item *toremove1 = NULL, *toremove2 = NULL;
	int errcode = ks2Remove(table->ks2, key2, table->msize2, &toremove2, mode);
	if (errcode) {
		return errcode;
	}
	errcode = ks1Remove(&(table->ks1), key1, &toremove1, mode);
	if (errcode) {
		return errcode;
	}
	if (toremove1 != toremove2) {
		return 6;
	}
	errcode = ItemDelete(toremove1);
    return errcode;
}

int tabSearchAny(Table *table, KeyType1 key1, KeyType2 key2, int mode) {// 1 - key1, 2 - key2
	if (!table) {
		return 1;
	}
	Table *cop = (Table*) malloc(sizeof(Table));
	int errcode = tabInit(cop, 1);
	if (errcode) {
		tabClear(cop);
		return errcode;
	}
	Item *ans;
	switch (mode) {
		case 1: {
			errcode = ks1Search(table->ks1, key1, &ans);
			if (errcode) {
				tabClear(cop);
				return errcode;
            			}
			break;
		}
        	case 2: {
			errcode = ks2Search(table->ks2, table->msize2, key2, &ans);
            		if (errcode) {
				tabClear(cop);
                		return errcode;
            		}
			break;
		}
	}
	KeySpace1 *ptr = (KeySpace1*) ans->p1;
	while (ans) {
		InfoType *info = (InfoType*) malloc(sizeof(InfoType));
		if (!info) {
			tabClear(cop);
			return 2;
		}
		Item *item = (Item*) malloc(sizeof(Item));
		if (!item) {
			free(info);
			tabClear(cop);
			return 2;
		}
		memcpy(info, ans->info, sizeof(InfoType));
		memcpy(item, ans, sizeof(Item));
		item->info = info;
		ans = ans->next;
		errcode = tabInsert(cop, 0, item);
	    if (errcode) {
		tabClear(cop);
        	return errcode;
        }
	}
	errcode = tabPrint(cop);
    if (errcode) {
	tabClear(cop);
        return errcode;
    }
	errcode = tabClear(cop);
	return errcode;
}

int parSearch(Table *table, KeyType1 par) {
    if (!table) {
        return 1;
    }
    Table *cop = (Table*) malloc(sizeof(Table));
    int errcode = tabInit(cop, 1);
    if (errcode) {
	tabClear(cop);
        return errcode;
    }
    KeySpace1 *ptr = table->ks1;
    Item *ans;
    while (ptr) {
        ans = ptr->info;
        if (ptr->par == par) {
            while (ans) {
                InfoType *info = (InfoType*) malloc(sizeof(InfoType));
                if (!info) {
			tabClear(cop);
                    return 2;
                }
                Item *item = (Item*) malloc(sizeof(Item));
                if (!item) {
                    free(info);
			tabClear(cop);
                    return 2;
                }
                memcpy(info, ans->info, sizeof(InfoType));
                memcpy(item, ans, sizeof(Item));
                item->info = info;
                ans = ans->next;
                errcode = tabInsert(cop, 0, item);
                if (errcode) {
			tabClear(cop);
                    return errcode;
                }
            }
        }
        ptr = ptr->next;
    }
	errcode = tabPrint(cop);
	if (errcode) {
		tabClear(cop);
		return errcode;
	}
	errcode = tabClear(cop);
	return errcode;
}

int recDelete(Table *table, KeySpace1 *ks1) {
    if (!ks1) {
        return 0;
    }
	KeySpace1 *ptr = table->ks1;
	while (ptr) {
		if (ptr->par == ks1->key) {
			recDelete(table, ptr);
		}
		if (ptr) {
			ptr = ptr->next;
		}
	}
    Item *toremove1 = NULL, *toremove2 = NULL;
    int errcode = ks2Remove(table->ks2, ks1->info->key2, table->msize2, &toremove2, 1);
    if (errcode) {
        return errcode;
    }
    errcode = ks1Remove(&(table->ks1), ks1->key, &toremove1, 1);
    if (errcode) {
        return errcode;
    }
    if (toremove1 != toremove2) {
        return 6;
    }
    errcode = ItemDelete(toremove1);
    return errcode;
}

int multRemove(Table *table, KeyType1 key1) {
    if (!table) {
        return 1;
    }
    KeySpace1 *ptr = table->ks1;
    while (ptr) {
        if (ptr->key == key1) {
            break;
        }
        ptr = ptr->next;
        if (!ptr) {
            return 4;
        }
    }
    int errcode = recDelete(table, ptr);
    return errcode;
}
