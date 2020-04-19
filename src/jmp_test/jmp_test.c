#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

void foo(void) {
    switch(setjmp(env)) {
    case 0:
        printf("foo branch 1\n");
        break;
    case 1:
        printf("foo branch 2\n");
    }
}

void baz(void) {
    printf("baz start\n");
    longjmp(env, 1);
    printf("baz end\n");
}

void bar(void) {
    printf("bar start\n");
    baz();
    printf("bar end\n");
}


int main(int argc, char** argv) {
    foo();
    bar();

    exit(EXIT_SUCCESS);
}