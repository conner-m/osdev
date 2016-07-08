#include <stddef.h>
#include <stdint.h>

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


uint16_t pic_get_irr(void);
uint16_t pic_get_isr(void);
void IRQ_set_mask(unsigned char IRQline);
void IRQ_clear_mask(unsigned char IRQline);
