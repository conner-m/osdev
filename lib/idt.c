#include <stdint.h>
#include "../include/include.h"
#include "../include/interrupts.h"

#define INTERRUPT 0xE /* Interrupts disabled in eflags. */
#define TRAP 0xF      /* Interrupts unaffected in eflags. */

#define FLAG_PRESENT (1 << 7)
#define DPL_SHIFT 5
#define DPL_BITS 2
#define TYPE_SHIFT 0
#define TYPE_BITS 4

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1


void* memset(void* bufptr, int value, size_t size)
{
	unsigned char* buf = (unsigned char*) bufptr;
	for ( size_t i = 0; i < size; i++ )
		buf[i] = (unsigned char) value;
	return bufptr;
}
void lidt(uintptr_t base, size_t limit){
	asm volatile ("subl $6, %%esp\n\t"
	              "movw %w0, 0(%%esp)\n\t"
	              "movl %1, 2(%%esp)\n\t"
	              "lidt (%%esp)\n\t"
	              "addl $6, %%esp" : : "rN"(limit), "r"(base));
}

struct idt_entry{
	uint16_t offset_1; //(Handler Low)
	uint16_t sel;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t offset_2; //(Handler High)
};

struct idt_entry idt[256];

void make_idt_entry(struct idt_entry* idte,void(*handler)(void), uint8_t type, uint8_t dpl){
	idte->offset_1 = (uintptr_t)handler >> 0 & 0xFFFF;
	idte->sel = 0x08;
	idte->zero = 0;
	idte->type_attr = FLAG_PRESENT | dpl << DPL_SHIFT | type << TYPE_SHIFT;
	idte->offset_2 = (uintptr_t)handler >> 16 & 0xFFFF;
}

void idt_init(){
	memset(&idt, 0, sizeof(idt));
	make_idt_entry(&idt[0], isr0, INTERRUPT, 0x0);
	make_idt_entry(&idt[1], isr1, INTERRUPT, 0x0);
	make_idt_entry(&idt[2], isr2, INTERRUPT, 0x0);
	make_idt_entry(&idt[3], isr3, INTERRUPT, 0x0);
	make_idt_entry(&idt[4], isr4, INTERRUPT, 0x0);
	make_idt_entry(&idt[5], isr5, INTERRUPT, 0x0);
	make_idt_entry(&idt[6], isr6, INTERRUPT, 0x0);
	make_idt_entry(&idt[7], isr7, INTERRUPT, 0x0);
	make_idt_entry(&idt[8], isr8, INTERRUPT, 0x0);
	make_idt_entry(&idt[9], isr9, INTERRUPT, 0x0);	
	make_idt_entry(&idt[10], isr10, INTERRUPT, 0x0);
	make_idt_entry(&idt[11], isr11, INTERRUPT, 0x0);
	make_idt_entry(&idt[12], isr12, INTERRUPT, 0x0);
	make_idt_entry(&idt[13], isr13, INTERRUPT, 0x0);
	make_idt_entry(&idt[14], isr14, INTERRUPT, 0x0);
	make_idt_entry(&idt[15], isr15, INTERRUPT, 0x0);
	make_idt_entry(&idt[16], isr16, INTERRUPT, 0x0);
	make_idt_entry(&idt[17], isr17, INTERRUPT, 0x0);
	make_idt_entry(&idt[18], isr18, INTERRUPT, 0x0);
	make_idt_entry(&idt[19], isr19, INTERRUPT, 0x0);
	make_idt_entry(&idt[20], isr20, INTERRUPT, 0x0);
	make_idt_entry(&idt[21], isr21, INTERRUPT, 0x0);
	make_idt_entry(&idt[22], isr22, INTERRUPT, 0x0);
	make_idt_entry(&idt[23], isr23, INTERRUPT, 0x0);
	make_idt_entry(&idt[24], isr24, INTERRUPT, 0x0);
	make_idt_entry(&idt[25], isr25, INTERRUPT, 0x0);
	make_idt_entry(&idt[26], isr26, INTERRUPT, 0x0);
	make_idt_entry(&idt[27], isr27, INTERRUPT, 0x0);
	make_idt_entry(&idt[28], isr28, INTERRUPT, 0x0);
	make_idt_entry(&idt[29], isr29, INTERRUPT, 0x0);
	make_idt_entry(&idt[30], isr30, INTERRUPT, 0x0);
	make_idt_entry(&idt[31], isr31, INTERRUPT, 0x0);
	make_idt_entry(&idt[32], irq0, INTERRUPT, 0x0);
	make_idt_entry(&idt[33], irq1, INTERRUPT, 0x0);
	make_idt_entry(&idt[34], irq2, INTERRUPT, 0x0);
	make_idt_entry(&idt[35], irq3, INTERRUPT, 0x0);
	make_idt_entry(&idt[36], irq4, INTERRUPT, 0x0);
	make_idt_entry(&idt[37], irq5, INTERRUPT, 0x0);
	make_idt_entry(&idt[38], irq6, INTERRUPT, 0x0);
	make_idt_entry(&idt[39], irq7, INTERRUPT, 0x0);
	make_idt_entry(&idt[40], irq8, INTERRUPT, 0x0);
	make_idt_entry(&idt[41], irq9, INTERRUPT, 0x0);
	make_idt_entry(&idt[42], irq10, INTERRUPT, 0x0);
	make_idt_entry(&idt[43], irq11, INTERRUPT, 0x0);
	make_idt_entry(&idt[44], irq12, INTERRUPT, 0x0);
	make_idt_entry(&idt[45], irq13, INTERRUPT, 0x0);
	make_idt_entry(&idt[46], irq14, INTERRUPT, 0x0);
	lidt((uintptr_t) idt, sizeof(idt) - 1);
}


 
void remap_pic()
{
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	outb(PIC1_DATA, 0x20);                 // ICW2: Master PIC vector offset
	outb(PIC2_DATA, 0x28);                 // ICW2: Slave PIC vector offset
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);
 
	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}

