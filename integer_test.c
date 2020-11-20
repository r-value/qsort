#include <stdio.h>
#include "qsort.h"

typedef struct {
    int first;
    int second;
} pair;

int compareMyType(const void* lptr, const void* rptr){
    pair lhs = *((pair*)lptr);
    pair rhs = *((pair*)rptr);

    return lhs.first==rhs.first ? lhs.second - rhs.second : lhs.first - rhs.first;
}

int main(){
    int n;
    scanf("%d",&n);
    pair* arr = __builtin_malloc(sizeof(pair) * n);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &arr[i].first, &arr[i].second);
    qsort(arr, n, sizeof(pair), compareMyType);
    for(int i = 0; i < n; i++)
        printf("%d %d\n", arr[i].first, arr[i].second);
    __builtin_free(arr);
    return 0;
}
