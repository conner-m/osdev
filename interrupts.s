
#make handler for spurious irqs 7 15
.extern int_handler
.type int_handler_prep, @function
int_handler_prep:
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl %ebx
	pushl %ebp
	pushl %esi
	pushl %edi
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	movl $0x10 /* Kernel Data Segment */, %ebp
	movl %ebp, %ds
	movl %ebp, %es
	movl %ebp, %fs
	movl %ebp, %gs

	movl %cr2, %ebp
	pushl %ebp

	movl %esp, %ebx
	subl $4, %esp
	andl $0xFFFFFFF0, %esp /* 16-byte align stack */
	movl %ebx, (%esp)
	call int_handler
	movl %ebx, %esp

	popl %ebp
	movl %ebp, %cr2

	popl %gs
	popl %fs
	popl %es
	popl %ds
	popl %edi
	popl %esi
	popl %ebp
	popl %ebx
	popl %edx
	popl %ecx
	popl %eax

	addl $8, %esp
	iret

.type handler_prep, @function
handler_prep:
	pushl %gs
	pushl %fs
	pushl %es
	pushl %ds
	pusha
	movl $0x10, %eax
	movl %eax, %gs
	movl %eax, %fs
	movl %eax, %es
	movl %eax, %ds

	movl %esp, %eax
	pushl %eax

	call int_handler
	
	popl %eax

	popa
	popl %ds
	popl %es
	popl %fs
	popl %gs
	addl $8, %esp

	iret
	

.macro isr num
	.global isr\num
	.type isr\num, @function
	isr\num:
		pushl $0
		pushl $\num
		jmp int_handler_prep
.endm

.macro irq num
	.global irq\num
	.type irq\num, @function
	irq\num:
		#pushl $0
		pushl $(\num +32)
		jmp int_handler_prep
.endm

isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr 8
isr 9
isr 10
isr 11
isr 12
isr 13
isr 14
isr 15
isr 16
isr 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31
irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14