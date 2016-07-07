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
}


struct regs{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

void int_handler(struct regs *st){
	printk(st->int_no,'d');
}





	

	
