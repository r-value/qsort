#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void swap(void* lhs, void* rhs, size_t size){
    void* tmp = malloc(size);
    memcpy(tmp, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, tmp, size);
    free(tmp);
}

void qsort(void* base, size_t count, size_t size, int (*comp)(const void*, const void*)){
    if(count < 2)
        return;
    {
        void* seed = malloc(1);
        swap(base + size * ((size_t)(seed) % count), base + size * (count - 1), size);
        free(seed);
    }
    void* top = base;
    void* pivot = base + size * (count - 1);
    for(void* cur = base; cur != pivot; cur += size){
        if(comp(cur, pivot) < 0){
            swap(cur, top, size);
            top += size;
        }
    }
    swap(top, pivot, size);
    size_t lcnt = (top - base) / size;
    qsort(base, lcnt, size, comp);
    qsort(top, count - lcnt, size, comp);
}
