#include "gdt.h"

extern void gdt_flush(addr_t);

struct gdt_entry gdt[3];
struct gdt_ptr point; 
void initgdt(){

    //sets adress location
    point.limit = (sizeof(struct gdt_entry)*3) - 1;

    point.base = &gdt;

    //creating entries
    setGdtEntry(0,0,0,0,0);
    setGdtEntry(1,0,0xFFFFFFFF,0x9A,0xCF); //kernel code segment, cannot write to
    setGdtEntry(2,0,0xFFFFFFFF,0x92,0xCF); //kernel data segment 

    gdt_flush(&point);
 
};

//sets each gdt entry by using bitwise operations to modify each part of the descriptor
void setGdtEntry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    
    gdt[num].limit = (limit & 0xFFFF);
    gdt[num].flags = (limit >> 16) & 0x0F;
    gdt[num].flags |= (gran & 0xF0);
    gdt[num].access = access;


};












