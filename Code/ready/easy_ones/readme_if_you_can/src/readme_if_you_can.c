#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readme()
{
    char *buf;
    buf = (char*)malloc(18);
    memset(buf, 0x00, 18);

    strcpy(buf, "SECRET{LOLFOUNDME}");

    printf("secret is at %p\n", buf);
    printf("read it in any way you can :)\n");

    free(buf);
    printf("and it's not there anymore!\n");
}

int main()
{
    readme();
}




