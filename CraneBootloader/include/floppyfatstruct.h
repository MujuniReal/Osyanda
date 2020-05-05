#define FAT_STRUCT
//the following file is for a floppy disk of 1.4MBs

FATstruct:

devOEM:	.asciz	"mkdosfs"	//Original Equipment Manufacturer 8bytes we ended this string with a zero to make up for 8bytes
ByPSect:	.word 0x0200	//512Bytes per sector
SectPClust:	.byte 0x01	//Sectors per cluster in this case one cluster is as heavy as the sector 1Byte
ResSects:	.word 0x0001	//Reserved Sectors of Floppy 2Bytes in this case this is initialized to 1 coz there is onlyone the boot sector as the reserved sector
FatTabs:	.byte 0x02	//Number of Fat tables 1Byte i gues becoz its a floppy with two sides period thats why
NRootDirEs:	.word 0x00e0	//Maximum Number of root directory entries for a floppy disk 2Bytes in base 10 they are 224 as max entries
TotSects:	.word 0x0b40	//Total number of sectors on the floppy 2Bytes
MedDescr:	.byte 0xf0	//The media descriptor of a floppy disk 1Byte for any floppy disk
SectsPFat:	.word 0x0009	//The number of sectors per FAT 2Bytes each FAT table spans 9 sectors
SectsPTrck:	.word 0x0012	//Sectors Per Track 2Bytes. for this floppy they are 18 sectors per track
NHeads:		.word 0x0002	//Number of heads 2Bytes, of the disk or required heads thats if the disk doesnt have the physical heads
NHiddenSects:	.word 0x0000	//Number of hidden sectors 2Bytes we go zero coz we wish not to hide any or naturally there arent any hidden sectors
NhiddnSectshi:	.word 0x0000	//This is the total number of hidden sectors as a high word of the total number spanning 2Bytes
TotSectsInFS:   .word 0x0000
                .byte 0x00      //Total sectors in Filesystem

LogDrvNo:	.byte 0x00	//Logical Drive Number 1Byte. This here is tobe initialized at boot time from the %dl register coz the %dl register holds the number of the selected device as seen from the BIOS perspective
Resrvd:		.byte 0x00	//This here is reserved space 1Byte
ExtSig:		.byte 0x01	//Well this was the extended signature of this floppy disk 1Byte
DrvSeriNum:	.word 0xa329
		.word 0x7091	//This is the drive Serial Number comes with the drive it spans 4Bytescc
		.byte 0x64
VolLabel:	.ascii "           "	//Volume Label 11Bytes like a name We just initialized it with spaces in hexadecimal ascii spaces are 0x20
FSType:		.ascii "FAT12   "	//Filesystem Type This Spans 8Bytes 

