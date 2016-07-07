#!/bin/bash
../i686/bin/i686-elf-as boot.s -o boot.o

../i686/bin/i686-elf-gcc -c main/main.c -o main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
../i686/bin/i686-elf-gcc -c lib/io.c -o io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
../i686/bin/i686-elf-gcc -c lib/string.c -o string.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
../i686/bin/i686-elf-gcc -c lib/vga.c -o vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
../i686/bin/i686-elf-gcc -c lib/idt.c -o idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

../i686/bin/i686-elf-gcc -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib boot.o main.o io.o string.o vga.o idt.o -lgcc
rm *.o