#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    
    int fd = open("test", O_APPEND | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(-1 == fd) 
        errExit("open");

    if (-1 == lseek(fd, 0, SEEK_SET)) {
        errExit("lseek");
    }

    char writestr[] = "deep dark fantasy";
    if (strlen(writestr) != write(fd, writestr, strlen(writestr)))
        errExit("write");

    exit(EXIT_SUCCESS);
}