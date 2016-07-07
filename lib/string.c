#include <stdint.h>
#include <stddef.h>
char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)	
		buf[i] = "0123456789abcdef"[val % base];	
	return &buf[i+1];
	
}

size_t strlen(const char* str){
	size_t len = 0;	
	while(str[len])
		len++;
	return len;
}
