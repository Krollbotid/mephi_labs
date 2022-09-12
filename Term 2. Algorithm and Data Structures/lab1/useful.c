#include <string.h>
#include <stdlib.h>
#include <string.h>

int strtoint(char *s, int *err){
    if(s != NULL){
        char digits[10] = "0123456789";
        int i = 0, chfound = 0, minusfound = 0, ans = 0;
        if (s[i] == '-') {
            minusfound = 1;
            i = 1;
        }
        for (; i < strlen(s); i++){
            int isdigit = 0, j = 0;
            for (j = 0; j < 10; j++){
                if (s[i] == digits[j]){
                    isdigit = 1;
                    ans = ans * 10 + j;
                }
            }
            if (!isdigit){
                chfound = 1;
                break;
            }
        }
        if (minusfound) {
            ans *= -1;
        }
        if (chfound){
            *err = 1;
            return -1;
        } else {
            return ans;
        }
    } else {
        *err = 1;
        return -1;
    }
}

void clear(int **mat, int amount, int *sizes) {
    if (!mat || !sizes) {
        return;
    }
    int i = 0, **ptr = mat;
    for (; i < amount; i++) {
        free(*ptr);
        ptr++;
    }
    free(mat);
    free(sizes);
    return;
}

int scalerand(const int start, const int end){
    if (end > start){
        return start + (rand() %(end-start));
    } else {
        return end - 1;
    }
}
