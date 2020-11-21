#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "xorshift.h"

static void swap(void* lhs, void* rhs, size_t size){
    void* tmp = malloc(size);
    memcpy(tmp, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, tmp, size);
    free(tmp);
}

static void selection_sort(void* base, size_t count, size_t size, int (*comp)(const void*, const void*)){
    void* end = base + size * count;
    for(void* top = base; top != end; top += size){
        void* min = top;
        for(void* cur = top + size; cur != end; cur += size)
            if(comp(cur, min) < 0)
                min = cur;
        swap(top, min, size);
    }
}

void qsort(void* base, size_t count, size_t size, int (*comp)(const void*, const void*)){
    if(count < 2)
        return;
    else if(count < 20)
        selection_sort(base, count, size, comp);
    else{
        void* top = base;
        void* pivot = base + size * (count - 1);
        swap(base + size * (xorshift32() % count), pivot, size);

        for(void* cur = base; cur != pivot; cur += size){
            if(comp(cur, pivot) < 0){
                swap(cur, top, size);
                top += size;
            }
        }
        swap(top, pivot, size);

        size_t lcnt = (top - base) / size;
        qsort(base, lcnt, size, comp);
        qsort(top+size, count - lcnt - 1, size, comp);
    }
}
