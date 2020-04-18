#include "tlpi_hdr.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

int main(int argc, char* argv[]) {
    if (strcmp(argv[1],"--help") == 0 || 2 != argc)
        usageErr("%s file", argv[0]);


    char* filepath = argv[1];
    int fd;
    char ch;
    ssize_t size_write;
    char buffer[BUFSIZE];
    int index = 0;

    fd = open(filepath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (-1 == fd) {
        switch (errno) {
        case EACCES:
            errExit("open: Permission Denied");
            break;

        case EISDIR:
            errExit("open: Unable to open a directoty");
            break;
        }
        errExit("open");
    }
    
    
    
    
    while ((ch = getchar()) != EOF) {
        if (index == BUFSIZ - 1) {
            size_write = write(fd, buffer, BUFSIZE);

            if (-1 == size_write) {
                errExit("write");
            }

            index = 0;
        } else {
            buffer[index++] = ch;
        }
    }

    if (index > 0) {
        size_write = write(fd, buffer, index);

        if (-1 == size_write) {
            errExit("write");
        }
    }

    if (-1 == close(fd))
        errExit("close");

    

        



    exit(EXIT_SUCCESS);
}