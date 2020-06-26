The_partition_table:

Partition1:
Boot_signature1:	.byte 0x0
Start_head1:	.byte 0x20
Start_sector1:	.byte 0x21
Start_cylinder1:	.byte 0x0
System_signature1:	.byte 0x83
End_head1:	.byte 0x9f
End_sector1:	.byte 0x59
End_cylinder1:	.byte 0x87
Sectors_before_partition1:	.int 0x800
Sectors_in_partition1:	.int 0x5ff801

Partition2:
Boot_signature2:	.byte 0x0
Start_head2:	.byte 0x8a
Start_sector2:	.byte 0x88
Start_cylinder2:	.byte 0x24
System_signature2:	.byte 0x83
End_head2:	.byte 0x74
End_sector2:	.byte 0xe
End_cylinder2:	.byte 0x49
Sectors_before_partition2:	.int 0x600001
Sectors_in_partition2:	.int 0x600001

Partition3:
Boot_signature3:	.byte 0x0
Start_head3:	.byte 0x74
Start_sector3:	.byte 0xf
Start_cylinder3:	.byte 0x49
System_signature3:	.byte 0x83
End_head3:	.byte 0x2
End_sector3:	.byte 0x91
End_cylinder3:	.byte 0x56
Sectors_before_partition3:	.int 0xc00002
Sectors_in_partition3:	.int 0x200001

Partition4:
Boot_signature4:	.byte 0x0
Start_head4:	.byte 0x2
Start_sector4:	.byte 0x92
Start_cylinder4:	.byte 0x56
System_signature4:	.byte 0x83
End_head4:	.byte 0x2e
End_sector4:	.byte 0x2
End_cylinder4:	.byte 0x62
Sectors_before_partition4:	.int 0xe00003
Sectors_in_partition4:	.int 0x1fffbd


