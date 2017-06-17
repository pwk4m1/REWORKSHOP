#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif
int itoa_s(int num, int base, char* rv);

__attribute__((__noreturn__))
void abort(void);

#ifdef __cplusplus
}
#endif

#endif
