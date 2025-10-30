#include "gdt.h"

void kernelmain(){
    
    char *video = (char*)0xB8000;
    
    video[0] = 'H';
    video[1] = 0x0F;
    
    initgdt();
    
    video[2] = 'i';
    video[3] = 0x0F;
    
    // Infinite loop
    while(1){

    }
}
