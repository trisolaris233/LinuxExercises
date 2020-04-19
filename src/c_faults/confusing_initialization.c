#include <stdio.h>
#include <stdlib.h>


static int primes = {2, 3, 3};

int main(int argc, char **argv) {

    printf("%p\n", &primes);

    exit(EXIT_SUCCESS);
}