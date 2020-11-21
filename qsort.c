#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "xorshift.h"

#define swap(lhs,rhs,size)                       \
do {                                             \
    size_t _size = (size);                       \
    char *_lhs = (lhs), *_rhs = (rhs);           \
    while(_size --> 0){                          \
        char tmp = *_lhs;                        \
        *_lhs++ = *_rhs;                         \
        *_rhs++ = tmp;                           \
    }                                            \
}while(0)

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
