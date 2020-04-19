#include <stdio.h>
#include <stdlib.h>

char gloBuf[65536]; // global but uninitialized data
int primes[] = { 2, 3, 5, 7 }; // global initialized data

static int square(int x) {
    int result;

    result = x * x;
    return result;
}


static void doCalc(int val) {
    printf("the square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;
        t = val * val * val;
        printf("the cube of %d is %d\n", val, t);
    }
}

int main(int argc, char** argv) {
    static int key = 9973; // static initialized variable
    static char buf[1024000]; // static but uninitialized variable
    char *p; 
    p = malloc(1024); // allocated in heap
    doCalc(key);

    exit(EXIT_SUCCESS);
}