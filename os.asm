[org 0x7c00]

mov ax, 0
mov ds, ax
mov si, msg
jmp loop

main:
    jmp $


loop:
    lodsb
    test al, al
    jz main
    mov ah, 0x0e
    int 0x10
    jmp loop



msg: db 'hello world!',0
times 510-($-$$) db 0       
dw 0xAA55 
