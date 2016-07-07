#include <stdint.h>
#include <stddef.h>

uint16_t* SCRN_BUFFER = (uint16_t*)0xB8000;
const int HEIGHT = 30, WIDTH = 80;
int xpos = 0, ypos = 0;

void cls(){
	for(int h = 0; h <= HEIGHT; h++)
		for(int w = 0; w <= WIDTH; w++){
			int pos = h * WIDTH + w;
			SCRN_BUFFER[pos] = ' ';
		}

}

void printk(const char* str, const char* format){
		//struct data dat;
		//dat.data = str;
		//dat.color = 7<<8;
		if(format == 's')
			puts(str);			
		else if(format == 'd')
			puts(itoa((int)str,10));			
		else if(format == 'h')
			puts(itoa((int)str, 16));			
		else if(format == 'b')
			puts(itoa((int)str,2));
}

void puts(const char* str){
	size_t len = strlen(str);
	for(int i = 0; i < len; i++)
		putchar(str[i]);
}

void putchar(const char* ch){
	uint16_t pos = ypos * WIDTH + xpos;
	SCRN_BUFFER[pos] = (int)ch | 7 << 8;
	
	if(xpos > WIDTH){
		xpos = 0; 
		ypos++;
	}
	else
		xpos++;
}