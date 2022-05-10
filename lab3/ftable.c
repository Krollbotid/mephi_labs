#include "ftable.h"
#include "stdio.h"
#include <string.h>

int writeTableStructure(Table *table) {
	if (!table || !(table->ks1) || !(table->infofile) || !(table->structurefile)) {
		return 1;
	}
	FILE *fp = fopen(table->infofile, "wb");
	if (!fp) {
		return 62;
	}
	KeySpace1 *ks1 = table->ks1;
	int count = 0;
	if (!(ks1->info)) {
		fwrite(&count, sizeof(int), 1, fp);
		fclose(fp);
		return 0;
	}
	//fwrite(table->infofile, sizeof(char), strlen(table->infofile), fp);
	if (fseek(fp, sizeof(int) * 1, SEEK_CUR)){
		fclose(fp);
		return 64;
	}
	while (ks1) {
		Item *item = ks1->info;
		while (item) {
			if (fwrite(item, sizeof(Item), 1, fp)){
				fclose(fp);
				return 65;
			}
			count++;
			item = item->next;
		}
		ks1 = ks1->next;
	}
	if (fseek(fp, 0, SEEK_SET)) {
		fclose(fp);
		return 64;
	}
	if (fwrite(&count, sizeof(int), 1, fp)) {
		fclose(fp);
		return 65;
	}
	fclose(fp);
	return 0;
}

int readTableStructure(Table *table) {
	if (!table || !(table->ks1) || !(table->infofile) || !(table->structurefile)) {
		return 1;
	}
	if (table->status == 1) {
		return 68;
	}
	FILE *fs = fopen(table->structurefile, "rb");
	if (!fs) {
		return 62;
	}
	int count, i;
	if (fread(&count, sizeof(int), 1, fs)) {
		fclose(fs);
		return 0;
	}
	//fwrite(table->infofile, sizeof(char), strlen(table->infofile), fp);
	for (i = 0; i < count; i++) {
		Item *item =  malloc(sizeof(Item));
		if (!item) {
			fclose(fs);
			return 2;
		}
		if (fread(item, sizeof(Item), 1, fs)){
			fclose(fs);
			return 66;
		}
		item->next = NULL;
		tabInsert(table, item->par, item, 0, NULL);
	}
	fclose(fs);
	return 0;
}

int rewriteTableData(Table *table) {
	if (!table || !(table->ks1) || !(table->infofile) || !(table->structurefile)) {
		return 1;
	}
	char s[] = "a;ldsh;ogm;alemto";
	FILE *fp = fopen(table->infofile, "rb"), *fcopy = fopen(s, "wb");
	if (!fp) {
		return 62;
	}
	KeySpace1 *ks1 = table->ks1;
	int status = 0;
	if (!(ks1->info)) {
		fwrite(&status, sizeof(int), 1, fcopy);
		fclose(fp);
		fclose(fcopy);
		rename(s, table->infofile);
		return 0;
	}
	fseek(fcopy, sizeof(int), SEEK_SET);
	while (ks1) {
		Item *item = ks1->info;
		while (item) {	
			fseek(fp, item->info, SEEK_SET);
			InfoType info;
			if (fread(&info, sizeof(InfoType), 1, fp)){
				fclose(fp);
				fclose(fcopy);
				return 65;
			}
			if (fwrite(&info, sizeof(InfoType), 1, fcopy)){
				fclose(fp);
				fclose(fcopy);
				return 65;
			}
			item = item->next;
		}
		ks1 = ks1->next;
	}
	if (fseek(fcopy, 0, SEEK_SET)) {
		fclose(fp);
		fclose(fcopy);
		return 64;
	}
	status = 1;
	if (fwrite(&status, sizeof(int), 1, fp)) {
		fclose(fp);
		fclose(fcopy);
		return 65;
	}
	fclose(fp);
	fclose(fcopy);
	rename(s, table->infofile);
	return 0;
}