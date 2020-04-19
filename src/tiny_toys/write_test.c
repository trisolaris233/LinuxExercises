#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    int fd1, fd2, fd3;
    char file[] = "test";
    fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    fd2 = dup(fd1);
    fd3 = open(file, O_RDWR);
    write(fd1, "Hello,", 6);
    // hello,
    write(fd2, "world", 6);
    // hello,world
    lseek(fd2, 0, SEEK_SET);
    // hello,world
    write(fd1, "HELLO,", 6);
    // because fd3 is from open not dup() so fd3 maintains its own file offset in the
    // system-wide open file description table.
    // so the ultimate result is Giddyworld
    // HELLO,world
    write(fd3, "Gidday", 6);
    // Giddyworld

    exit(EXIT_SUCCESS);
}