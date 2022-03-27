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
