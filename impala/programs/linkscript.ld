
ENTRY(terminal)

SECTIONS{

	.text 0x160000 :
	{

		*(.text)
		*(.rodata)
}

	.data :
	{
		*(.data)

}

}
