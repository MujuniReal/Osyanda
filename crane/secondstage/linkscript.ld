
ENTRY(crane_main)

SECTIONS{

	.text 0x80000: ALIGN(4096)
	{
		*(.text)
		*(.rodata)
	}

	.data : ALIGN(4096)
	{
		*(.data)

	}

	.bss : ALIGN(4096)
	{
		*(COMMON)
		*(.bss)
	}
}
