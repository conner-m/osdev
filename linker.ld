ENTRY(_start)

SECTIONS{
	/*. = 1M;
	.text BLOCK(4K):ALIGN(4K){
		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K):ALIGN(4K){
		*(.rodata)
	}

	.data BLOCK(4K):ALIGN(4K){
		*(.COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}*/

	/*First put the multiboot header, as it is required to be put very early
	early in the image or the bootloader won't recognize the file format.
	Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}


	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}


	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}


	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
}
KernelEnd = .;