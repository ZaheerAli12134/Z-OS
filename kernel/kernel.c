#include "gdt.h"
#include "vga/vga.h"

void kernelmain(void) {
    initgdt();

    print("Hi\n");
    
    for(int i = 0; i<30; i++){
        print("hi\n");

    }

    // Infinite loop
    while (1) { }
}
