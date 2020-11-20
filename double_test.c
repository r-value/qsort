#include <stdio.h>
#include "qsort.h"

int compareMyType(const void* lptr, const void* rptr){
    double lhs = *((double*)lptr);
    double rhs = *((double*)rptr);

    if(lhs < rhs)
        return -1;
    else if(lhs > rhs)
        return 1;
    else
        return 0;
}

int main(){
    int n;
    scanf("%d",&n);
    double* arr = __builtin_malloc(sizeof(double) * n);
    for(int i = 0; i < n; i++)
        scanf("%lf", arr + i);
    qsort(arr, n, sizeof(double), compareMyType);
    for(int i = 0; i < n; i++)
        printf("%f\n", arr[i]);
    __builtin_free(arr);
    return 0;
}
