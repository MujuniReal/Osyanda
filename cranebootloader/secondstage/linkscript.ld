
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

}
