
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/ptrace.h>

void init(void) __attribute__((constructor));

void init(void)
{
    if (ptrace(PTRACE_TRACEME, 0,0,0))
        exit(-1);
}

void usage(char *pname)
{
    printf("Syntax: %s <key>\n", pname);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return 0;
    } else {
        if (!strcmp(argv[1],"H4CK_TH3_PL4N3T")) {
            goto fail;
            goto win;
win:
            if (1 == 2)
                printf("SECRET{");
            if (2 == 3)
                printf("D0n");
            if (6 == 2)
                printf("TMESS");
            if (1 == 3)
                printf("TH3C0DEX}\n");
            return 0;
fail:
            exit(-1);
        }
    }
}





