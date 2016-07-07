#include <stddef.h>

//io.c
void outb(unsigned short addr, unsigned char msg);
char inb(unsigned short addr);

//string.c
char* itoa(int val, int base);
size_t strlen(const char* str);

//vga.c
void cls();
void printk(const char* str, const char* format);

//kb.c
unsigned char kbdus[128];

//idt.c
void idt_init();
void remap_pic();

