#include <stdlib.h>
#include <string.h>
#include "useful.h"

char *readline(char *s) {
	printf("%s", s);
	char buf[80 + 1] = {0}; //#define bufsiz 80
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = scanf("%80[^\n]",buf);
		if (n < 0){
			if(!ans){
				return NULL;
			}
		} else if (n > 0) {
			int buf_len = strlen(buf);
			int str_len = len + buf_len;
			ans = (char*) realloc(ans, (str_len + 1) * sizeof(char));
			strncpy(ans+len, buf, buf_len);
			len = str_len;
		} else {
			scanf("%*c");
		}
	} while (n > 0);
	if (len > 0){
		ans[len] = '\0';
	} else {
		ans = (char*) calloc(1, sizeof(char));
	}
	return ans;
}

char *freadline(FILE *fp) {
	char buf[80 + 1] = {0}; //#define bufsiz 80
	char *ans = NULL;
	int len = 0, n = 0;
	do {
		n = fscanf(fp, "%80[^\n]",buf);
		if (n < 0){
			if(!ans){
				return NULL;
			}
		} else if (n > 0) {
			int buf_len = strlen(buf);
			int str_len = len + buf_len;
			ans = (char*) realloc(ans, (str_len + 1) * sizeof(char));
			strncpy(ans+len, buf, buf_len);
			len = str_len;
		} else {
			fscanf(fp, "%*c");
		}
	} while (n > 0);
	if (len > 0){
		ans[len] = '\0';
	} else {
		ans = (char*) calloc(1, sizeof(char));
	}
	return ans;
}

int scalerand(const int start, const int end) {
    if (end > start){
        return start + (rand() %(end-start));
    } else {
        return end-1;
    }
}