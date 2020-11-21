#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

static uint32_t memseed(){
    void* ptr = malloc(1);
    uint32_t seed = (uint32_t)((size_t)ptr);
    free(ptr);
    return seed;
}

uint32_t xorshift32(){
//    static uint32_t state = memseed(); // Missing C++ for the 2147483647th time (-_-|||)
    static uint32_t state = 0;
    {
        static bool firstexec = true;
        if(firstexec){ // Hope that branch prediction will work here...
            state = memseed();
            firstexec = false;
        }
    }
    uint32_t cur = state;
    cur ^= cur << 13;
    cur ^= cur >> 17;
    cur ^= cur << 5;
    return state = cur;
}
