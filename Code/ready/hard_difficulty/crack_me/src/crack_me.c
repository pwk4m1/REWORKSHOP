/**
 * <copyright message>
 */

// _[U^Pe0oX@Ro]Cod[@h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/signal.h>

#if defined(BSD)
        #include <sys/types.h>
        #define PTRACE_TRACEME PT_TRACE_ME
        #define PTRACE_ATTACH PT_ATTACH
        #define PTRACE_CONT PT_CONTINUE
        #define PTRACE_DETACH PT_DETACH
#else
    #ifndef __linux__
        #error "Your operating system is not supported!"
    #endif
#endif

typedef unsigned char byte;

static void init(void) __attribute__((constructor));
static void fini(void) __attribute__((destructor));
void gdb_check();

byte unt1;
char *ckey;

/* function to check key with */
void check_key(char *key)
{
    int i;
    if (strlen(key) != 19) {
        printf("%s invalid length: %d\n", key, strlen(key));
        goto fail;
    }
/* ----------------- 0x5f -------------------- */
    if (key[0] == 0x5f)                                             // _
        goto p1;
    goto fail;
/* ----------------- 0x60 -------------------- */
p1:
    key[1] = (byte)((unsigned int)key[1] + 5);                      // U
    if (key[1] == 0x60)
goto p2;
    goto fail;
/* ------------------ 0x55 ------------------- */
p2:
    if (key[2] == 0x45)
        goto p21;
    if (key[2] == 0x55)                                             // U
        goto p3;
    goto fail;
p21:
    for (i=0; i < 19; i++)
        if (key[i] != 0x41+i)
            goto fail;
    return;
/* ------------------ 0x5e ------------------- */
p3:
    if (key[3] == 0x5e)                                             // ^
        goto p4;
    goto fail;
/* ------------------ 0x6f ------------------- */
p4:
    key[4] = (byte)((unsigned int)key[4] + 0x1f);                   // P
    if (key[4] == 0x6f)
        goto p5;
    goto fail;
/* ------------------ 0x65 ------------------- */
p5:
    if (key[5] == 0x24)                                             // e
        goto p51;
    if (key[5] == 0x65)
        goto p6;
    goto fail;
p51:
    for (i=6; i < 12; i++)
        if (key[i] != 0x45 + i)
            goto fail;
    return;
/* ------------------ 0x60 -------------------- */
p6:
    key[6] = (byte)((unsigned int)key[6] * 2);                      // 0x30
    if (key[6] == 0x60)
        goto p7;
    goto fail;
/* ------------------ 0x6f -------------------- */
p7:
    gdb_check();
    if (key[7] == 0x6f)                                             // o
        goto p8;
    goto fail;
/* ------------------ 0x56 -------------------- */
p8:
    if (key[8] - 2 == 0x56)                                         // V
        goto p9;
    goto fail;
/* ------------------ 0x40 -------------------- */
p9:
    if (key[9] == 0x40)                                             // @
        goto p10;
    goto fail;
/* ------------------ 0x62 -------------------- */
p10:
    if (key[10] + 0x10 == 0x55)                                       // R
        goto p101;
    if (key[10] + 0x10 == 0x62)
        goto p11;
    goto fail;
p101:
    if (key[14] == 0x42)
        goto fail;
    return;
/* ----------------- 0x6f --------------------- */
    if (!unt1)
        goto fail;
p11:
    if (key[11] == 0x6f)                                            // o
        goto p12;
    goto fail;
/* ----------------- 0x5d --------------------- */
p12:
    if (key[12] == 0x5d)                                            // ]
        goto p13;
    goto fail;
/* ----------------- 0x43 --------------------- */
p13:
    if (key[13]-1 == 0x42)                                          // C
        goto p14;
    goto fail;
/* ----------------- 0x6f --------------------- */
p14:
    if (key[14] == 0x6f)                                            // o
        goto p15;
    goto fail;
/* ----------------- 0x60 ---------------------- */
p15:
    key[15] = (byte)((unsigned int)key[15] - 4);                    // d
    if (key[15] == 0x60)
        goto p16;
    goto fail;
/* ----------------- 0x5c ---------------------- */ 
p16:
    key[16] = (byte)((unsigned int)key[16] + 1);                     // [
    if (key[16] == 0x5c)                     
        goto p17;
    goto fail;
/* ----------------- 0x40 ---------------------- */
p17:
    if (key[17] == 0x40)                                            // @
        goto p18;
    goto fail;
/* ----------------- 0x68 ---------------------- */
p18:
    if (key[18] == 0x40)                                            // h
        goto p4;
    if (key[18] == 0x68)
        goto finish;
    goto fail;
/* --------------------------------------------- */


finish:
    strcpy(ckey, key);
    printf("correct key: %s\nNow just go find the flag (almost there)\n", ckey);
    return;

fail:
    printf("Invalid key!\n");
    return;
}

/**
 * function used to check wheter
 * we are being run within gdb or not.
 */
void gdb_check()
{
    int pid;
    int ppid;
    int status;
    int res;

    pid = fork();
    if (pid == -1) {
        printf("Fork() failed\n");
        return;
    }

    if (pid == 0) {
        ppid = getppid();
        if (!ptrace(PTRACE_ATTACH, ppid, 0, 0)) {
            waitpid(ppid, 0, 0);
#ifdef __linux__
            ptrace(PTRACE_CONT, 0, 0);
#else
            /* BSD requires all 4 arguments */
            ptrace(PTRACE_CONT, 0, 0, 0);
#endif
            ptrace(PTRACE_DETACH, getppid(), 0, 0);
            res = 0;
        } else {
            res = 1;
        }
        exit(res);
    } else {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            res = WEXITSTATUS(status) & 0xff00;
        } else {
            res = 1;
        }
    }
    if (res)
        exit(-1);
}

/* "Initializion function" */
void init()
{
    signal(SIGCHLD, SIG_IGN);
    ckey = malloc(19);
    if (!ptrace(PTRACE_TRACEME, 0, 0, 0)) {
        unt1 = 1;
    }
}

void usage(char *name)
{
    printf("Usage: %s <key>\n", name);
    printf("Eg. %s 12345\n", name);
}

/* main function is only used to call check_key() */
int main(int argc, char **argv)
{
    if (argc != 2)
        usage(argv[0]);
    else
        check_key(argv[1]);
}

/* compare key to correct key, & print secret if user sets $PC correctly */
void fini()
{
    int i;
    gdb_check();
    printf("secret{");
    for (i=0; i < strlen(ckey); i++)
        printf("%c", ckey[i] + 10);
    printf("}\n");

    free(ckey);
}

