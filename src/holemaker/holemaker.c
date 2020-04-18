#include "tlpi_hdr.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <alloca.h> // for alloca()

#define BUFFER_SIZE 1024

/*
usage: ./holemaker file offset bytes-to-read-or-write...
*/
int main(int argc, char** argv) {
    if (4 < argc || 0 == strcmp("--help", argv[1]))
        usageErr("%s filepath offset w<msg-to-write>|r<bytes-to-read>|s<bytes-to-offset>...", argv[0]);

    int fd;
    fd = open(argv[1], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IWOTH | S_IROTH);
    /* open file or create file in mode rw-rw-rw- */

    if (-1 == fd) {
        switch (errno) {
        case EACCES:
            errExit("open: permission denied");
            break;
        }

        errExit("open");
    }

    long value;
    char* buffer;
    ssize_t size;
    off_t offset;

    for (int index = 2; index < argc; ++index) {
        switch(argv[index][0]) {
        case 'r':
            value = getLong(&argv[index][1], GN_ANY_BASE, argv[index]);
            buffer = alloca(value);

            if (NULL == buffer)
                errExit("alloca");

            size = read(fd, buffer, value);

            if (-1 == size)
                errExit("read");

            if (0 == size)
                errExit("read: end-of-file");

            for (int i = 0; i < value; ++i) {
                printf("%c", isprint(buffer[i]) ? buffer[i] : '?');
            }
            
            break;

        case 'w':
            size = write(fd, &argv[index][1], strlen(&argv[index][1]));

            if (-1 == size) 
                errExit("write");

            printf("%lld bytes are written\n", (long long)size); 

            break;

        case 's':
            offset = getLong(&argv[index][1], GN_ANY_BASE, argv[index]);
            if (-1 == lseek(fd, offset, SEEK_SET)) 
                errExit("lseek");

            printf("move to position at offset of %lld bytes\n", (long long)offset);
            

            break;
        }
    }
    
    
    
    


    exit(EXIT_SUCCESS);
}