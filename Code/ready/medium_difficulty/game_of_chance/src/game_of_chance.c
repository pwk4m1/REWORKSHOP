#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void get_correct(char *buf)
{
    int i;
    for (i=0; i < 5; i++)
        buf[i] = ((char) 0x41 + (rand() % 10));
    buf[i++] = '\0';
}

int main(int argc, char **argv)
{
    char *correct;

    if (argc != 2) {
        printf("usage: %s <numbers/letters>\n", argv[0]);
        printf("eg: %s ABC1242\n", argv[0]);
    } else {
        correct = (char*)malloc(6);
        memset(correct, 0x00, 6);
        get_correct(correct);

        if (!strcmp(correct, argv[1])) {
            printf("Good job , you won!\n");
        } else {
            printf("You lost!\n");
        }

        free(correct);
        return 0;
    }
}


