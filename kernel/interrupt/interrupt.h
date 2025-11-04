#include <stdint.h>
struct idt_entry{
   uint16_t offset_high;      
   uint16_t selector;       
   uint8_t  zero;           
   uint8_t  gate_type; 
   uint16_t offset_2low;       
}__attribute__((packed));



