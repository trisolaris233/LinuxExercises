#include <stdio.h>
#include "header.h"

int main() {
    extern int deep_dark_fantasy;
    extern struct test_struct van;
    extern const double fucku;
    extern int fuckyou;

    printf("deep_dark_fantasy:       %d\n", deep_dark_fantasy);
    printf("van: {%d, %d, %d}\n", van.x, van.y, van.z);
    printf("fuckyou: %d\n", fuckyou);
    printf("fucku: %lf\n", fucku);

    // if this line is complied, it will pass through the compile
    // safely, but only a segmention fault on runtime
    // fucku = 7.8;

    return 0;
}