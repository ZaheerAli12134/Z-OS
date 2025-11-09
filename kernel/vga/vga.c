#include "vga.h"

static uint16_t* const vga = (uint16_t*)0xB8000;
static const uint8_t color = (COLOR8_LIGHT_GREY | (COLOR8_BLACK << 4));
static uint16_t column = 0;
static uint16_t line = 0;

void scroll(void) {
    for (uint16_t y = 1; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            vga[(y - 1) * width + x] = vga[y * width + x];
        }
    }

    for (uint16_t x = 0; x < width; x++) {
        vga[(height - 1) * width + x] = ' ' | ((uint16_t)color << 8);
    }
}

void newLine(void) {
    if (line < height - 1) {
        line++;
        column = 0;
    } else {
        scroll();
        column = 0;
    }
}

void print(const char* s) {
    while (*s) {
        char c = *s++;

        if (c == '\n') {
            newLine();
        } else {
            if (column >= width)
                newLine();

            vga[line * width + column] = (uint16_t)c | ((uint16_t)color << 8);
            column++;
        }
    }
}

void printChar(char c) {
    if (c == '\n') {
        newLine();
    } else {
        if (column >= width)
            newLine();

        vga[line * width + column] = (uint16_t)c | ((uint16_t)color << 8);
        column++;
    }
}



