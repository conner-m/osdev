#include "../include/include.h"
#include <stdbool.h>

extern char KernelEnd[];

/*struct data{
	uint8_t color;
	uint8_t data;
};*/

void main(){
	cls();
	printk("Test",'s');
	remap_pic();
	idt_init();
	
	//asm volatile("int $0x07");
}







	

	
