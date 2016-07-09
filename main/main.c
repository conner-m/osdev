#include "../include/include.h"
#include <stdbool.h>

extern char KernelEnd[];

/*struct data{
	uint8_t color;
	uint8_t data;
};*/

void main(){
	cls();
	//printk("Test",'s');
	remap_pic();
	idt_init();
	cls();
	outb(0x21,0xfd);
   	outb(0xa1,0xff);
	asm("sti");
	//PS2_Initialize();
	
	//outb();
	//asm volatile("int $0x07");
}







	

	
