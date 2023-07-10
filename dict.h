#ifndef DICT_H__
#define DICT_H__
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct dictentry {
    char *k;
    char *v;
} dictentry;

typedef struct dict {
    size_t n;
    size_t m;
    dictentry *kv;
    int (*add)(struct dict *, const char *, const char *);
    void (*del)(struct dict *, const char *);
    char *(*val)(struct dict *, const char *);
} dict;




#define dictdestroy(D) dictdestroy_impl(&D)




// Return the (hypothetical) index of an element via binary search
static int64_t dicthypoindex(dict *D, const char *key) {
    int64_t min = 0;
    int64_t max = D->n;
    int64_t mid = min + (max-min)/2;
    int cmp;

    while (min < max) {
        cmp = strcmp(key, D->kv[mid].k);
        if (cmp == 0) {  // Midpoint of search space is right on
            return mid;
        } else if (cmp < 0) { // Too high, narrow to lower half
            if (mid>min) max = mid-1; else max = min;
            mid = min + (max-min)/2;
        } else if (0 < cmp) { // Too low, narrow to upper half
            if (mid<max) min = mid+1; else min = max;
            mid = min + (max-min)/2;
        }
    }

    while (mid < D->n && strcmp(key, D->kv[mid].k) > 0) mid++;

    return mid;
}




// Allocate more memory if we've used it all
static void dictmaybegrow(dict *D) {
    dictentry *allocation;

    if (D->n >= D->m) { // n (number of elements) >= m (memory allocated)
        // Try reallocating more memory
        allocation = realloc(D->kv, D->m * 2 * sizeof(dictentry));
        // If successful, use new allocation (and track how much we now have)
        if (allocation) {
            D->kv = allocation;
            D->m = D->m * 2;
        }
    }
}




static inline int dictadd(dict *D, const char *key, const char *val) {
    int64_t i = dicthypoindex(D, key);
    int64_t dst = i + 1;
    char *tmpkey;
    char *tmpval;
    int Dhasentries = (D->n != 0) ? 1 : 0;
    int keyvalid = (key != NULL) ? 1 : 0;


    if (i < D->n && key != NULL && D->kv[i].k != NULL && !strcmp(D->kv[i].k, key)) {
        tmpval = strdup(val);
        if (!tmpval) return 0;
        free(D->kv[i].v);
        D->kv[i].v = tmpval;
    } else {
        dictmaybegrow(D);
        tmpkey = strdup(key);
        tmpval = strdup(val);
        if (!tmpkey || !tmpval) { free(tmpkey); free(tmpval); return 0; }
        // From the insertion points, move everything down to make room.
        memmove(&D->kv[dst], &D->kv[i], (D->n - (size_t)i) * sizeof(dictentry));
        D->kv[i].k = tmpkey;
        D->kv[i].v = tmpval;
        D->n++;
    }

    return 1;
}




static inline char *dictval(dict *D, const char *key) {
    int64_t i = dicthypoindex(D, key);
    if (i < D->n && !strcmp(D->kv[i].k, key)) {
        return D->kv[i].v;
    }
    return NULL;
}




static inline void dictdel(dict *D, const char *key) {
    int64_t i = dicthypoindex(D, key);
    int64_t src = i + 1;

    if (!strcmp(D->kv[i].k, key)) {
        free(D->kv[i].k);
        free(D->kv[i].v);
        memmove(&D->kv[i], &D->kv[src], (D->n - (size_t)src) * sizeof(dictentry));
        D->n--;
    }
}




static inline void dictdestroy_impl(dict **d) {
    int64_t i;
    dict *D = *d;
    for (i=0; i < D->n; i++) {
        free(D->kv[i].k);
        free(D->kv[i].v);
    }
    free(D->kv);
    free(D);
    D = NULL;
}




static inline void dictprint(dict *D) {
    int64_t i;
    for (i = 0; i < D->n; i++) {
        printf("%14s:  \"%s\"\n", D->kv[i].k, D->kv[i].v);
    }
}




static inline dict *dictnew(void) {
    dict *D = malloc(sizeof *D);

    if (D) {
        D->n = 0;  D->m = 8;
        D->kv = malloc(D->m * sizeof(dictentry));
        if (!D->kv)  {  
            free(D);  
            D = NULL;  
        }
        else {
            D->add = dictadd;  
            D->del = dictdel;  
            D->val = dictval;
        }
    }

    return D;
}

#endif
