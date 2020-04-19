#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int mydup(int oldfd);
int mydup2(int oldfd, int newfd);

int main() {
    int fd = open("test", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    printf("opened test with fd = %d\n", fd);
    
    if (-1 == fd)
        errExit("open");

    int fd2 = mydup(fd);
    if (-1 == fd2)
        errExit("mydup");

    printf("duplicate the original fd to %d using mydup by fcntl()\n", fd2);

    int fd3 = mydup2(fd2, 2);
    if (-1 == fd3) 
        errExit("mydup2");

    printf("duplicate original fd to 2 successfullly");
    


    exit(EXIT_SUCCESS);
}

int mydup(int oldfd) {
    return fcntl(oldfd, F_DUPFD, oldfd);
}

int mydup2(int oldfd, int newfd) {
    if(-1 == fcntl(oldfd, F_GETFL)) {
        errno = EBADF;
        return -1;
    } 
    if (oldfd == newfd) {
        return oldfd;
    }

    if (-1 == fcntl(newfd, F_GETFL)) {
        if (-1 == close(newfd)) {
            return -1;
        }
    }
    return fcntl(oldfd, F_DUPFD, newfd);
}