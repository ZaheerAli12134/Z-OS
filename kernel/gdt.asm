global gdt_flush

;re setting all segment registers
gdt_flush:
    MOV eax, [esp+4]
    LGDT [eax]
    MOV, eax 0x10
    MOV ss, ax
    MOV ds, ax
    MOV es
    MOV gs 
    MOV fs

    JMP 0x08:.flush  ;far jump to 2nd entry in GDT to reset cs

.flush:
    RET



