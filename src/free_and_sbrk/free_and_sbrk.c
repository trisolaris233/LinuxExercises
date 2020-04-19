#define _DEFAULT_SOURCE
#include "tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char **argv) {
    char *ptr[MAX_ALLOCS];
    int free_stp, free_min, free_max, blocksize, number_alloc, j;

    if (argc < 3 || 0 == strcmp(argv[1], "--help"))
        usageErr("%s num-allocs block-size [step [min [max]]]\n", argv[0]);

    number_alloc = getInt(argv[1], GN_ANY_BASE, argv[1]);
    if (number_alloc > MAX_ALLOCS)
        cmdLineErr("num-allocs > %d\n", number_alloc);

    blocksize = getInt(argv[2], GN_ANY_BASE, argv[2]);

    free_stp = (argc > 3) ? getInt(argv[3], GN_ANY_BASE, argv[3]) : 1;
    free_min = (argc > 4) ? getInt(argv[4], GN_ANY_BASE, argv[4]) : 0;
    free_max = (argc > 5) ? getInt(argv[5], GN_ANY_BASE, argv[5]) : number_alloc;

    printf("initial break: %10p\n", sbrk(0));

    for (int i = 0; i < number_alloc; ++i) {
        if ((ptr[i] = malloc(blocksize)) == NULL)
            errExit("malloc");
        printf("break: %10p\n", sbrk(0));
    }

    printf("now the break is %10p\n", sbrk(0));

    printf("--------- free start ------------\n");

    for (int i = free_min; i < free_max; i += free_stp) {
        free(ptr[i]);
        printf("break: %10p\n", sbrk(0));
    }

    printf("after free(), the break is %10p", sbrk(0));
    


    exit(EXIT_SUCCESS);
}