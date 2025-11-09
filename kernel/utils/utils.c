#include "utils.h"
#include <stdint.h>

void memset(void *dest, char val, uint32_t count){
    char *temp = (char*) dest;
    for(; count!=0; count--){
        *temp++ = val;
    }
}

void outPortB(uint16_t port, uint8_t value){
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

char inPortB(uint16_t port){
    char n;
    asm volatile("inb %1, %0": "=a"(n):"dN"(port));
    return n;
}

