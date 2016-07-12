#include <io.h>
#include <display/textmode/textmode_display.h>
#include <keyboard/kbd.h>
#include <stdint.h>
#include <stddef.h>
unsigned char exception_messages[]={
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved1"
};
struct regs{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};
void handler_default(){
	printk("Default ",'s');

}
struct handler{
	void (*func)(); 
};

struct handler irq_handler_list[47];

void irq_handlers_install(int h, uintptr_t hand_func){
	struct handler* han = &irq_handler_list[h];
	han->func = hand_func;

}

void irq_handlers_init(){
	irq_handlers_install(0,&handler_default);
	irq_handlers_install(1,&keyboard_handler);
	irq_handlers_install(2,&handler_default);
	irq_handlers_install(3,&handler_default);
	irq_handlers_install(4,&handler_default);
	irq_handlers_install(5,&handler_default);
	irq_handlers_install(6,&handler_default);
	irq_handlers_install(7,&handler_default);
	irq_handlers_install(8,&handler_default);
	irq_handlers_install(9,&handler_default);
	irq_handlers_install(10,&handler_default);
	irq_handlers_install(11,&handler_default);
	irq_handlers_install(12,&handler_default);
	irq_handlers_install(13,&handler_default);
	irq_handlers_install(14,&handler_default);
	irq_handlers_install(15,&handler_default);
	
}

void int_handler(struct regs *st){

	if (st->int_no >= 40){
        	outb(0xA0, 0x20);
		
    	}
    	outb(0x20, 0x20);

	if(st->int_no-32 <= 15){
		struct handler han = irq_handler_list[(st->int_no)-32];
		han.func();
	}
	else{
		printk(exception_messages[st->int_no],'s');}

	
}




