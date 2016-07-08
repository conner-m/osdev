#include "../include/include.h"
#include <stdint.h>
#include <stddef.h>

struct regs{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

void int_handler(struct regs *st){
	printk(st->int_no,'d');

	
}

