#include <stdio.h>
#include <string.h>
#include <stdint.h>

int itoa_s(int num, int base, char* rv)
{
    char buffer[32];
    char digits[16] = {"0123456789abcdef"};
    int i;

    i = 0;

    while ( num > 10 ) {
        if ( strlen(buffer) == 32 ) return 0;
        buffer[i] = digits[num % base];
        num = num / 10;
        i++;
    }

    buffer[i+1] = num + '\0';

    memcpy(rv, buffer, strlen(buffer));
    return 1;
}



