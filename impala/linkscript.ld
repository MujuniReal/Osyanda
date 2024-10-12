
ENTRY(_start)

SECTIONS{

	.text 0x100000 : ALIGN(4096)
	{
		*(.text)
		*(.rodata)
	}

	.rodata : ALIGN(4096)
	{
		*(.rodata)
	}

	.data : ALIGN(4096)
	{
		*(.data)
	}

	.bss : ALIGN(4096)
	{
		*(COMMON)
		*(bss)
	}
	.gnuasm : ALIGN(4096)
	{
		*(.gnuasm)
	}

}
