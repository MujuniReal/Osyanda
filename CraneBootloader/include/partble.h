The_partition_table:

Partition1:
Boot_signature1:	.byte 0x0
Start_head1:	.byte 0x20
Start_sector1:	.byte 0x21
Start_cylinder1:	.byte 0x0
System_signature1:	.byte 0x83
End_head1:	.byte 0xfe
End_sector1:	.byte 0xff
End_cylinder1:	.byte 0xff
Sectors_before_partition1:	.int 0x800
Sectors_in_partition1:	.int 0x182d866f

Partition2:
Boot_signature2:	.byte 0x80
Start_head2:	.byte 0xfe
Start_sector2:	.byte 0xff
Start_cylinder2:	.byte 0xff
System_signature2:	.byte 0x7
End_head2:	.byte 0xfe
End_sector2:	.byte 0xff
End_cylinder2:	.byte 0xff
Sectors_before_partition2:	.int 0x182d9000
Sectors_in_partition2:	.int 0xc583800

Partition3:
Boot_signature3:	.byte 0x0
Start_head3:	.byte 0xfe
Start_sector3:	.byte 0xff
Start_cylinder3:	.byte 0xff
System_signature3:	.byte 0x82
End_head3:	.byte 0xfe
End_sector3:	.byte 0xff
End_cylinder3:	.byte 0xff
Sectors_before_partition3:	.int 0x2485c800
Sectors_in_partition3:	.int 0xbd1000

Partition4:
Boot_signature4:	.byte 0x0
Start_head4:	.byte 0x0
Start_sector4:	.byte 0x0
Start_cylinder4:	.byte 0x0
System_signature4:	.byte 0x0
End_head4:	.byte 0x0
End_sector4:	.byte 0x0
End_cylinder4:	.byte 0x0
Sectors_before_partition4:	.int 0x0
Sectors_in_partition4:	.int 0x0

