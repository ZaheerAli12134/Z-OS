global idt_flush

idt_flush:
    MOV eax, [esp+4]
    LIDT[eax]
    STI 
    RET

%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
        cli
        PUSH LONG 0
        PUSH LONG %1
        JMP isr_commonH
%endmacro

%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        cli
        push long %1
        JMP isr_commonH
%endmacro

%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push long 0 
        push long %2
        jmp irq_commonH
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9 
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31
ISR_NOERRCODE 128
ISR_NOERRCODE 177

IRQ 0, 32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47


extern isr_handler
isr_commonH:

    pusha ;push all general purpose registers onto stack to preserve thir state

    mov eax, ds  ;push data segement selector to stack to preserve memory context as we are going to switch to kernel data mode after
    push eax

    mov  eax, cr2 ;holds the address that holds the page fault, needed to handle page faults useless otherwsie
    push eax

    mov ax, 0x10  ;change to kernel data mode
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp    ;push stack pointer and all C function
    call isr_handler

    add esp, 8     ;removes cr2 and C argument from stack

    pop ebx   ;pops old data segment selector and returns to old mode, could be user data ect
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa    ;pop all original gpr's
    add esp, 8 ;removes interrupt number and error code
    STI        ;re enables interrupts
    iret  ;return from interrupt, returns eip (instruction pointer) Code segment and the eflags(arithmetic results and other important flags)

extern irq_handler
irq_commonH:

    pusha 

    mov eax, ds  

    mov  eax, cr2 
    push eax

    mov ax, 0x10 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp  
    call irq_handler

    add esp, 8    

    pop ebx   
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa    
    add esp, 8 
    STI        
    iret  
    