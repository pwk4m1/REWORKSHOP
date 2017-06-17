
#include <stdio.h>

typedef unsigned char byte;

void print_secrets2(void)
{
    int i, j;
    char secret[10];

    for (i=0; i < 10; i++) {
        for (j=0x30; j < 0x5F; j++) {
            j = (byte) j;
            switch (j) {
                case ('C'):
                  secret[i] = j;
                  break;
                case ('0'):
                   secret[i] = j;
                   break;
                case ('u'):
                   secret[i] = j;
                   break;
                case ('N'):
                   secret[i] = j;
                   break;
                case ('7'):
                   secret[i] = j;
                   break;
                case ('_'):
                   secret[i] = j;
                   break;
                case ('Z'):
                   secret[i] = j;
                   break;
                case ('3'):
                   secret[i] = j;
                   break;
                case ('R'):
                   secret[i] = j;
                   break;
            }
        }
    }
    printf("SECRET{");
    printf(secret);
    printf("}\n");
}


