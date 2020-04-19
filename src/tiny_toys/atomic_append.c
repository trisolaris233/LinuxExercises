#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    if (3 > argc || argv[1] == "--help")
        usageErr("%s filepath bytes-to-write [x](open O_APPEND flag)", argv[0]);

    char* filepath = argv[1];
    long bytes = getLong(argv[2], GN_ANY_BASE, argv[2]);
    Boolean is_append = (argc >= 4 && argv[3][0] == 'x');

    int fd = open(filepath, O_WRONLY | O_CREAT | (is_append ? O_APPEND : 0), S_IRUSR | S_IWUSR);
    if (-1 == fd)
        errExit("open");

    char* buffer = malloc(bytes);
    if (buffer == NULL)
        errExit("malloc");


    for (int i = 0; i < bytes; ++i)
        buffer[i] = 'x';
    
    if (!is_append && -1 == lseek(fd, 0, SEEK_END))
        errExit("lseek");

    ssize_t bytes_write = write(fd, buffer, bytes);
    if (bytes_write != bytes)
        errExit("write");

    printf("%lld bytes written.\n", bytes_write);
    

    exit(EXIT_SUCCESS);
} 