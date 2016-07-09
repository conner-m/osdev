#include <stdint.h>

void outb(unsigned short addr, unsigned char msg){
	asm volatile("outb %0, %1"
				 : : "a"(msg), "Nd"(addr));
}
uint8_t inb(unsigned short addr){
	uint8_t ret;
	asm volatile("inb %1, %0"
				 : "=a"(ret) : "dN"(addr));
	return ret;
}