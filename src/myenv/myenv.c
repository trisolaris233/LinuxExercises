#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tlpi_hdr.h"

#define MAX_ENVIRON 256

extern char **environ;
/* extern char **environ;
 an alternative wey of declration of char** env in main
 argument list but can be used globally
 */
int mysetenv(char*,char*,int);
int myunsetenv(char*);
static char* envir[MAX_ENVIRON];
static int ind = 0;

int main(int argc, char** argv/*,char** env*/) {
    if (argc < 2 || 0 == strcmp(argv[1], "--help"))
        usageErr("%s p|s<NAME>=<VALUE>|d<NAME>...|S<NAME>=<VALUE>");

    char* equal;

    for (int i = 1; i < argc; ++i) {
        switch(argv[i][0]) {
        case 'p':
            for (char** p = environ; NULL != *p; ++p)
                puts(*p);
            break;
        case 's':
        case 'S':
            equal = strchr(argv[i], '=');
            if (NULL == equal)
                errExit("strchr");

            char *name = malloc(equal - argv[i]);
            if (NULL == name)
                errExit("malloc");

            if (NULL == strncpy(name, argv[i] + 1, equal -argv[i] - 1))
                errExit("strncpy");
            name[equal - argv[i] - 1] = '\0';

            char* value = malloc(strlen(argv[i]) - (equal - argv[i]));
            if (NULL == value)
                errExit("malloc");

            if (NULL == strcpy(value, equal + 1))
                errExit("strcpy");
            
            mysetenv(name, value, argv[i][0] == 'S');
            break;
        case 'd':
            myunsetenv(name);
            break;
        }
    }

    // no necessity to free for the system will free them automatically.

    exit(EXIT_SUCCESS);
}

int mysetenv(char *name, char *value, int overwrite) {
    envir[ind++] = malloc(strlen(name) + strlen(value) + 2);
    strcat(envir[ind - 1], name);
    strcat(envir[ind - 1], "=");
    strcat(envir[ind - 1], value);
    envir[ind - 1][strlen(name) + strlen(value) + 1] = '\0';
    char** p;
    for (char** p = environ; NULL != *p; ++p) {
        char* ptr = strchr(*p, '=');
        char envname[ptr - *p + 1];
        strncpy(envname, *p, ptr - *p);
        envname[ptr - *p] = '\0';
        if (0 == strcmp(envname, name)) {
            if (overwrite) {
                *p = envir[ind - 1];
                return 0;
            } else 
                break;
        }
    }
    if (!overwrite) {
        return putenv(envir[ind - 1]);
    }
}

int myunsetenv(char* name) {
    for (char** p = environ; NULL != *p; ++p) {
        char* ptr = strchr(*p, '=');
        char envname[ptr - *p + 1];
        strncpy(envname, *p, ptr - *p);
        envname[ptr - *p] = '\0';
        if (0 == strcmp(envname, name)) {
            for(int i = 0; i < strlen(*p); ++i)
                (*p)[i] = '\0';
            return 0;
        }
    }
    /* or use the glic nonstandard extension by putenv(name)
    which is regarded as removing the name from the env list */
}