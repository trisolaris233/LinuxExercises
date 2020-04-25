#include "tlpi_hdr.h"

static void sysconfPrint(const char *msg, int name) {
    long lim;

    errno = 0;
    lim = sysconf(name);
    if (-1 != lim) {
        printf("%s %ld\n", msg, lim);
    } else {
        if (0 == errno) {
            printf("%s (indeterminate)\n", msg);
        } else {
            errExit("sysconf %s", msg);
        }
    }
}

int main(int argc, char **argv) {
    sysconfPrint("_SC_ARG_MAX:          ", _SC_ARG_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:      ", _SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:         ", _SC_PAGE_SIZE);
    sysconfPrint("_SC_RTSIG_MAX:        ", _SC_RTSIG_MAX);

    exit(EXIT_SUCCESS);
} 