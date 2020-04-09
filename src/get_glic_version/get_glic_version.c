#include <gnu/libc-version.h>
#include <stdio.h>
#include <stdlib.h>

int
main() {
    const char* ptr = gnu_get_libc_version();
    printf("%s\n",ptr);
    exit(0);
}
