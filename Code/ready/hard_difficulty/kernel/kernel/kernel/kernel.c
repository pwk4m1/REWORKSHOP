#include <stdio.h>
#include <stdlib.h>

#include <kernel/tty.h>
#include <kernel/secrets.h>

void print_secret()
{
    int i;
    int j;
    char secret[15];
    printf("SECRET{");
    printf("K");
    printf("e");
    printf("R");
    printf("n");
    printf("e");
    printf("L");
    printf("S");
    printf("F");
    printf("t");
    printf("w");
    printf("}\n");
}

void kernel_main(void) {
	terminal_initialize();
    printf("Good job :)\n");
    printf("Now go find my secrets...\n");
    printf("They are in form SECRET{secret}\n");

    abort();
}


