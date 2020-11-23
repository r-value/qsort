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

static void* qsort_pivot(void* base, size_t count, size_t size, int (*comp)(const void*, const void*)){
    size_t half = count / 2;
    void* p1 = base + size * half;
    void* p2 = base + size * (xorshift32() % half);
    void* p3 = base + size * (xorshift32() % (count - half - 1) + half + 1);
    
    return comp(p1, p2) < 0 ? (
            comp(p2, p3) < 0 ? p2 : (
                comp(p1, p3) < 0 ? p3 : p1
            )
        )
        :(
            comp(p2, p3) > 0 ? p2 : (
                comp(p1, p3) > 0 ? p3 : p1
            )
        )
    ;
}

void qsort(void* base, size_t count, size_t size, int (*comp)(const void*, const void*)){
    if(count < 2)
        return;
    else if(count < 15)
        selection_sort(base, count, size, comp);
    else{
        void* pivot = base + size * (count - 1);
        swap(qsort_pivot(base, count, size, comp), pivot, size);

        void* L = base;
        void* R = pivot - size;
        while(1){
            while(comp(L, pivot) < 0)
                L += size;
            while(comp(R, pivot) > 0)
                R -= size;

            if(L >= R)
                break;

            swap(L, R, size);
            L += size;
            R -= size;
        }
        swap(L, pivot, size);

        size_t lcnt = (L - base) / size;
        qsort(base, lcnt, size, comp);
        qsort(L + size, count - lcnt - 1, size, comp);
    }
}
