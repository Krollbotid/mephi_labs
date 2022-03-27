#include <stdlib.h>
#include "ks2.h"

int keytohash(KeyType2 key, int msize2) {
    return (int) key % msize2;
    char *bytes = (void*) &key;
    int hash = 2147483647, i = 0;
    for (; i < sizeof(KeyType2); i++) {
        hash = 37 * hash + bytes[i];
    }
    return abs(hash) % msize2;
}

int ks2ArrCreate(int msize2) {
    if (!msize2) {
        return 1;
    }
    KeySpace2 *arr = (KeySpace2*) malloc(msize2 * sizeof(KeySpace2)), *ptr = arr;
    if (!arr) {
        return 2;
    }
    int i = 0;
    for (; i < msize2; i++) {
        ptr->next = NULL;
        ptr++;
    }
    return 0;
}

int ks2Insert(KeySpace2 *ks2, int msize2, Item *info, Item **ans) {
    if (!ks2 || !msize2 || !info) {
        return 1;
    }
    KeyType2 key = info->key2;
    KeySpace2 *ptr = ks2 + keytohash(key, msize2);
    while(ptr->next) {
        ptr = ptr->next;
        if (ptr->key == key) {
            if (ptr->info->key1 == info->key1) {
                *ans = ptr->info;
                return 0;
            }
            return 30;
        }
    }
    ptr->next = (KeySpace2*) malloc(sizeof(KeySpace2));
    if (!(ptr->next)) {
        return 2;
    }
    ptr->next->key = key;
    ptr->next->info = info;
    ptr->next->next = NULL;
    return 0;
}

int ks2Search(KeySpace2 *ks2, int msize2, KeyType2 key, Item **ans) {
    if (!ks2 || !msize2) {
        return 1;
    }
    KeySpace2 *ptr = ks2 + keytohash(key, msize2);
    do {
        ptr = ptr->next;
        if (!ptr) {
            return 404;
        }
    } while(key != ptr->key);
    return 0;
}