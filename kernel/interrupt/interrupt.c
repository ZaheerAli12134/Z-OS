#include <stdint.h>
#include "../utils/utils.h"
#include "interrupt.h"
#include "../vga/vga.h"


struct idt_entry idt[256];
struct idtptr pointer;

extern void idt_flush(uint32_t);

void initIDT(){
    pointer.limit = (sizeof(struct idt_entry) * 256) - 1;
    pointer.base = (uint32_t) &idt;

    memset(&idt, 0, sizeof(struct idt_entry) * 256);


    //vector is address that points to correct interrupt handler
    //each idt entry is the vector then the idt also poitns to that handler

    outPortB(0x20, 0x11); // initialises the PIC chip, next commands ICW1 2 3 4 
    outPortB(0xA0, 0x11);

    outPortB(0x21, 0x20); //set offsets
    outPortB(0xA0, 0x28);

    outPortB(0x21,0x04);   // master slave connection, theres a slave on irq2, bitmask
    outPortB(0xA0, 0x02);  // there is a master on  irq1 direct value

    outPortB(0x21,0x01);
    outPortB(0xA0,0x01);

    outPortB(0x21, 0x0);
    outPortB(0xA0, 0x0); //allow all interrupt to send signals

    setIdtGate(0, (uint32_t)isr0,0x08, 0x8E);
    setIdtGate(1, (uint32_t)isr1,0x08, 0x8E);
    setIdtGate(2, (uint32_t)isr2,0x08, 0x8E);
    setIdtGate(3, (uint32_t)isr3,0x08, 0x8E);
    setIdtGate(4, (uint32_t)isr4, 0x08, 0x8E);
    setIdtGate(5, (uint32_t)isr5, 0x08, 0x8E);
    setIdtGate(6, (uint32_t)isr6, 0x08, 0x8E);
    setIdtGate(7, (uint32_t)isr7, 0x08, 0x8E);
    setIdtGate(8, (uint32_t)isr8, 0x08, 0x8E);
    setIdtGate(9, (uint32_t)isr9, 0x08, 0x8E);
    setIdtGate(10, (uint32_t)isr10, 0x08, 0x8E);
    setIdtGate(11, (uint32_t)isr11, 0x08, 0x8E);
    setIdtGate(12, (uint32_t)isr12, 0x08, 0x8E);
    setIdtGate(13, (uint32_t)isr13, 0x08, 0x8E);
    setIdtGate(14, (uint32_t)isr14, 0x08, 0x8E);
    setIdtGate(15, (uint32_t)isr15, 0x08, 0x8E);
    setIdtGate(16, (uint32_t)isr16, 0x08, 0x8E);
    setIdtGate(17, (uint32_t)isr17, 0x08, 0x8E);
    setIdtGate(18, (uint32_t)isr18, 0x08, 0x8E);
    setIdtGate(19, (uint32_t)isr19, 0x08, 0x8E);
    setIdtGate(20, (uint32_t)isr20, 0x08, 0x8E);
    setIdtGate(21, (uint32_t)isr21, 0x08, 0x8E);
    setIdtGate(22, (uint32_t)isr22, 0x08, 0x8E);
    setIdtGate(23, (uint32_t)isr23, 0x08, 0x8E);
    setIdtGate(24, (uint32_t)isr24, 0x08, 0x8E);
    setIdtGate(25, (uint32_t)isr25, 0x08, 0x8E);
    setIdtGate(26, (uint32_t)isr26, 0x08, 0x8E);
    setIdtGate(27, (uint32_t)isr27, 0x08, 0x8E);
    setIdtGate(28, (uint32_t)isr28, 0x08, 0x8E);
    setIdtGate(29, (uint32_t)isr29, 0x08, 0x8E);
    setIdtGate(30, (uint32_t)isr30, 0x08, 0x8E);
    setIdtGate(31, (uint32_t)isr31, 0x08, 0x8E);

    setIdtGate(32, (uint32_t)irq0, 0x08, 0x8E);
    setIdtGate(33, (uint32_t)irq1, 0x08, 0x8E);
    setIdtGate(34, (uint32_t)irq2, 0x08, 0x8E);
    setIdtGate(35, (uint32_t)irq3, 0x08, 0x8E);
    setIdtGate(36, (uint32_t)irq4, 0x08, 0x8E);
    setIdtGate(37, (uint32_t)irq5, 0x08, 0x8E);
    setIdtGate(38, (uint32_t)irq6, 0x08, 0x8E);
    setIdtGate(39, (uint32_t)irq7, 0x08, 0x8E);
    setIdtGate(40, (uint32_t)irq8, 0x08, 0x8E);
    setIdtGate(41, (uint32_t)irq9, 0x08, 0x8E);
    setIdtGate(42, (uint32_t)irq10, 0x08, 0x8E);
    setIdtGate(43, (uint32_t)irq11, 0x08, 0x8E);
    setIdtGate(44, (uint32_t)irq12, 0x08, 0x8E);
    setIdtGate(45, (uint32_t)irq13, 0x08, 0x8E);
    setIdtGate(46, (uint32_t)irq14, 0x08, 0x8E);
    setIdtGate(47, (uint32_t)irq15, 0x08, 0x8E);

    setIdtGate(128, (uint32_t)isr128, 0x08, 0x8E); 
    setIdtGate(177, (uint32_t)isr177, 0x08, 0x8E); 

    idt_flush(&pointer);



};

void setIdtGate(uint8_t num, uint32_t base, uint16_t selector, uint8_t gate_type){
            idt[num].base_low = base & 0xFFFF;
            idt[num].base_high = (base >> 16) & 0xFFFF;
            idt[num].selector = selector;
            idt[num].zero = 0;
            idt[num].gate_type_section = gate_type | 0x60;
}

unsigned char* exceptions[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Fault",
    "Machine Check", 
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"

};

//each irq routine that needs to be peformed for a specific interrupt
void *irq_routines[16] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0


};

void isr_handler(struct InterruptRegisters* regs){
    if(regs->int_no < 32){
        print(exceptions[regs->int_no]);
        print("\n");
        print("exception NOOOOO");
        while(2){

        }
    }

}

//takes in irq number, and fucntion for that specific irq to be solved, stores in irq routines so "installes" it
void irq_install_handler (int irq, void (*handler)(struct InterruptRegisters* r)){
    irq_routines[irq] = handler;
}


//takes pushed registers as arguments
void irq_handler(struct InterruptRegisters* regs){

    //initlialises handler func
    void (*handler)(struct InterruptRegisters *regs);

    //checks if exists
    handler = irq_routines[regs->int_no - 32];

    if (handler){
        handler(regs);
    }

    if (regs->int_no >= 40){
        outPortB(0xA0, 0x20); //send EOI to slave
    }

    outPortB(0x20,0x20); //send to master
}