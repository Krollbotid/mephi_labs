#ifndef FILED_H
#define FILED_H

#include "table.h"

int writeTableStructure(Table *table);
int readTableStructure(Table *table);
int rewriteTableData(Table *table);
#endif
