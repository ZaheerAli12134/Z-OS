[bits 32]
[extern kernelmain]

section .multiboot
    align 4
    dd 0x1BADB002            
    dd 0x00000003              
    dd -(0x1BADB002 + 0x00000003) 

section .text
global start
start:
    cli                    
    mov esp, stack_top     
    call kernelmain        
.hang:
    cli
    hlt
    jmp .hang

section .bss
    align 16
stack_bottom:
    resb 8192             
stack_top:
