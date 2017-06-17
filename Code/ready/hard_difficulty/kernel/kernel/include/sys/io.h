#if !defined(Nyanix_IO)
    #define Nyanix_IO
#endif
#include <stdint.h>

/** 
 * In functions are used to read from
 * paraller port <port>.
 *
 * Takes as argument: paraller port.
 * Returns: bytes red from paraller port
 * corresponding the function type.
 * 
 */
extern unsigned char inb(unsigned short int port);
extern unsigned short int inl(unsigned short int port);
extern unsigned int inw(unsigned short int port);

/**
 * Out functions are used to write to
 * paraller port <port>.
 *
 * Takes as argument: paraller port, data to write.
 * Returns: None.
 *
 */
extern void outb(unsigned short int port, unsigned char b);
extern void outl(unsigned short int port, unsigned short int l);
extern void outw(unsigned short int port, unsigned int w);

