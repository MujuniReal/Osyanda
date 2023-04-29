
ENTRY(mainSecond)

SECTIONS{

	.text 0x0:
	{
		*(.text)
		*(.rodata)
	}

	.data :
	{
		*(.data)

	}

	.bss : 
	{
		*(COMMON)
		*(.bss)
	}
}
