#include <vga.h>

uint16_t column = 0;
uint16_t line = 0;
static uint16_t* const vga = (uint16_t*)0xB8000;
static const uint8_t color = (COLOR8_LIGHT_GREY | (COLOR8_BLACK << 4));

void scroll(){
    for(uint16_t y = 1; y<height ; y++){
        for(uint16_t x = 0; x<width;x++){
            vga[(y-1)*width + x] = vga[y*width + x];
        }
    }

    for(uint16_t x = 0; x<width;x++){
        vga[(height-1)*width+x] = ' ';
    }
};

void newLine(){
    if(line < height -1){
        line++;
        column = 0;

    }
    else{
        scroll();
        column = 0;
    }
};

void print(const char* s){
    while(*s){
        char c = *s++;
        
        if(c == '\n'){
            newLine();
            break;
        }
        else{
            if(column == width){
                newLine();
            }
            vga[line*width + (column++)] = c | color;
            break;
        }
    }

}
