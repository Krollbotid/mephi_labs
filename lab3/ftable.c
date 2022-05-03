#include "filed.h"

int fInsert(char *nameoffile, Item *item) {
	
}

int fRewrite(Table *table, char *nameoffile) {
	if (!nameoffile || !table || !(table->ks1)) {
		return 1;
	}
	FILE *fp = fopen(nameoffile, "wb");
	if (!fp) {
		return 61;
	}
	KeySpace1 *ks1 = table->ks1;
	if (!(ks1->info)) {
		fclose(fp);
		return 0;
	}
	while (ks1) {
		Item *item = ks1->info;
		while (item) {
			fwrite
			item = item->next;
		}
		ks1 = ks1->next;
	}
}
