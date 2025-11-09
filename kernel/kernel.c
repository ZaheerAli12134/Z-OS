#include "gdt.h"
#include "vga/vga.h"
#include "interrupt/interrupt.h"
#include "utils/utils.h"
#include "interrupt/keyboard.h"

void kernelmain(void) {
    initgdt();


    initIDT();
    print("WELCOME TO MY OS");
    print("\n");
    initKeyboard();
    while(1){

    }
    
}

