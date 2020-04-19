#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    int fd = open("test", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    if (-1 == fd)
        errExit("open");

    if (-1 == lseek(fd, 233, SEEK_SET))
        errExit("lseek"); 

    puts("move SEEK_CUR to 233");

    int fd2 = dup(fd);
    if (-1 == fd2)
        errExit("dup");

    printf("duplicate fd to fd2 with value of %d\n", fd2);

    off_t offset;
    if ((offset = lseek(fd2, 0, SEEK_CUR)) == -1)
        errExit("lseek");

    printf("current offset of fd2 is %d\n", offset);

    int flags = fcntl(fd, F_GETFL), flags2 = fcntl(fd2, F_GETFL);

    if (-1 == flags || -1 == flags2)
        errExit("fcntl() F_GETFL");

    printf("the flags of fd is %d, fd2 is %d\n", flags, flags2);

    
    exit(EXIT_SUCCESS);
}