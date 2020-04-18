#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#define BUFFER_SIZE 1024

int main(int argc, char** argv) {

    if (argc < 3 || strcmp("--help", argv[1]) == 0) 
        usageErr("%s source dest", argv[0]);

    char buffer[BUFFER_SIZE];
    int fd, fd2;

    fd = open(argv[1], O_RDONLY);
    if (-1 == fd) {
        switch(errno) {
        case EACCES:
            errExit("open: permission denied");
        }

        errExit("open");
    }

    fd2 = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, S_IWUSR | S_IRUSR);
    if (-1 == fd2) {
        switch(errno) {
        case EACCES:
            errExit("open: permission denied");
        }

        errExit("open");
    }
    

    ssize_t bytes_read, bytes_write;

    while((bytes_read = read(fd, buffer, BUFFER_SIZE)) == BUFFER_SIZE) {
        bytes_write = write(fd2, buffer, BUFFER_SIZE);
        
        if (-1 == bytes_write) 
            errExit("write");
    }

    if (-1 == bytes_read) 
        errExit("read");
    
    if (0 == bytes_read)
        errExit("read: end-of-file");

    bytes_write = write(fd2, buffer, bytes_read);
        
    if (-1 == bytes_write) 
        errExit("write");


    exit(EXIT_SUCCESS);
}