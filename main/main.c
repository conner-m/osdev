#include <x86/pic.h>
#include <x86/idt.h>
#include <x86/gdt.h>
#include <io.h>
#include <display/textmode/textmode_display.h>
#include <keyboard/kbd.h>
#include <stdbool.h>


extern char KernelEnd[];

/*struct data{
	uint8_t color;
	uint8_t data;
};*/

void main(){
	pic_remap();
	irq_handlers_init();
	idt_init();
	keyboard_init();
	gdt_install();
	
	cls();
	printk("> ",'s');

	asm("sti");
	

}









	

	
