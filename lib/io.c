#include <stdint.h>

void outb(unsigned short addr, unsigned char msg){
	asm volatile("outb %0, %1"
				 : : "a"(msg), "Nd"(addr));
}
char inb(unsigned short addr){
	char ret;
	asm volatile("inb %1, %0"
				 : "=a"(ret) : "dN"(addr));
	return ret;
}