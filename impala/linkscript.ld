
ENTRY(_start)

SECTIONS{

	.text 0x60000 :
	{

		*(.text)
		*(.rodata)
}

	.data :
	{
		*(.data)

}

}
