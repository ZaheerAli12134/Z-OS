.PHONY: all clean kernel image
all: clean kernel image

clean:
	rm -f *.o kernel.bin kernel.iso
	rm -rf isodir

kernel:
	gcc -m32 -ffreestanding -fno-stack-protector -fno-builtin -c kernel/kernel.c -o kernel.o
	gcc -m32 -ffreestanding -fno-stack-protector -fno-builtin -c kernel/gdt.c -o gdt.o
	nasm -f elf32 kernel/boot.asm -o boot_asm.o
	nasm -f elf32 kernel/gdt.asm -o gdt_asm.o

image:
	ld -m elf_i386 -T linker.ld -o kernel.bin boot_asm.o kernel.o gdt.o gdt_asm.o
	mkdir -p isodir/boot/grub
	mv kernel.bin isodir/boot/kernel.bin
	cp boot/grub/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir
	rm *.o

