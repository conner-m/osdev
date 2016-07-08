#include "../include/include.h"
#include <stdbool.h>

extern char KernelEnd;

/*struct data{
	uint8_t color;
	uint8_t data;
};*/

void main(){
	cls();
	printk("Test",'s');
	remap_pic();
	idt_init();
	
	uint16_t irr = pic_get_irr(), isr = pic_get_isr();
	//printk(p, 'h');
	printk("  IRR=",'s');
	printk(irr,'h');
	printk("  ISR=",'s');
	printk(isr, 'h');
	asm("sti");
	/*while(1==1){
		if(pic_get_isr() != isr){
			isr = pic_get_isr();
			printk("  New ISR=",'s');
			printk(isr,'h');
		}
		if(pic_get_irr() != irr){
			irr = pic_get_irr();
			printk("  New IRR=",'s');
			printk(irr,'h');	
			
		}

	}*/
	//asm volatile("cli");
	//asm volatile("sti");
	
}







	

	
