#include "gdt.h"
#include "vga/vga.h"
#include "interrupt/interrupt.h"

void kernelmain(void) {
    initgdt();
    initIDT();

    print("Hi");
    print("\n");
    print(1/0);
    
}

