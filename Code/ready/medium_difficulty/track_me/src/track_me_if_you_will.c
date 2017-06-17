#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

typedef struct
{
    char *addr;
    int port;
} addr_pair;

void decrypt_addr(char *addr, char *crypto)
{
    unsigned char byte;
    unsigned int i;

    for (i=0; i < strlen(crypto); i++) {
        addr[i] = crypto[i] ^ 1;
    }
}

int decrypt_port(int crypto)
{
    return crypto >> 1;
}

void connect_home(addr_pair *ap)
{
    int sock;
    struct sockaddr_in saddr;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
        return;

    saddr.sin_addr.s_addr   = inet_addr(ap->addr);
    saddr.sin_family        = AF_INET;
    saddr.sin_port          = htons(ap->port);

    if (connect(sock, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
        printf("OOPSIE , if this was real , you might be having a shell popped to your system now :)\n");
    } else {
        printf("Nice job, apparently you found correct addr:port pair:)\n");
    }
    close(sock);
    return;
}

void get_addr_pair(addr_pair *ap)
{
    decrypt_addr(ap->addr, "\x30\x33\x36\x2f\x31\x2f\x31\x2f\x30");
    ap->port = decrypt_port(2674);
}

int main()
{
    addr_pair *ap;
    ap = (addr_pair *) malloc(sizeof(addr_pair));
    ap->addr = (char*)malloc(20);
    memset(ap->addr, 0x00, 20);
    get_addr_pair(ap);
    connect_home(ap);
    free(ap);
}

