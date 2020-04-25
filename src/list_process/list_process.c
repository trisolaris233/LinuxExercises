#include <sys/types.h>
#include <pwd.h>
#include "tlpi_hdr.h"
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>

#define MAX_BUF 1024
#define READ_BUF 1024

uid_t get_uid_from_usrname(const char *name) {
    struct passwd *pwd;
    pwd = getpwnam(name);

    if (NULL == pwd) {
        errExit("getpwname");
    }
    return pwd->pw_uid;
}


int main(int argc, char **argv) {
    if (argc < 2 || strcmp("--help", argv[1]) == 0) 
        usageErr("%s usrname", argv[0]);

    uid_t uid = get_uid_from_usrname(argv[1]);
    DIR *dirp;
    struct dirent *dir;
    char dirbuf[MAX_BUF];
    char readbuf[READ_BUF];

    if (NULL == (dirp = opendir("/proc"))) 
        errExit("opendir");

    do {
        errno = 0;
        if (NULL != (dir = readdir(dirp))) {
            char *p;
            Boolean flag = FALSE;

            for (p = dir->d_name; *p != '\0'; ++p) {
                if (!isdigit(*p)) {
                    flag = TRUE;
                    break;
                }
            }

            if (!flag) {
                char filename[MAX_BUF];
                strcpy(filename, "/proc/");
                strcat(filename, dir->d_name);
                strcat(filename, "/status");


                FILE *fp = fopen(filename, "r");
                if (NULL == fp)
                    errExit("fopen");

                while (NULL != fgets(readbuf, READ_BUF, fp)) {
                    // find the line of Uid
                    if (0 == strncmp(readbuf, "Uid:", 4)) {
                        char *p2;
                        uid_t own_id;
                        own_id = 0;
                        char idstack[22];
                        int index = 0;
                        int weight = 1;

                        for (p2 = readbuf; !isdigit(*p2); ++p2);
                        while (isdigit(*p2))
                            idstack[index++] = *p2 - '0', p2++;

                        while(index - 1 >= 0) {
                            own_id += idstack[--index] * weight;
                            weight *=10;
                        }
                        
                        char proc_num_buf[MAX_BUF] = {0};
                        strncpy(proc_num_buf, filename, strlen(filename) - strlen(strrchr(filename, '/')));

                        
                        if (own_id == uid) {
                            printf("%s\n", proc_num_buf + 6);
                        }
                        break;
                    }
                    
                    memset(readbuf, 0, READ_BUF);
                }

            }
        }
    } while(NULL != dir);


    exit(EXIT_SUCCESS);
}


