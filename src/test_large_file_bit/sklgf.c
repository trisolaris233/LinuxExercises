#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

/*
 64-bit systems naturally permit file sizes greater than 2
              Gigabytes, and on those systems this macro has no effect.
*/

int main() {
    off_t offset = 1;
    size_t size = sizeof(offset), bits = size*8;
    int i;
    long j;
    long long k;

#ifdef _FILE_OFFSET_BITS

    printf("Defined _FILE_OFFSET_BITS to %d\n", _FILE_OFFSET_BITS);
#endif
    printf("the size of off_t is %ld, and int is %ld, long is %ld, long long is %ld\n",
                             (long)size, (long)sizeof(i), sizeof(j), sizeof(k));

    printf("so bits of off_t is %ld\n", bits);

    if (sizeof(k) == size) {
        printf("max of bytes: %lld\n", __LONG_LONG_MAX__);
        k = __LONG_LONG_MAX__;

        double vkb = k / 1024.0, vmb = vkb / 1024.0, vgb = vmb / 1024.0,
            vtb = vgb / 1024.0;

        printf("%lf KB, %lf MB, %lf GB, %lf TB\n", vkb, vmb, vgb, vtb); 
    }


    exit(EXIT_SUCCESS);
}
