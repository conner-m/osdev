#include <io.h>

#define ICW1_ICW4 0x01		
#define ICW1_INIT 0x10		

#define ICW4_8086 0x01		
#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1

#define PIC_READ_ISR 0xB
#define PIC_READ_IRR 0xA

void pic_remap(){
	unsigned char a1, a2;
 
	a1 = inb(PIC1_DATA);                        
	a2 = inb(PIC2_DATA);
 
	outb(PIC1_CMD, ICW1_INIT+ICW1_ICW4);  
	outb(PIC2_CMD, ICW1_INIT+ICW1_ICW4);
	outb(PIC1_DATA, 0x20);	//Offsets                 
	outb(PIC2_DATA, 0x28);                 
	outb(PIC1_DATA, 4);	//Connect PIC1&2 through pin 2                       
	outb(PIC2_DATA, 2);                       

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);
	//printk("PICs Set", 's');
	//outb(0x20, 0xF4);

	//outb(PIC1_CMD, 0xFF);
 
	//outb(PIC1_DATA, a1);   
	//outb(PIC2_DATA, a2);
}

/* Helper func */
static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_CMD, ocw3);
    outb(PIC2_CMD, ocw3);
    return (inb(PIC2_CMD) << 8) | inb(PIC1_CMD);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

void IRQ_set_mask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) | (1 << IRQline);
    outb(port, value);        
}
 
void IRQ_clear_mask(unsigned char IRQline) {
    uint16_t port;
    uint8_t value;
 
    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inb(port) & ~(1 << IRQline);
    outb(port, value);        
}