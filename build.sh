#!/bin/bash

AS="../i686/bin/i686-elf-as -g"
CC="../i686/bin/i686-elf-gcc -g -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wunused-parameter -Iinclude -Iarch -Idrivers -Ilib -c"
LD="../i686/bin/i686-elf-gcc -T"

CRTBEGIN="../i686/bin/i686-elf-gcc -print-file-name=crtbegin.o)"
CRTEND="../i686/bin/i686-elf-gcc -print-file-name=crtend.o)"
$CC $CRTEND -o crte.o

$AS boot.s -o boot.o
$AS arch/x86/interrupts.s -o int.o
$AS arch/x86/crti.S -o i.o
$AS arch/x86/crtn.S -o n.o

$CC main/main.c -o main.o 
$CC lib/io.c -o io.o 
$CC lib/string.c -o string.o 
$CC drivers/display/textmode/textmode_display.c -o tmd.o 
$CC arch/x86/idt.c -o idt.o 
$CC arch/x86/interrupts.c -o intc.o 
$CC drivers/keyboard/kbd.c -o kb.o 
$CC arch/x86/pic.c -o pic.o
$CC arch/x86/gdt.c -o gdt.o


$LD linker.ld -o _/kernel.bin -ffreestanding -O2 -nostdlib boot.o int.o main.o io.o string.o tmd.o idt.o intc.o kb.o pic.o gdt.o -lgcc
rm *.o