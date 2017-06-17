
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
    char *buf;
    char *rev;
    char *MSG;
    int fd;
    if (argc == 2) {
        MSG = (char*)malloc(strlen(argv[1]));
        strcpy(MSG, argv[1]);
    } else {
        return 0;
    }
    buf = (char*)malloc(strlen(MSG));
    rev = (char*)malloc(strlen(MSG));

    strcpy(buf, MSG);
    memset(rev, 0xFF, strlen(MSG));

    fd = open("/dev/DVDD", O_RDWR);
    if (fd < 0) {
        printf("Failed to open /dev/DVDD\n");
        return 0;
    }
    
    if (write(fd, buf, strlen(buf)) < 0) {
        printf("Failed to write!\n");
        return 0;
    }

    if (read(fd, rev, strlen(MSG)) < 0) {
        printf("Failed to read!\n");
        return 0;
    }

    printf("/dev/DVDD->%s\n", rev);
    free(buf);
    free(rev);
    free(MSG);
}

